---
layout: default
title: 6. Gyakorlat - AVR Timer és feladatütemező
nav_order: 9
---

# 6. Gyakorlat: AVR Timer/Counter és szoftveres feladatütemező (AT90CAN128)
{: .no_toc }

Az előző gyakorlatban láttuk, hogy a `for` ciklusos késleltetés blokkolja a CPU-t. A mai gyakorlat célja a **hardveres Timer/Counter** megismerése, amellyel pontos, nem blokkoló időzítést valósíthatunk meg. Emellett megismerünk egy egyszerű **szoftveres feladatütemező (task scheduler)** mintát, amellyel különböző időzítésű feladatokat tudunk párhuzamosan futtatni.

## Tartalomjegyzék
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Elméleti háttér

### Bitmaszkok és bitszintű operátorok

Az előző gyakorlathoz képest az inicializáló kódban új írásmódot látunk a regiszterértékek megadására. Ez a módszer **olvashatóbb és biztonságosabb** az egyszerű hexadecimális értékek írásánál.

#### A `(1 << n)` bitmaszkos jelölés

A `(1 << n)` kifejezés egy olyan 8-bites értéket állít elő, amelyben **csak az `n`-edik bit értéke 1**, a többi 0.

```
(1 << PA0) = (1 << 0) = 0b00000001 = 0x01
(1 << PA1) = (1 << 1) = 0b00000010 = 0x02
(1 << PA2) = (1 << 2) = 0b00000100 = 0x04
(1 << PA3) = (1 << 3) = 0b00001000 = 0x08
```

Az `avr/io.h` fejlécfájl definiálja a `PA0`, `PA1`, `PB0` stb. konstansokat, amelyek egyszerűen a megfelelő pin sorszámát jelentik (0, 1, 2, ...).

Több bitet VAGY (`|`) operátorral kombinálunk:
```c
// Ezek mind ugyanazt jelentik:
DDRA = 0x0F;
DDRA = 0b00001111;
DDRA = (1<<PA3) | (1<<PA2) | (1<<PA1) | (1<<PA0);  // <- legjobb olvashatóság!
```

#### Az XOR (`^`) toggle operátor

A `^=` (XOR egyenlő) operátor egy bit **állapotát megfordítja (toggle)**, a többi bitet érintetlenül hagyja:

```
PORTA = 0b00001111
XOR     0b00000001   ← (1<<PA0) maszk
      = 0b00001110   ← PA0 megfordult (1→0)

PORTA = 0b00001110
XOR     0b00000001
      = 0b00001111   ← PA0 ismét megfordult (0→1)
```

Kód: `PORTA ^= (1<<PA0);` → minden híváskor a PA0 pin állapota vált HIGH/LOW között.

#### Pull-up ellenállás és a `(0<<PBx)` probléma

```c
DDRB = (0<<PB0) | (0<<PB1);  // PB0, PB1 bemenetek
PORTB = (1<<PB0) | (1<<PB1); // Pull-up aktiválva
```

A **pull-up ellenállás** belső ellenállás a mikrovezérlőn belül, amely a bemeneti lábat HIGH szintre húzza, ha nincs rá kötve semmi. **Ez fontos nyomógomboknál: nyomás nélkül a pin HIGH, nyomásra (GND-re kötve) LOW lesz. Avagy a logika megfordul a bemeneteken.**

---

### Mi az a Timer/Counter?

A Timer/Counter (időzítő/számláló) a mikrovezérlő egyik belső perifériája. Egy **hardveres számláló**, amely a CPU-tól teljesen függetlenül, az órajel ütemére növeli az értékét. Az AT90CAN128-nak több timere van (Timer0, Timer1, Timer2, Timer3).

A Timer működése:
1. Az órajel minden ütemére (vagy prescaler után, ha be van állítva) a számláló értéke **1-gyel nő**
2. Ha eléri a beállított **felső határt (OCR – Output Compare Register)**, esemény keletkezik
3. Az esemény egy **jelzőbitet (flag)** állít be, amelyet a program kiolvashat
4. A számláló **visszaáll nullára** (CTC módban)

**A Timer nem blokkolja a CPU-t** – miközben a timer a háttérben számlál, a `while(1)` ciklusban lévő kód folyamatosan futhat.

---

### TCCR0A – Timer/Counter0 Control Register

A Timer0 viselkedését a **TCCR0A** regiszter vezérli. Szerkezete (AT90CAN128 datasheet, 12.9.1):

```
 Bit:    7       6       5       4       3       2       1       0
      +-------+-------+-------+-------+-------+-------+-------+-------+
      | FOC0A | WGM00 |COM0A1 |COM0A0 | WGM01 | CS02  | CS01  | CS00  |  TCCR0A
      +-------+-------+-------+-------+-------+-------+-------+-------+
        W      R/W     R/W     R/W     R/W     R/W     R/W     R/W
```

| Bit(ek) | Név | Funkció |
|---|---|---|
| 7 | **FOC0A** | Force Output Compare – csak nem-PWM módban aktív, általában 0 |
| 6 | **WGM00** | Waveform Generation Mode (együtt a WGM01-gyel) |
| 5–4 | **COM0A1:0** | Compare Output Mode – OC0A pin viselkedése compare match-nél |
| 3 | **WGM01** | Waveform Generation Mode (együtt a WGM00-val) |
| 2–0 | **CS02:0** | Clock Select – prescaler / órajelforrás kiválasztása |

**WGM bitek (Table 12-1):**

| WGM01 | WGM00 | Mód |
|:---:|:---:|---|
| 0 | 0 | Normal (0xFF-ig számlál) |
| 0 | 1 | PWM, Phase Correct |
| **1** | **0** | **CTC – Clear Timer on Compare** |
| 1 | 1 | Fast PWM |

### Prescaler – az időzítő „lassítója"

Az AT90CAN128 alapórajele pl. **8 MHz** (8 millió tick/másodperc). Ha a timer minden egyes teckre növelne, nagyon gyorsan elérné a határt. A **prescaler** egy osztó, amely lelassítja a timer órajelét. A CS02:0 bitek (TCCR0A bit 2–0) választják ki:

| CS02 | CS01 | CS00 | Forrás | Timer tick ideje (8MHz-en) |
|:---:|:---:|:---:|---|---:|
| 0 | 0 | 0 | Timer leállítva | – |
| 0 | 0 | 1 | clk/1 (nincs osztás) | 0.125 µs |
| 0 | 1 | 0 | clk/8 | 1 µs |
| 0 | 1 | 1 | clk/64 | 8 µs |
| 1 | 0 | 0 | clk/256 | 32 µs |
| **1** | **0** | **1** | **clk/1024** | **128 µs** |
| 1 | 1 | 0 | Külső órajel, T0 pin, lefutó él | – |
| 1 | 1 | 1 | Külső órajel, T0 pin, felfutó él | – |

> ⚠️ **Fontos!** CS=`111` **nem** 1024-es prescaler – az külső órajel forrást jelent! A 1024-es prescaler beállítása: **CS02=1, CS01=0, CS00=1** (CS=`101`).

A mi esetünkben `CS02=1, CS01=0, CS00=1` → **1024-es prescaler** → timer tick = 1024 / 8 000 000 Hz = **0.128 ms = 128 µs**.

---

### CTC mód (Clear Timer on Compare Match)

A Timer0-nak több üzemmódja van. Mi a **CTC (Clear Timer on Compare)** módot használjuk: `WGM01=1, WGM00=0` (Mode 2, a datasheet Table 12-1 szerint).

#### OCR0 – Output Compare Register

Az **OCR0** egy 8-bites regiszter, amelybe a compare értéket írjuk. A timer számlálója (TCNT0) folyamatosan eléri ezt az értéket, majd visszaáll.

```
 Bit:    7       6       5       4       3       2       1       0
      +-------+-------+-------+-------+-------+-------+-------+-------+
      |                       OCR0A[7:0]                              |  OCR0
      +-------+-------+-------+-------+-------+-------+-------+-------+
        R/W     R/W     R/W     R/W     R/W     R/W     R/W     R/W
 Alapért.: 0       0       0       0       0       0       0       0
```

CTC módban a timer számlál 0-tól felfelé, és amikor eléri az **OCR0** értékét:
1. A számláló **visszaáll 0-ra** (clear)
2. Az **OCF0 (Output Compare Flag 0)** jelzőbit beáll 1-re a TIFR regiszterben
3. Ha hardveres kimenet is be van kötve (COM0A=toggle), az OC0A pin állapotot vált

#### CTC periódus – compare match vs. kimenet hullámforma

Fontos megkülönböztetni a **compare match periódust** (az OCF0 flag sűrűségét) és a **kimeneti hullámforma periódusát**.

A képletekben szereplő **N a prescaler értéke** (1, 8, 64, 256 vagy 1024 – a CS bitek alapján):

- **Compare match periódus** (az OCF0 flag ennyi időnként keletkezik):

```
T_match = (OCR0 + 1) × N / f_cpu

ahol:  N      = prescaler értéke (pl. 1024)
       f_cpu  = a mikrovezérlő órajele (pl. 8 000 000 Hz)
       OCR0   = az Output Compare Register tartalma (0–255)
```


- **Kimeneti hullámforma periódusa** (az OC0A pin toggle): egy teljes periódushoz **2 compare match** kell (egy felfutó él + egy lefutó él → 2 élváltás per periódus):


```
T_hullam = 2 × (OCR0 + 1) × N / f_cpu

Ebből:  f_OC0A = f_cpu / (2 × N × (OCR0 + 1))    ← datasheet képlet
```


A mi kódunk az **OCF0 flag**-et kérdezi le (nem hardveres tűkimenet), ezért a **compare match periódus** a mérvadó:

```
T_match = (OCR0 + 1) × N / f_cpu
        = (77 + 1) × 1024 / 8 000 000
        = 78 × 128 µs
        = 9 984 µs ≈ 10 ms
```

**Az OCF0 flag tehát minden ~10 ms-ban keletkezik – a LED toggle is 10 ms-onként történik, de a LED villogás periódusa 20 ms (10 ms HIGH + 10 ms LOW = 2 élváltás).**

#### OCR0 kiszámítása adott időből

Ha adott a kívánt periódus (**T_match**), az OCR0 értéke közvetlenül időből is kiszámítható:

```
            T_match × f_cpu
OCR0  =  ─────────────────── − 1
                  N

ahol:  T_match = kívánt compare match periódus (másodpercben!)
       f_cpu   = órajel (Hz)
       N       = prescaler értéke
```

**Példa – 10 ms periódus, f_cpu = 8 MHz, N = 1024:**

```
OCR0 = (0.010 × 8 000 000 / 1024) − 1
     = (80 000 / 1024) − 1
     = 78.125 − 1
     ≈ 77
```

**Kiszámított értékek f_cpu = 8 MHz, N = 1024 mellett:**

| Kívánt T_match | OCR0 (számított) | OCR0 (kerekített) | Tényleges T_match |
|---:|---:|:---:|---:|
| 1 ms | 6.81 | 7 | 1.024 ms |
| 5 ms | 38.06 | 38 | 4.992 ms |
| **10 ms** | **78.13** | **77** | **9.984 ms** |
| 20 ms | 156.25 | 156 | 19.968 ms |
| 50 ms | 390.6 | – | ❌ nem fér el (max. 255)! |

> **Ha az OCR0 > 255 lenne**, nagyobb prescaler értéket kell választani. Amennyiben ez nem lehetséges abban az esetben szoftveres feladatütemezőt kell használni, lásd lentebb.

---

### TIFR0 és TIMSK0 – Flag és Interrupt Mask regiszterek

#### TIFR0 – Timer/Counter0 Interrupt Flag Register

A **TIFR0** jelzőbiteket (flag) tartalmaz – ezek állnak be, ha valamilyen timer esemény bekövetkezett.

```
 Bit:    7       6       5       4       3       2       1       0
      +-------+-------+-------+-------+-------+-------+-------+-------+
      |   –   |   –   |   –   |   –   |   –   |   –   | OCF0A | TOV0  |  TIFR0
      +-------+-------+-------+-------+-------+-------+-------+-------+
        R       R       R       R       R       R       R/W     R/W
 Alapért.: 0       0       0       0       0       0       0       0
```

| Bit | Név | Leírás |
|:---:|---|---|
| 1 | **OCF0A** | Output Compare Flag 0A – beáll, ha TCNT0 == OCR0 (compare match) |
| 0 | **TOV0** | Timer Overflow Flag – beáll, ha a számláló túlcsordul (0xFF → 0x00) |


#### A flag törlése

Az **OCF0A** bit beáll, ha a Timer0 elérte az OCR0 értékét.

> ⚠️ **AVR különlegesség – a flag törlése fordítva működik!**
>
> Az AVR architektúrában az I/O flag biteket **1-es írásával töröljük** (nem 0-val!). Ez ellentétes az elvárásokkal, de így működik. Ha 0-t írnánk, a flag **megmaradna**.

```c
// HELYES: 1-et írunk az OCF0 bitre → törlődik
TIFR = TIFR | (1<<OCF0);

// HIBÁS: 0-t írunk → a flag nem törlődik!
// TIFR &= ~(1<<OCF0);
```

---

### A szoftveres feladatütemező (task scheduler) minta

Valós rendszerekben különböző feladatoknak különböző időzítés kell:
- LED villogás: 500 ms
- Gombstátusz olvasás: 10 ms
- Kommunikáció: 100 ms
- Hibaellenőrzés: 1 s

Az egyszerű **polling-alapú task scheduler** minta:
1. Egyetlen alap-timer üt (pl. 10 ms)
2. Minden ütemben egy számláló nő (`timer_cnt++`)
3. A számláló oszthatósága alapján különböző jelzők (`task_flag`) állnak be
4. A `while(1)` ciklus ezeket a jelzőket vizsgálja, végrehajtja a feladatot, majd törli a jelzőt

```
timer_cnt % 1   == 0  →  10ms task  (minden ütemben)
timer_cnt % 10  == 0  →  100ms task (minden 10. ütemben)
timer_cnt % 50  == 0  →  500ms task (minden 50. ütemben)
timer_cnt % 100 == 0  →  1s task    (minden 100. ütemben)
```

Ez a megközelítés **nem blokkoló**: a CPU gyorsan végigfut a `while(1)` cikluson, minden feladatot csak akkor hajt végre, ha a megfelelő jelző be van állítva.

---

## 1. Feladat: Timer0 CTC és feladatütemező

**Feladat:** Valósítsa meg az alábbi programot AT90CAN128-on:
- **PA0–PA3:** kimenet (LED-ek), kezdetben HIGH
- **PB0–PB1:** bemenet, belső pull-up ellenállással
- Timer0 CTC módban, 10 ms-onként jelez
- PA0 vált 10 ms-onként, PA1 100 ms-onként, PA2 500 ms-onként, PA3 1 s-onként

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  /******************************************************************************
  * Include files
  ******************************************************************************/
  #include <avr/io.h>    // AVR port és regiszter definíciók
  #include <inttypes.h>  // uint8_t, uint16_t típusok

  /******************************************************************************
  * Global Variables
  ******************************************************************************/
  // A 10 ms-os timer ütemeit számolja – 100-nál visszaáll (uint16_t elég)
  uint16_t timer_cnt = 0;

  // Feladatjelzők: 1 ha a feladat esedékes, 0 ha nem
  // A while(1) ciklus ezeket figyeli és a végrehajtás után törli
  uint8_t timer_task_10ms  = 0;
  uint8_t timer_task_100ms = 0;
  uint8_t timer_task_500ms = 0;
  uint8_t timer_task_1s    = 0;

  /******************************************************************************
  * Function:         void port_init(void)
  * Description:      I/O portok inicializálása
  * Input:            -
  * Output:           -
  * Notes:            PA0-PA3 kimenet, PB0-PB1 bemenet pull-up-pal
  ******************************************************************************/
  void port_init(void)
  {
      // PA0–PA3 kimenetek. A (1<<PAx) | ... alakkal bitmaszkot építünk.
      // Csak PA0–PA3 lesz kimenet, PA4–PA7 bemenet marad (0 az alap).
      DDRA = (1<<PA3) | (1<<PA2) | (1<<PA1) | (1<<PA0);

      // PA0–PA3 kezdeti értéke HIGH (LED-ek kigyulladnak induláskor)
      PORTA = (1<<PA3) | (1<<PA2) | (1<<PA1) | (1<<PA0);

      // PB0, PB1 bemenetek (DDR bit = 0 az alapértelmezett, de explicit is megadható)
      // Megjegyzés: (0<<PBx) mindig 0, ezért DDRB = 0x00-val egyenértékű
      DDRB = (0<<PB0) | (0<<PB1);

      // PORTB = 1 bemenet esetén → belső pull-up ellenállás aktiválása
      // Így a pin HIGH-on áll, ha nincs rá kötve semmi (nyomógomb esetén fontos!)
      PORTB = (1<<PB0) | (1<<PB1);
  }

  /******************************************************************************
  * Function:         void timer_init(void)
  * Description:      Timer0 inicializálása CTC módban, ~10 ms periódussal
  * Input:            -
  * Output:           -
  * Notes:            f_cpu = 8 MHz, N = 1024 (CS=101), OCR0 = 77
  *                   T_match = (77+1) * 1024 / 8 000 000 = 9.984 ms ≈ 10 ms (OCF0 flag)
  *                   T_villogas = 2 * T_match = ~20 ms (LED teljes periódus)
  ******************************************************************************/
  void timer_init(void)
  {
      // TCCR0 – Timer/Counter0 Control Register
      // WGM01=1, WGM00=0 → CTC mód (Mode 2, datasheet Table 12-1)
      // CS02=1, CS01=0, CS00=1 → prescaler: 1024 (CS=101, datasheet Table 12-5)
      // FIGYELEM: CS=111 külső órajelet jelent, NEM 1024-es prescalert!
      TCCR0 = (0<<WGM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);

      // OCR0 – Output Compare Register 0
      // A timer számlál 0-tól OCR0-ig, majd visszaáll 0-ra és beállítja az OCF0 flaget.
      // OCR0 = (f_cpu / (N * f_match)) - 1
      //      = (8 000 000 / (1024 * 100)) - 1 = 78.125 - 1 ≈ 77
      // → az OCF0 flag ~10 ms-onként keletkezik
      // → a LED villogás periódusa: 2 × 10 ms = 20 ms (2 élváltás = 1 teljes periódus)
      OCR0 = 77;
  }

  /******************************************************************************
  * Function:         uint8_t check_timer_compare(void)
  * Description:      Timer0 compare flag lekérdezése és törlése
  * Input:            -
  * Output:           1 ha a timer épp jelez (OCF0 bit be van állva), 0 ha nem
  * Notes:            AVR-en a flag törlése 1-es ÍRÁSÁVAL történik (nem 0-val!)
  ******************************************************************************/
  uint8_t check_timer_compare(void)
  {
      // TIFR – Timer Interrupt Flag Register
      // Az OCF0 bit 1-re áll, ha a Timer0 elérte az OCR0 értékét.
      // Az & (AND) maszkolással ellenőrizzük, hogy pontosan az OCF0 bit van-e beállva.
      if ((TIFR & (1<<OCF0)) == (1<<OCF0))
      {
          // A flag törlése: AVR-en 1-et ÍRUNK a flag bitre (ez töröl, nem 0 írás!)
          TIFR = TIFR | (1<<OCF0);
          return 1;  // Jelezzük a hívónak: timer leütött
      }
      return 0;  // Még nem telt el 10 ms
  }

  /******************************************************************************
  * Function:         int main(void)
  * Description:      Főprogram – nem blokkoló feladatütemező
  * Input:            -
  * Output:           -
  * Notes:            -
  ******************************************************************************/
  int main(void)
  {
      port_init();   // Portok beállítása
      timer_init();  // Timer0 elindítása

      // Végtelen főciklus – ez fut folyamatosan, nagyon gyorsan
      while (1)
      {
          // check_timer_compare() csak 10 ms-onként ad vissza 1-et.
          // Ha igen: növeljük a számlálót és beállítjuk az esedékes feladatjelzőket.
          if (check_timer_compare())
          {
              timer_cnt++;

              // Minden 10 ms-os ütemben (minden ticked): 10ms task
              if ((timer_cnt % 1)   == 0) timer_task_10ms  = 1;
              // Minden 10. ütemben (10 * 10ms = 100ms): 100ms task
              if ((timer_cnt % 10)  == 0) timer_task_100ms = 1;
              // Minden 50. ütemben (50 * 10ms = 500ms): 500ms task
              if ((timer_cnt % 50)  == 0) timer_task_500ms = 1;
              // Minden 100. ütemben (100 * 10ms = 1000ms = 1s): 1s task
              if ((timer_cnt % 100) == 0) timer_task_1s    = 1;
          }

          // --- Feladatok végrehajtása (csak ha a jelző be van állítva) ---

          // 10 ms-os feladat: PA0 toggle
          if (timer_task_10ms)
          {
              PORTA ^= (1<<PA0);    // PA0 XOR 1 → vált HIGH/LOW között
              timer_task_10ms = 0;  // Jelző törlése!
          }

          // 100 ms-os feladat: PA1 toggle
          if (timer_task_100ms)
          {
              PORTA ^= (1<<PA1);
              timer_task_100ms = 0;
          }

          // 500 ms-os feladat: PA2 toggle
          if (timer_task_500ms)
          {
              PORTA ^= (1<<PA2);
              timer_task_500ms = 0;
          }

          // 1 s-os feladat: PA3 toggle
          if (timer_task_1s)
          {
              PORTA ^= (1<<PA3);
              timer_task_1s = 0;
          }
      }
  }

  /******************************************************************************
  * Interrupt Routines
  ******************************************************************************/
  // (Ebben a feladatban polling alapon olvassuk a timer flaget, nem megszakítással)
  ```

    Az időzítések kiszámítása:

  | Jelző | Osztó | Ütemek száma | Időzítés |
  |---|:---:|:---:|---:|
  | `timer_task_10ms` | `% 1` | minden ütem | **10 ms** |
  | `timer_task_100ms` | `% 10` | minden 10. ütem | **100 ms** |
  | `timer_task_500ms` | `% 50` | minden 50. ütem | **500 ms** |
  | `timer_task_1s` | `% 100` | minden 100. ütem | **1000 ms = 1 s** |

  A program folyamatábrája:

  ```
  Indulás → port_init() → timer_init()
       ↓
  [while(1)] ←───────────────────────────────────────────┐
       ↓                                                 │
  check_timer_compare() == 1?                            │
    ├─ NEM → feladatjelzők vizsgálata                    │
    └─ IGEN → timer_cnt++                                │
              feladatjelzők beállítása                   │
              ↓                                          │
  timer_task_10ms == 1?  → PORTA ^= PA0, jelző törlése   │
  timer_task_100ms == 1? → PORTA ^= PA1, jelző törlése   │
  timer_task_500ms == 1? → PORTA ^= PA2, jelző törlése   │
  timer_task_1s == 1?    → PORTA ^= PA3, jelző törlése ──┘
  ```

</details>

---

## Ellenőrző kérdések

1. Mi a különbség a `(1<<PA0)` és a `0x01` között? Mikor melyiket érdemes használni?
2. Miért pont 77 az OCR0 értéke? Számítsa ki, milyen OCR0 értékkel kapnánk pontosan 20 ms-os **compare match periódust** (8 MHz, N=1024 esetén)! Ebben az esetben mekkora lenne a LED villogás tényleges periódusa?
3. Mi történne, ha a `timer_task_10ms = 0;` sort elfelejtjük a feladatblokk végéről?
4. Miért írunk 1-et az OCF0 bitre törléskor, és nem 0-t?
5. Mi az előnye a feladatjelzős (flag-alapú) megközelítésnek a közvetlen `PORTA ^= ...` híváshoz képest a timer-blokkban?
6. Mi lenne a `timer_cnt` változó maximális értéke, mielőtt túlcsordul (`uint16_t` esetén)? Hány másodperc ez 10 ms-os alapidőzítéssel?
