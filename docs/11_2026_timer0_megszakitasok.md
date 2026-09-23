---
layout: default
title: 2026/27 - 1. Gyakorlat - Timer0 és megszakítások
nav_order: 11
---

# 2026/27 - 1. Gyakorlat: Megszakítások, Timer0 és ciklikus feladatok
{: .no_toc }

A gyakorlat célja a megszakítások működésének megértése, majd egy körülbelül 10 ms-os hardveres időalap és egy egyszerű ciklikus feladatütemező elkészítése az **AT90CAN128** mikrovezérlőn. A példák **8 MHz-es CPU-órajellel** számolnak.

A teljes mintaprogram letölthető innen: [2026_01_timer0_interrupt.c]({{ site.github.repository_url }}/blob/main/docs/code/2026_01_timer0_interrupt.c)

## Tartalomjegyzék
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## 1. Regiszterek és perifériák

A mikrovezérlőn belül két regisztercsoportot érdemes megkülönböztetni:

- a CPU 32 darab, 8 bites általános célú regiszterét az aritmetikai és logikai műveletekhez;
- a perifériák I/O-regisztereit a GPIO, a timer, az ADC, a kommunikációs egységek és más hardverblokkok beállításához.

A `DDRF`, `PORTF`, `TCCR0A`, `OCR0A` és `TIMSK0` tehát nem hagyományos programváltozók: meghatározott memóriacímekhez rendelt hardverregiszterek. A program ezeken keresztül konfigurálja a mikrovezérlőt.

### GPIO-emlékeztető

| Regiszter | Szerepe |
|---|---|
| `DDRx` | Adatirány: `0` = bemenet, `1` = kimenet |
| `PORTx` | Kimeneti érték, illetve bemenetnél a belső pull-up vezérlése |
| `PINx` | A lábak tényleges bemeneti állapotának olvasása |

Egy bit beállításához maszkolást használunk:

```c
DDRF |= (1u << PF0);    // PF0 kimenet
PORTF ^= (1u << PF0);   // csak PF0 állapotának invertálása
```

---

## 2. Blokkoló várakozás, polling és megszakítás

### Mi a gond a blokkoló várakozással?

```c
while (1)
{
    PORTF ^= (1u << PF0);
    _delay_ms(500);

    read_button();
    read_adc();
    send_can_message();
}
```

A CPU a késleltetés alatt nem jut el a további feladatokhoz. Ez egyszerű LED-villogtatásnál elfogadható lehet, több eltérő időzítésű vagy gyors reakciót igénylő feladatnál azonban már nem.

### Polling

Polling esetén a program rendszeresen megvizsgál egy állapotot:

```c
if (PINF & (1u << PF4))
{
    /* bemenet feldolgozása */
}
```

Az információáramlás: **CPU lekérdezi a perifériát**. A módszer egyszerű, de a programnak elég gyakran vissza kell térnie az ellenőrzéshez.

### Megszakítás

Megszakításnál egy perifériaesemény értesíti a CPU-t. A processzor rövid időre félreteszi a főprogramot, végrehajtja a megfelelő megszakításkezelő rutint, majd visszatér a megszakított kódhoz:

```text
main:  A -> B ---------> C -> D
                  |
                  +-> ISR -+
```

Ez nem párhuzamos végrehajtás. Az egymagos AT90CAN128-on egy adott pillanatban vagy a főprogram, vagy egy ISR fut.

---

## 3. ISR és megszakítási vektor

Az ISR az *Interrupt Service Routine*, vagyis megszakításkezelő rutin rövidítése. AVR-GCC alatt egy Timer0 Compare Match ISR:

```c
ISR(TIMER0_COMP_vect)
{
    /* a Timer0 eseményének kezelése */
}
```

A függvényt nem a `main()` hívja meg. A hardver a megszakítási vektor alapján adja át neki a vezérlést.

### Kétszintű engedélyezés

A Timer0 Compare Match megszakításhoz két feltételnek egyszerre kell teljesülnie:

```c
TIMSK0 |= (1u << OCIE0A);  // a konkrét Timer0 megszakításforrás
sei();                     // globális megszakításengedélyezés
```

Ha bármelyik hiányzik, a timer számlálhat és a Compare Match esemény is bekövetkezhet, de a CPU nem hajtja végre az ISR-t.

---

## 4. Timer0, előosztó és CTC mód

A Timer0 egy 8 bites hardveres számláló, ezért a számlálási tartománya `0...255`. A számláló órajele a CPU-órajelből és az előosztóból adódik:

```text
f_timer = f_CPU / N
```

8 MHz-es CPU-órajel és `N = 1024` előosztó esetén:

```text
f_timer = 8 000 000 / 1024 = 7812,5 Hz
T_tick  = 1 / 7812,5       = 128 us
```

### CTC - Clear Timer on Compare Match

CTC módban a számláló nullától az `OCR0A` regiszter értékéig halad. Egyezéskor Compare Match esemény keletkezik, majd a számláló újraindul nulláról.

```text
0, 1, 2, ..., OCR0A -> Compare Match -> 0, 1, 2, ...
```

A periódusidő:

```text
T_interrupt = N * (OCR0A + 1) / f_CPU
```

A `+1` azért szükséges, mert a számlálás nulláról indul. `OCR0A = 77` esetén 78 timerütem telik el:

```text
T_interrupt = 1024 * (77 + 1) / 8 000 000 = 9,984 ms
f_interrupt = 1 / 9,984 ms                 = 100,16 Hz
```

Ez a gyakorlatban megfelelő közelítése a 10 ms-os alapidőnek.

### Timer0 inicializálása

```c
static void timer_init(void)
{
    TCCR0A = (1u << WGM01) |  // CTC mód
             (1u << CS02)  |  // előosztó: 1024
             (1u << CS00);

    OCR0A = 77u;
    TIMSK0 |= (1u << OCIE0A);
}
```

---

## 5. Első feladat - Timer0-megszakítással vezérelt kimenet

**Feladat:** állítsa PF0-t kimenetnek, konfigurálja a Timer0-t körülbelül 10 ms-os Compare Match időre, majd minden megszakításkor invertálja PF0 állapotát.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  #include <avr/io.h>
  #include <avr/interrupt.h>

  #define F_CPU 8000000UL

  static void timer_init(void)
  {
      TCCR0A = (1u << WGM01) |
               (1u << CS02)  |
               (1u << CS00);
      OCR0A = 77u;
      TIMSK0 |= (1u << OCIE0A);
  }

  int main(void)
  {
      DDRF |= (1u << PF0);
      timer_init();
      sei();

      while (1)
      {
          /* A PF0-t nem a főciklus módosítja. */
      }
  }

  ISR(TIMER0_COMP_vect)
  {
      PORTF ^= (1u << PF0);
  }
  ```

  Az ISR 9,984 ms-onként invertálja a lábat. Egy teljes négyszögjel-periódushoz két invertálás kell, ezért a PF0 kimenet frekvenciája körülbelül 50,08 Hz.
</details>

---

## 6. Miért legyen rövid az ISR?

Az ISR futása alatt a főprogram szünetel, és más megszakítások kiszolgálása is késhet. Ezért a jó alapszabály:

> **Az ISR jelez vagy ütemez; a `main()` végzi az alkalmazási feladatot.**

Egy jelzőváltozóval a Timer0 ISR csak eseményt jelez:

```c
volatile uint8_t timer_event = 0u;

ISR(TIMER0_COMP_vect)
{
    timer_event = 1u;
}
```

A főprogram végzi a tényleges műveletet:

```c
if (timer_event)
{
    timer_event = 0u;
    PORTF ^= (1u << PF0);
}
```

### Miért `volatile`?

Az ISR a `main()` normál végrehajtási folyamán kívül is megváltoztathatja a változó értékét. A `volatile` megakadályozza, hogy a fordító ezt a hozzáférést tévesen változatlannak tekintse vagy kioptimalizálja.

A `volatile` azonban **nem jelent automatikus atomitást**, és nem old meg minden versenyhelyzetet. Itt a jelző 8 bites, ezért egy 8 bites AVR-en az egyszerű olvasása és írása egyetlen művelettel megoldható.

---

## 7. Ciklikus feladatok egyetlen időalapból

A 10 ms-os alapidőből szoftveres számlálóval több periódus állítható elő:

| Feladat | Aktiválás | Timerütemek száma |
|---|---:|---:|
| 10 ms | minden megszakításnál | 1 |
| 100 ms | minden 10. megszakításnál | 10 |
| 500 ms | minden 50. megszakításnál | 50 |
| 1 s | minden 100. megszakításnál | 100 |

```c
ISR(TIMER0_COMP_vect)
{
    timer_task_10ms = TRUE;
    timer_cnt++;

    if ((timer_cnt % 10u) == 0u)
        timer_task_100ms = TRUE;

    if ((timer_cnt % 50u) == 0u)
        timer_task_500ms = TRUE;

    if (timer_cnt >= 100u)
    {
        timer_task_1s = TRUE;
        timer_cnt = 0u;
    }
}
```

A főciklus minden jelzőhöz külön feladatot rendel, majd a végrehajtáskor törli a jelzőt.

<details markdown="1">
  <summary>A teljes megoldás megjelenítése</summary>

  ```c
  #include <avr/io.h>
  #include <avr/interrupt.h>
  #include <stdint.h>

  #define F_CPU 8000000UL
  #define TRUE  1u
  #define FALSE 0u

  volatile uint8_t timer_task_10ms  = FALSE;
  volatile uint8_t timer_task_100ms = FALSE;
  volatile uint8_t timer_task_500ms = FALSE;
  volatile uint8_t timer_task_1s    = FALSE;
  static uint8_t timer_cnt = 0u;

  static void port_init(void)
  {
      DDRF |= (1u << PF0) | (1u << PF1) |
              (1u << PF2) | (1u << PF3);
  }

  static void timer_init(void)
  {
      TCCR0A = (1u << WGM01) | (1u << CS02) | (1u << CS00);
      OCR0A = 77u;
      TIMSK0 |= (1u << OCIE0A);
  }

  int main(void)
  {
      port_init();
      timer_init();
      sei();

      while (1)
      {
          if (timer_task_10ms)
          {
              timer_task_10ms = FALSE;
              PORTF ^= (1u << PF0);
          }
          if (timer_task_100ms)
          {
              timer_task_100ms = FALSE;
              PORTF ^= (1u << PF1);
          }
          if (timer_task_500ms)
          {
              timer_task_500ms = FALSE;
              PORTF ^= (1u << PF2);
          }
          if (timer_task_1s)
          {
              timer_task_1s = FALSE;
              PORTF ^= (1u << PF3);
          }
      }
  }

  ISR(TIMER0_COMP_vect)
  {
      timer_task_10ms = TRUE;
      timer_cnt++;

      if ((timer_cnt % 10u) == 0u) timer_task_100ms = TRUE;
      if ((timer_cnt % 50u) == 0u) timer_task_500ms = TRUE;

      if (timer_cnt >= 100u)
      {
          timer_task_1s = TRUE;
          timer_cnt = 0u;
      }
  }
  ```
</details>

### A LED-jelek értelmezése

Minden feladat csak **invertálja** a kimenetet, ezért a LED-jel teljes periódusa kétszerese a feladat aktiválási periódusának.

| Kimenet | Feladat aktiválása | Kimeneti jel periódusa | Kimeneti frekvencia |
|---|---:|---:|---:|
| PF0 | kb. 10 ms | kb. 20 ms | kb. 50 Hz |
| PF1 | kb. 100 ms | kb. 200 ms | kb. 5 Hz |
| PF2 | kb. 500 ms | kb. 1 s | kb. 1 Hz |
| PF3 | kb. 1 s | kb. 2 s | kb. 0,5 Hz |

### A logikai feladatjelző korlátja

Ha a főprogram nem dolgozza fel időben az eseményt, két egymást követő `timer_task_10ms = TRUE` írásból továbbra is csak egyetlen `TRUE` érték marad. A logikai flag azt mutatja, hogy a feladat végrehajtásra vár, de nem tárolja az elmaradt aktiválások számát.

Az egyszerű megoldás ezért feltételezi, hogy a feladat futási ideje lényegesen kisebb a periódusidejénél. Ha minden eseményt meg kell őrizni, logikai jelző helyett számláló vagy eseménysor szükséges.

---

## Ellenőrző kérdések és további feladatok

1. Mi a különbség a polling és a megszakítás között?
2. Miért kell egyszerre az `OCIE0A` bit és a `sei()` hívás?
3. Miért szerepel `OCR0A + 1` a CTC-időzítés képletében?
4. Miért kell `volatile` minősítő az ISR és a főprogram között megosztott jelzőkhöz?
5. Számítsa ki az `OCR0A` értékét névleges 5 ms-os alapidőhöz 8 MHz és 1024-es előosztó mellett!
6. Egészítse ki a programot 20 ms-os, 200 ms-os és 250 ms-os feladatjelzővel!

<details markdown="1">
  <summary>Az 5 ms-os számítás ellenőrzése</summary>

  ```text
  OCR0A = T * f_CPU / N - 1
        = 0,005 * 8 000 000 / 1024 - 1
        = 38,0625
  ```

  A választható közeli egész érték `OCR0A = 38`, amellyel a tényleges periódus 4,992 ms.
</details>
