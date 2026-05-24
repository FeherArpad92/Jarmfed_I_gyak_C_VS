---
layout: default
title: 5. Gyakorlat - AVR Portok és GPIO
nav_order: 8
---

# 5. Gyakorlat: AVR Portok és GPIO alapok (AT90CAN128)
{: .no_toc }

A mai gyakorlat célja a beágyazott rendszerek alapvető fogalmainak megismerése, különösen az AVR mikrovezérlők portjainak és GPIO (General Purpose Input/Output) lábainak kezelése. A feladatban egy **futófény** programot valósítunk meg az AT90CAN128 mikrovezérlőn.

## Tartalomjegyzék
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Elméleti háttér

### Mi a különbség egy PC és egy mikrovezérlő között?

Egy hagyományos számítógép (PC) operációs rendszert futtat, amelyen keresztül érheti el a hardvert – közvetlenül nem nyúlhat a portokhoz. Egy **mikrovezérlő** (mint az AT90CAN128) ezzel szemben egy egyetlen chipen lévő kis számítógép, amelyen nincs operációs rendszer: a programunk közvetlenül, „csupaszon" fut a hardveren, és **közvetlenül vezérli a kivezetéseket (lábakat/pineket)**.

Ez adja a beágyazott rendszerek erejét: tökéletes valós idejű vezérléshez, pl. járművek, ipari eszközök, érzékelők számára.

---

### Mi az a Port és mi az a Pin?

A mikrovezérlő fizikai lábait (kivezetéseit) **portokba** csoportosítják. Az AT90CAN128-nak több ilyen portja van: **Port A, Port B, Port C, Port D, Port E, Port F, Port G**.

Minden porthoz **8 láb (pin)** tartozik: `pin0`-tól `pin7`-ig. Ezeket a lábakat összeköthetjük pl. LED-ekkel, nyomógombokkal, motorvezérlőkkel stb.

```
Port A lábai:
  PA7  PA6  PA5  PA4  PA3  PA2  PA1  PA0
  [7]  [6]  [5]  [4]  [3]  [2]  [1]  [0]
```

Minden pin kétállapotú digitálisan: **HIGH (1, ~5V)** vagy **LOW (0, 0V)**.

---

### Mi az a regiszter?

Mielőtt a portokhoz érnénk, fontos megérteni, hogy mi az a **regiszter**.

Egy regiszter a mikrovezérlő chipjén belül elhelyezkedő, **nagyon gyorsan elérhető, kis méretű memóriacella** – jellemzően 8 vagy 16 bites. A regiszterek közvetlenül a CPU-hoz vannak kötve (nem a külső RAM-ban vannak), ezért a hozzáférésük szinte azonnali.

A beágyazott programozásban kétféle regiszterrel találkozunk:
- **CPU regiszterek:** az ALU (Arithmetic Logic Unit) számítási munkaterei – ezeket a fordító kezeli automatikusan
- **Periféria (I/O) regiszterek:** a mikrovezérlő belső egységeit (portokat, timereket, UART-ot stb.) vezérlik – **ezeket mi írjuk a kódban**

A mi esetünkben a `DDRA`, `PORTA`, `PINA` stb. mind ilyen periféria I/O regiszterek. A C kódban úgy kezeljük őket, mintha sima változók lennének, de valójában a chip hardverét vezérlik közvetlenül.

> **Analógia:** Képzeljük el a regisztert mint egy villanykapcsoló-táblát. Minden bit egy kapcsoló: 1 = be, 0 = ki. A `DDRA` tábla megmondja, melyik „ajtó" bejárat és melyik kijárat, a `PORTA` tábla pedig azt, hogy melyik kijáraton folyjon áram.

---

### A három fontos I/O regiszter: DDR, PORT, PIN

Minden porthoz három 8-bites **I/O regiszter** tartozik, amelyeken keresztül a mikrovezérlőt programozzuk:

| Regiszter | Neve | Funkció |
|---|---|---|
| `DDRx` | Data Direction Register | Megadja, hogy az adott pin **kimenet** (`1`) vagy **bemenet** (`0`) legyen |
| `PORTx` | Port Data Register | Ha kimenet: **HIGH** (`1`) vagy **LOW** (`0`) értéket ad a pinnek. Ha bemenet: belső felhúzó ellenállást (`pull-up`) aktivál |
| `PINx` | Port Input Pins | Olvassa a pin **aktuális fizikai állapotát** (csak olvasható!) |

> Az `x` helyére a port betűje kerül: `DDRA`, `DDRB`, `PORTA`, `PORTB`, `PINA`, `PINB`, stb.

---

### Bitek és számrendszerek – a bitmanipuláció alapjai

Mivel minden regiszter **8 bites**, a beállításokat bináris, hexadecimális vagy decimális számokkal adhatjuk meg. Ezek mind ugyanazt jelentik:

| Bináris | Hexadecimális | Decimális | Jelentés (DDRA esetén) |
|---|---|---|---|
| `0b11111111` | `0xFF` | `255` | Minden pin kimenet |
| `0b00000000` | `0x00` | `0` | Minden pin bemenet |
| `0b01010101` | `0x55` | `85` | Páros pinok (0,2,4,6) kimenetek |
| `0b11111110` | `0xFE` | `254` | Csak pin0 bemenet, többi kimenet |

> **Tipp:** C-ben a bináris literálokat `0b` előtaggal is írhatjuk (GCC kiterjesztés): `DDRA = 0b11111111;`

---

### Biteltolás (`<<` és `>>` operátorok)

A C nyelvben az egész számokat **bitenként** is tudjuk tolni:

- `x << n` → az `x` értékét **n bittel balra** tolja (minden lépés = 2-vel szorzás)
- `x >> n` → az `x` értékét **n bittel jobbra** tolja (minden lépés = 2-vel osztás)

Példa – futófény lépései (`PORTA` értéke):
```
Kezdet:  0b00000001  = 0x01  → csak PA0 HIGH (1. LED ég)
<< 1  :  0b00000010  = 0x02  → csak PA1 HIGH (2. LED ég)
<< 1  :  0b00000100  = 0x04  → csak PA2 HIGH (3. LED ég)
...
<< 1  :  0b10000000  = 0x80  → csak PA7 HIGH (8. LED ég) → irányváltás!
>> 1  :  0b01000000  = 0x40  → csak PA6 HIGH (7. LED ég)
...
>> 1  :  0b00000001  = 0x01  → csak PA0 HIGH → irányváltás!
```

---

### Szoftveres késleltetés – és miért nem javasolt?

Az AVR-en nincs `sleep()` függvény. A legegyszerűbb késleltetési módszer egy **üres `for` ciklus**, amely a CPU-t lekötve számol:

```c
for (long int i = 0; i < 100000; i++);
```

Ez a megközelítés **demonstrációs célra elfogadható**, de valódi fejlesztésben **kerülendő** – az alábbi okok miatt:

#### A blokkoló (blocking) hatás problémája

Amíg a CPU a `for` ciklust pörgeti, **semmilyen más feladatot nem tud elvégezni**. Ez az úgynevezett **blokkoló viselkedés**:

- Nem tud gombnyomást érzékelni
- Nem tud soros kommunikációt (UART) kezelni
- Nem tud szenzort olvasni
- Nem reagál semmilyen külső eseményre

Egy valós járműelektronikai rendszerben (pl. ABS-vezérlő, motorvezérlő ECU) ez elfogadhatatlan lenne: ha a CPU egy késleltetési ciklusban „ül", egy kritikus szenzorjel feldolgozatlan marad.

> **Analógia:** Olyan, mintha a sofőr az időzítőt figyelve fejben visszaszámlálna, miközben a kezét a kormányról leveszi és a szemét lehúnyja. Ehelyett jobb egy ébresztőórát (timer) beállítani, és addig figyelni az utat.

#### Miért pontatlan?

A `for` ciklus lefutási ideje függ:
- a CPU **órajelétől** (AT90CAN128: akár 16 MHz, de **tipikusan 8MHz**)
- a fordító **optimalizálási szintjétől** – egy agresszív fordító akár el is **hagyhatja** az üres ciklust!
- a pipeline és az utasításkészlet belső végrehajtásától

#### Mi a helyes megoldás?

A késleltetésre és időzítésre **hardveres Timer/Counter egységeket** kell használni. Az AT90CAN128-nak több beépített timere van. A timer a háttérben, a CPU-tól függetlenül számlál, és egy **megszakítással (interrupt)** vagy pollinggal jelzi, ha lejárt az idő – a CPU közben szabadon végezhet más feladatokat.

> **A következő gyakorlatokban** megismerkedünk a Timer/Counter regiszterekkel és a polling-alapú időzítést, amellyel pontos és nem blokkoló késleltetést valósíthatunk meg.

---

## 1. Feladat: Futófény – Port inicializálás és biteltolás

**Feladat:** Valósítson meg egy futófény programot az AT90CAN128 mikrovezérlőn! A Port A 8 lábára kötött LED-ek egymás után gyulladjanak fel, majd vissza, végtelen ciklusban. Emellett inicializálja a Port B és Port D portokat is a leírtak szerint.

A `port_init()` függvény feladata:
- **Port A:** minden láb kimenet, kezdeti érték: csak a 0. pin HIGH (`PORTA = 1`)
- **Port B:** csak a páros lábak (0, 2, 4, 6) kimenetek (`DDRB = 0x55`), és ezek HIGH-on állnak
- **Port D:** a 0. pin bemenet, a többi (1–7) kimenet (`DDRD = 254`), és a kimenetek HIGH-on állnak

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  /******************************************************************************
  * Include files
  ******************************************************************************/
  #include <avr/io.h>   // Az AVR portok (DDRA, PORTA stb.) definícióit tartalmazza

  /******************************************************************************
  * Global Variables
  ******************************************************************************/
  int dir = 0;  // A futófény iránya: 0 = balra tolás (<<), 1 = jobbra tolás (>>)

  /******************************************************************************
  * Local Function Declarations
  ******************************************************************************/
  void port_init(void);

  /******************************************************************************
  * Function:         void port_init(void)
  * Description:      Port inicializáló függvény
  * Input:            -
  * Output:           -
  * Notes:            Port irányok és kezdeti értékek beállítása
  ******************************************************************************/
  void port_init(void)
  {
      // DDRA = 0xFF = 0b11111111: Port A ÖSSZES lába kimenet lesz
      DDRA = 0xff;
      // PORTA = 1 = 0b00000001: csak PA0 HIGH → az első LED ég
      PORTA = 1;

      // DDRB = 0x55 = 0b01010101: a PÁROS lábak (PB0, PB2, PB4, PB6) kimenetek,
      // a PÁRATLAN lábak (PB1, PB3, PB5, PB7) bemenetek
      DDRB = 0x55;
      // PORTB = 0x55: a kimenetnek beállított páros lábak HIGH-ra állnak
      PORTB = 0x55;

      // DDRD = 254 = 0b11111110: PD0 bemenet (bit0 = 0), PD1–PD7 kimenetek (bit1–7 = 1)
      DDRD = 254;
      // PORTD = 254: a kimenet lábak (PD1–PD7) HIGH-ra állnak
      PORTD = 254;
  }

  /******************************************************************************
  * Function:         int main(void)
  * Description:      Főprogram – futófény végtelen ciklusban
  * Input:            -
  * Output:           -
  * Notes:            -
  ******************************************************************************/
  int main(void)
  {
      // Portok inicializálása a főprogram elején – egyszer kell csak meghívni
      port_init();

      while (1)
      {
          // Ha az irány előre (dir==0), balra toljuk a bitet: a LED "léptet" PA0 → PA7 felé
          if (dir == 0)
          {
              PORTA = PORTA << 1;
          }
          // Ha az irány hátra (dir==1), jobbra toljuk: a LED "léptet" PA7 → PA0 felé
          else
          {
              PORTA = PORTA >> 1;
          }

          // Irányváltás: ha az alacsony végen vagyunk (PA0 ég), váltás előre irányba
          if (PORTA == 0x01) dir = 0;
          // Irányváltás: ha a magas végen vagyunk (PA7 ég), váltás hátra irányba
          if (PORTA == 0x80) dir = 1;

          // Szoftveres késleltetés: a CPU "semmit nem csinál" egy ideig,
          // hogy a LED-ek látható ideig világítsanak (nem pontos, de egyszerű)
          for (long int i = 0; i < 100000; i++);
      }
  }

  /******************************************************************************
  * Interrupt Routines
  ******************************************************************************/
  // (Ebben a feladatban nincsenek megszakítások)
  ```

  A program logikája – lépésről lépésre:

  | Lépés | `PORTA` értéke (bináris) | `PORTA` hex | Melyik LED ég? | `dir` |
  |---|---|---|---|---|
  | Indulás | `0b00000001` | `0x01` | PA0 | 0 |
  | 1. lépés | `0b00000010` | `0x02` | PA1 | 0 |
  | 2. lépés | `0b00000100` | `0x04` | PA2 | 0 |
  | … | … | … | … | 0 |
  | 7. lépés | `0b10000000` | `0x80` | PA7 | **1** (irányváltás) |
  | 8. lépés | `0b01000000` | `0x40` | PA6 | 1 |
  | … | … | … | … | 1 |
  | 14. lépés | `0b00000001` | `0x01` | PA0 | **0** (irányváltás) |

</details>

---

## Ellenőrző kérdések

1. Mit jelent a `DDRx` regiszter egyes bitjeinek `1` értéke?
2. Miért kell a `DDRA = 0xff` beállítás a `PORTA = 1` sor előtt?
3. Mi a `0x55` értéke binárisan? Melyik lábak lesznek kimenetek?
4. Mi történne, ha a `dir` változót nem globálisként, hanem a `main()` belsejében deklarálnánk, és a `port_init()` függvényen belül akarnánk elérni?
5. Miért nem pontos időzítés a `for` ciklusos késleltetés?
