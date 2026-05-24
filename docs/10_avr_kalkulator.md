---
layout: default
title: 7. Gyakorlat - AVR Kalkulátor
nav_order: 10
---

# 7. Gyakorlat: AVR Kalkulátor – Gombok, prellentés, switch-case (AT90CAN128)
{: .no_toc }

Ez a záró beágyazott gyakorlat összefoglalja az eddig tanultakat. Egy egyszerű **4-bites kalkulátort** valósítunk meg: 5 nyomógombbal két számot és egy műveletet választunk, az eredményt LED-eken jelenítjük meg. Megismerjük a **gombprellentés** szoftveres kezelését, a **switch-case** utasítást, a bemeneti lábak olvasását (**PINB**), valamint a **nibble** fogalmát.

## Tartalomjegyzék
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Elméleti háttér

### Makrók konstansként – bit-flag értékek

Az előző gyakorlatokból már ismerjük a `#define` makrókat. Ebben a feladatban a műveletek azonosítóit **hatványai 2-nek** értékkel definiáljuk:

```c
#define OSSZEADAS  1   // 0b00000001
#define KIVONAS    2   // 0b00000010
#define OSZTAS     4   // 0b00000100
#define SZORZAS    8   // 0b00001000
```

Miért hatványai 2-nek? Mert így minden értéknek **pontosan egy bit** felel meg, és a `muvelet` változó biteltolással (`<< 1`) körbejárhatja az értékeket. A `PORTE = muvelet;` sor pontosan az aktív műveletet jelző bitet jeleníti meg a LED-eken.

```
muvelet = 1 → PORTE = 0b00000001 → PE0 ég  (összeadás)
muvelet = 2 → PORTE = 0b00000010 → PE1 ég  (kivonás)
muvelet = 4 → PORTE = 0b00000100 → PE2 ég  (osztás)
muvelet = 8 → PORTE = 0b00001000 → PE3 ég  (szorzás)
```

---

### Bemeneti lábak olvasása – a PIN regiszter

Az előző gyakorlatokban csak **kimenetként** használtuk a portokat. Ha egy láb **bemenet** (DDR bit = 0), akkor a tényleges fizikai állapotát a **PINx** regiszterből kell olvasni – nem a PORTx-ből!

```c
// Helyes: a PIN regiszter tartalmazza a tényleges feszültségszintet
if ((PINB & (1<<PB0)) == 0) { ... }   // PB0 alacsony (LOW) szinten van

// Helytelen: PORTB bemenet esetén a pull-up beállítást tartalmazza, nem az állapotot!
// if ((PORTB & (1<<PB0)) == 0) { ... }   ← NE így!
```

---

### Aktív LOW logika – miért van ez fordítva?

A nyomógombok **aktív LOW** módon vannak bekötve: a gomb egyik lába a mikrovezérlő bemeneti lábára, másik lába **GND**-re (földre) van kötve. A belső **pull-up ellenállás** az értéket HIGH-on tartja, ha a gombot nem nyomják:

```
Gomb FELENGEDVE:  PB0 → pull-up → HIGH (1)  ← „nem nyomott" állapot
Gomb LENYOMVA:    PB0 → GND    → LOW  (0)  ← „nyomott" állapot
```

Ezért a kódban a **lenyomást** `== 0` feltétel jelzi, nem `== 1`:
```c
if ((PINB & (1<<PB0)) == 0)  // Ha PB0 LOW → gomb le van nyomva
```

---

### Gombprellentés (debouncing) – miért szükséges?

Egy mechanikus nyomógomb lenyomásakor a kontaktusok nem azonnal záródnak teljesen – **fizikailag rezegnek** (prell), és rövid idő alatt többször nyitnak-záródnak. Ez akár 5–20 ms ideig tarthat. Ha a program ezt nem kezeli, egyetlen gombnyomásra **több eseményt** érzékel.

```
Valódi jel gombnyomáskor (prellezés nélkül kellene):
  ______              ______
       |______________|

Valódi jel (prellezéssel):
  ____                ______
      |_|‾|_|‾|_|‾|_|

        ↑ ezeket érzékeli a gyors program többszöri nyomásként!
```

#### Szoftveres prellentés állapotgéppel

A legegyszerűbb megoldás: egy **jelző változó (flag)** tárolja, hogy a gomb le van-e nyomva, és az eseményt csak **egyszer** kezeljük:

```c
// PBx_pushed = 0: a gomb eddig nem volt lenyomva
// PBx_pushed = 1: a gomb le van nyomva, az esemény már le lett kezelve

// 1. lépés: Ha lenyomva érzékeljük ÉS még nem volt lekezelve → esemény!
if ((PINB & (1<<PB0)) == 0 && PB0_pushed == 0)
{
    szam1++;              // Esemény végrehajtása (csak egyszer!)
    PB0_pushed = 1;       // Jelöljük: a gomb le van nyomva
}

// 2. lépés: Ha felengedve érzékeljük ÉS le volt nyomva → reseteljük a jelzőt
if ((PINB & (1<<PB0)) == (1<<PB0) && PB0_pushed == 1) PB0_pushed = 0;
```

Ez egy kétállapotú **állapotgép**: `nem nyomott (0)` ↔ `nyomott (1)`. A timer 10 ms-os ütemével kombinálva elegendő prellszűrést biztosít.

#### Korlátok: Miért nem alkalmas ez az állapotgép a lenyomva tartás időtartamának mérésére?

Gyakori igény, hogy egy gomb lenyomásakor más esemény történjen rövid gombnyomásra (pl. +1 érték), és más hosszú lenyomásra (pl. más funkció, vagy az érték folyamatos pörgetése).

Ez az egyszerű állapotgép **önmagában nem alkalmas** a lenyomva tartott időtartam mérésére, mert **élvezérelt (edge-triggered)** módon működik:
- A gombnyomáshoz tartozó kód (pl. `szam1++`) **csak egyszer fut le**: pontosan abban a pillanatban, amikor élváltás történik (a gombot megnyomjuk, azaz a jelző `0`-ról `1`-re vált).
- Ha a gombot folyamatosan lenyomva tartjuk, a `PB0_pushed == 0` feltétel már nem teljesül a következő ciklusokban, így a program semmit nem csinál, hiába érzékeli folyamatosan a lenyomott állapotot.
- Nincs semmilyen változó, ami mérné vagy számon tartaná az idő múlását a lenyomás óta.

**Hogyan lehetne mégis mérni a lenyomva tartás idejét?**
Ki kell venni a perllenentés elleni védelmet az if feltételekből. A lenyomott gombok számláló változóját növelni kell minden ciklusban amíg a gomb le van nyomva. Amikor a gomb felenged, eldönthetjük a kívánt működést a számláló értékéből (pl. ha a számláló elérte az 50-et, az $50 \times 10\text{ ms} = 500\text{ ms}$ lenyomva tartást jelent).

---

### A `switch-case` utasítás

A `switch-case` több lehetséges értékre ágaztatja el a végrehajtást – olvashatóbb alternatíva a sok egymásba ágyazott `if-else if` helyett:

```c
switch (valtozo)
{
    case ERTEK1:
    {
        // Ez fut le, ha valtozo == ERTEK1
        break;   // Kilépés a switch-ből – kötelező, különben "átesel" a következőre!
    }
    case ERTEK2:
    {
        // Ez fut le, ha valtozo == ERTEK2
        break;
    }
    default:
    {
        // Ez fut le, ha egyik case sem illett – opcionális
        break;
    }
}
```

> **Fontos:** A `break` elhagyása esetén a program a következő `case` ágba is „átesel" (fall-through). Ez néha szándékos, de általában hibát okoz!

---

### Nibble – félbájt

Egy **nibble** = **4 bit** = egy hexadecimális jegy (0–F = 0–15).

Ebben a feladatban `szam1` és `szam2` is 4 bites értékek (0–15). A `PORTD` regiszteren egyszerre jelenítjük meg mindkettőt: `szam1` az alacsony nibble (bit 3–0), `szam2` a magas nibble (bit 7–4):

```
PORTD = szam1 | (szam2 << 4)

Példa: szam1 = 3 (0b0011), szam2 = 5 (0b0101)
  szam2 << 4  = 0b01010000
  szam1       = 0b00000011
  PORTD       = 0b01010011  →  LED-ek: [0101][0011] = 5 és 3
```

---

### Osztás nullával – potenciális veszély

> ⚠️ **Kritikus hiba:** Ha `szam2 == 0` és a kiválasztott művelet `OSZTAS`, a program **nullával osztást** kísérel meg. Ez AVR-en nem vezet kivételhez (nincs FPU vagy trap), de **definiálatlan/váratlan eredményt** ad!

Valós rendszerben ezt mindig ellenőrizni kell:
```c
case OSZTAS:
{
    if (szam2 != 0)
        PORTA = szam1 / szam2;
    else
        PORTA = 0xFF;  // Hibajelzés: minden LED ég
    break;
}
```

---

## 1. Feladat: AVR Kalkulátor – gombok, prellentés, switch-case

**A hardver felépítése:**

| Port | Irány | Funkció |
|---|---|---|
| **PORTA** | Kimenet | Számítás **eredménye** (8 LED) |
| **PORTD** | Kimenet | `szam1` (bit 3–0) és `szam2` (bit 7–4) megjelenítése |
| **PORTE** | Kimenet | Aktív **művelet** jelzése (1 bit ég egyszerre) |
| **PF0–PF3** | Kimenet | Timer feladat LED-ek (10ms, 100ms, 500ms, 1s) |
| **PB0** | Bemenet (pull-up) | `szam1` növelése (+1) |
| **PB1** | Bemenet (pull-up) | `szam1` csökkentése (−1) |
| **PB2** | Bemenet (pull-up) | `szam2` növelése (+1) |
| **PB3** | Bemenet (pull-up) | `szam2` csökkentése (−1) |
| **PB4** | Bemenet (pull-up) | Következő **művelet** kiválasztása |

**A számok tartománya:** 0–15 (0x00–0x0F), körkörösen növekednek/csökkennek.

**Feladat:** Valósítsa meg a fenti kalkulátort AT90CAN128-on, a leírt portok és logika alapján!

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  /******************************************************************************
  * Include files
  ******************************************************************************/
  #include <avr/io.h>    // AVR port és regiszter definíciók
  #include <inttypes.h>  // uint8_t, uint16_t típusok

  /******************************************************************************
  * Macros
  ******************************************************************************/
  // A műveletek azonosítói: hatványai 2-nek, hogy biteltolással lehessen köztük váltani,
  // és a PORTE-n pontosan egy bit égjen az aktív műveletnél.
  #define OSSZEADAS  1   // 0b00000001 → PE0
  #define KIVONAS    2   // 0b00000010 → PE1
  #define OSZTAS     4   // 0b00000100 → PE2
  #define SZORZAS    8   // 0b00001000 → PE3

  /******************************************************************************
  * Global Variables
  ******************************************************************************/
  uint16_t timer_cnt = 0;
  uint8_t timer_task_10ms = 0, timer_task_100ms = 0,
          timer_task_500ms = 0, timer_task_1s = 0;

  // Gombprellentés jelzők: 0 = gomb szabad, 1 = gomb le van nyomva (esemény lekezelve)
  uint8_t PB0_pushed = 0, PB1_pushed = 0, PB2_pushed = 0,
          PB3_pushed = 0, PB4_pushed = 0;

  uint8_t szam1 = 0;          // 1. operandus (0–15)
  uint8_t szam2 = 0;          // 2. operandus (0–15)
  uint8_t muvelet = OSSZEADAS; // Aktív művelet (alapból összeadás)

  /******************************************************************************
  * Function:         void port_init(void)
  * Description:      I/O portok inicializálása
  * Input:            -
  * Output:           -
  * Notes:            PORTA, PORTD, PORTE: kimenetek (eredmény, számok, művelet)
  *                   PORTF PF0-PF3: timer jelző LED-ek
  *                   PORTB PB0-PB4: gombok (bemenet, pull-up)
  ******************************************************************************/
  void port_init(void)
  {
      // PORTA: mind kimenet – az eredményt mutatja 8 LED-del
      DDRA = 0xff;

      // PORTF PF0–PF3: kimenet, kezdetben HIGH (LED-ek égnek)
      // A (1<<PA0) stb. itt PF0-t jelenti (PA és PF konstansok értéke azonos: 0,1,2,3)
      DDRF  = (1<<PF3) | (1<<PF2) | (1<<PF1) | (1<<PF0);
      PORTF = (1<<PF3) | (1<<PF2) | (1<<PF1) | (1<<PF0);

      // PORTB PB0–PB4: mind bemenet, belső pull-up engedélyezve
      // (0<<PBx) mindig 0, DDRB = 0x00 eredménye – bemenetek maradnak
      DDRB  = (0<<PB4) | (0<<PB3) | (0<<PB2) | (0<<PB1) | (0<<PB0);
      PORTB = (1<<PB4) | (1<<PB3) | (1<<PB2) | (1<<PB1) | (1<<PB0); // pull-up

      // PORTD: kimenet – szam1 (bit3–0) és szam2 (bit7–4) egy nibble-pár
      DDRD = 0xff;

      // PORTE: kimenet – az aktív műveletet jelzi (1 bit ég)
      DDRE = 0xff;
  }

  /******************************************************************************
  * Function:         void timer_init(void)
  * Description:      Timer0 inicializálása CTC módban, ~10 ms periódussal
  * Input:            -
  * Output:           -
  * Notes:            f_cpu = 8 MHz, N = 1024 (CS=101), OCR0 = 77
  *                   T_match = (77+1)*1024/8 000 000 ≈ 10 ms
  ******************************************************************************/
  void timer_init(void)
  {
      // WGM01=1, WGM00=0 → CTC mód
      // CS02=1, CS01=0, CS00=1 → prescaler 1024 (CS=101, lásd datasheet Table 12-5)
      TCCR0 = (0<<WGM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
      OCR0 = 77;
  }

  /******************************************************************************
  * Function:         uint8_t check_timer_compare(void)
  * Description:      Timer0 compare flag lekérdezése és törlése
  * Input:            -
  * Output:           1 ha az OCF0 flag be van állva (10 ms eltelt), 0 ha nem
  * Notes:            Flag törlése 1-es írásával történik (AVR sajátosság!)
  ******************************************************************************/
  uint8_t check_timer_compare(void)
  {
      if ((TIFR & (1<<OCF0)) == (1<<OCF0))
      {
          TIFR = TIFR | (1<<OCF0); // Flag törlése 1 írásával
          return 1;
      }
      return 0;
  }

  /******************************************************************************
  * Function:         int main(void)
  * Description:      Főprogram – AVR kalkulátor, nem blokkoló feladatütemezővel
  * Input:            -
  * Output:           -
  * Notes:            -
  ******************************************************************************/
  int main(void)
  {
      port_init();
      timer_init();

      while (1)
      {
          // Timer ütem feldolgozása – minden ~10 ms-ban fut le egyszer
          if (check_timer_compare())
          {
              timer_cnt++;
              if ((timer_cnt % 1)   == 0) timer_task_10ms  = 1;
              if ((timer_cnt % 10)  == 0) timer_task_100ms = 1;
              if ((timer_cnt % 50)  == 0) timer_task_500ms = 1;
              if ((timer_cnt % 100) == 0) timer_task_1s    = 1;
          }

          // ────────────────────────────────────────────────────────────────────
          // 10 ms-os feladat: gombok olvasása, számítás, kijelzés
          // ────────────────────────────────────────────────────────────────────
          if (timer_task_10ms)
          {
              // PF0 toggle: vizuális visszajelzés, hogy a 10ms task fut
              PORTF ^= (1<<PF0);

              // --- PB0: szam1 növelése ---
              // Ha a gomb lenyomva (LOW) ÉS még nem volt lekezelve:
              if ((PINB & (1<<PB0)) == 0 && PB0_pushed == 0)
              {
                  szam1++;
                  if (szam1 > 0x0F) szam1 = 0;  // Túlcsordulás: 16 → 0
                  PB0_pushed = 1;                 // Jelöljük: esemény lekezelve
              }
              // Ha a gomb felengedve (HIGH) ÉS korábban le volt nyomva → reset
              if ((PINB & (1<<PB0)) == (1<<PB0) && PB0_pushed == 1) PB0_pushed = 0;

              // --- PB1: szam1 csökkentése ---
              if ((PINB & (1<<PB1)) == 0 && PB1_pushed == 0)
              {
                  szam1--;
                  // uint8_t alulcsordulás: 0 - 1 = 255 (0xFF), vissza kell állítani 15-re
                  if (szam1 == 255) szam1 = 0x0F;
                  PB1_pushed = 1;
              }
              if ((PINB & (1<<PB1)) == (1<<PB1) && PB1_pushed == 1) PB1_pushed = 0;

              // --- PB2: szam2 növelése ---
              if ((PINB & (1<<PB2)) == 0 && PB2_pushed == 0)
              {
                  szam2++;
                  if (szam2 > 0x0F) szam2 = 0;
                  PB2_pushed = 1;
              }
              if ((PINB & (1<<PB2)) == (1<<PB2) && PB2_pushed == 1) PB2_pushed = 0;

              // --- PB3: szam2 csökkentése ---
              if ((PINB & (1<<PB3)) == 0 && PB3_pushed == 0)
              {
                  szam2--;
                  if (szam2 == 255) szam2 = 0x0F;
                  PB3_pushed = 1;
              }
              if ((PINB & (1<<PB3)) == (1<<PB3) && PB3_pushed == 1) PB3_pushed = 0;

              // --- PB4: következő művelet kiválasztása ---
              if ((PINB & (1<<PB4)) == 0 && PB4_pushed == 0)
              {
                  // Biteltolással váltunk a műveletek közt: 1 → 2 → 4 → 8 → 1
                  muvelet = muvelet << 1;
                  if (muvelet > 8) muvelet = 1; // Körbe: SZORZAS (8) után OSSZEADAS (1)
                  PB4_pushed = 1;
              }
              if ((PINB & (1<<PB4)) == (1<<PB4) && PB4_pushed == 1) PB4_pushed = 0;

              // --- Kijelzés frissítése ---
              // PORTD: szam1 a low nibble-ben (bit3–0), szam2 a high nibble-ben (bit7–4)
              PORTD = szam1 | (szam2 << 4);
              // PORTE: az aktív műveletnél pontosan egy bit ég
              PORTE = muvelet;

              // --- Számítás és eredmény megjelenítése ---
              switch (muvelet)
              {
                  case OSSZEADAS:
                  {
                      PORTA = szam1 + szam2;
                      break;
                  }
                  case KIVONAS:
                  {
                      PORTA = szam1 - szam2;
                      break;
                  }
                  case SZORZAS:
                  {
                      PORTA = szam1 * szam2;
                      break;
                  }
                  case OSZTAS:
                  {
                      // Nullával osztás elkerülése! Ha szam2 == 0, hibát jelzünk.
                      if (szam2 != 0)
                          PORTA = szam1 / szam2;
                      else
                          PORTA = 0xFF; // Hibajelzés: minden LED ég
                      break;
                  }
              }

              timer_task_10ms = 0; // Jelző törlése – következő ütemig ne fusson le újra
          }

          // 100 ms-os feladat: PF1 toggle
          if (timer_task_100ms)
          {
              PORTF ^= (1<<PF1);
              timer_task_100ms = 0;
          }

          // 500 ms-os feladat: PF2 toggle
          if (timer_task_500ms)
          {
              PORTF ^= (1<<PF2);
              timer_task_500ms = 0;
          }

          // 1 s-os feladat: PF3 toggle
          if (timer_task_1s)
          {
              PORTF ^= (1<<PF3);
              timer_task_1s = 0;
          }
      }
  }

  /******************************************************************************
  * Interrupt Routines
  ******************************************************************************/
  // (Ebben a feladatban nincsenek megszakítások – polling alapú timer kezelés)
  ```

  A rendszer működési logikája

  ```
  Gomb PB4 lenyomva → muvelet <<= 1 → ha > 8: vissza 1-re
  
  muvelet:  1 → 2 → 4 → 8 → 1 → ...
            +   -   /   *
  
  PORTA = szam1 [művelet] szam2   (8 LED mutatja az eredményt)
  PORTD = [szam2 (4 bit)][szam1 (4 bit)]
  PORTE = [0][0][0][0][szorzas][osztas][kivonas][osszeadas]
            ← csak 1 bit ég egyszerre →
  ```

  Alulcsordulás kezelése (uint8_t)

  ```
  szam1 típusa: uint8_t → értékkészlet: 0–255
  
  Ha szam1 = 0 és levonjuk 1-et:
    0 - 1 = -1 → de uint8_t-ben: 255 (0xFF)!  ← alulcsordulás
  
  Ezért ellenőrizzük: if (szam1 == 255) szam1 = 0x0F;
  → visszaállítjuk 15-re (a max. engedett értékre)
  ```

</details>

---

## Ellenőrző kérdések

1. Mi az előnye annak, hogy a műveletek értékei hatványai 2-nek (1, 2, 4, 8)? Hogyan működne a váltás, ha 1, 2, 3, 4 értékeket használnánk?
2. Miért kell a `PINx` regiszterből olvasni a bemeneti lábak állapotát, nem a `PORTx`-ből?
3. Mit jelent az „aktív LOW" logika? Miért előnyös pull-up ellenállással bekötni a nyomógombokat?
4. Mi történik, ha a prellentés kezelő kódból elhagyjuk a `PB0_pushed = 1;` sort?
5. Mi az a nibble? Hogyan kerül a `szam2` értéke a `PORTD` felső 4 bitjébe?
6. Miért veszélyes a `szam1 / szam2` kifejezés ellenőrzés nélkül? Hogyan kezeltük ezt a megoldásban?
7. Mi történne, ha a `switch` blokkból elhagynánk az egyik `break;` utasítást?
8. Miért nem alkalmas a fenti egyszerű állapotgépes gombkezelés a gomb lenyomva tartási idejének (pl. hosszú gombnyomás) mérésére? Hogyan kellene kiegészíteni a működést, hogy erre is alkalmas legyen?

