---
layout: default
title: 4. Gyakorlat - C szabványos könyvtárak
nav_order: 5
---

# 4. Gyakorlat: C szabványos könyvtárak
{: .no_toc }

A mai gyakorlat célja a C programozási nyelv legfontosabb szabványos könyvtárfüggvényeinek megismerése. A szabványos könyvtár (Standard Library) kész, tesztelt és optimalizált megoldásokat kínál a leggyakoribb programozási feladatokra, mint például sztringkezelés és matematikai számítások.

## Elméleti háttér: A fontosabb könyvtárak

A mai feladatokhoz szükséges fejlécfájlok:

| Fejlécfájl | Tartalom |
|---|---|
| `<string.h>` | Sztringkezelő függvények: `strcpy`, `strcat`, `strlen`, `strcmp`, … |
| `<math.h>` | Matematikai függvények: `sqrt`, `pow`, `sin`, `cos`, `tan`, `M_PI`, … |
| `<stdio.h>` | Be- és kimenet: `printf`, `scanf`, … |
| `<inttypes.h>` | Platformfüggetlen egész típusok: `int32_t`, `uint16_t`, … |

> **Fontos:** A `<math.h>` könyvtár függvényeinek `double` típusú paraméterek kellenek és `double` típusú értékkel térnek vissza. A `double` egy **dupla pontosságú lebegőpontos szám** (64 bites, kb. 15-16 tizedesjegy pontossággal). Linkeléskor (fordításkor) néha szükséges a `-lm` flag: `gcc main.c -lm -o main`.

## Tartalomjegyzék
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## 1. Sztring másolása (`strcpy`)
**Feladat:** Készítsen egy programot, amely bemásol egy stringet egy másik stringbe a `strcpy` függvény használatával, majd kiírja az eredményt.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
      // A forrás string, amelynek tartalmát másolni fogjuk.
      // A 'const' jelzi, hogy ez nem kerül módosításra.
      const char forras[] = "Hello, szabvanyos konyvtar!";
      
      // A cél puffer, amelybe másolunk.
      // Fontos: legalább akkora legyen, mint a forrás string (beleértve a '\0' lezárót)!
      char cel[50];
      
      // Az strcpy(cel, forras) a forras tartalmát (a lezáró '\0'-val együtt)
      // átmásolja a cel tömbbe.
      strcpy(cel, forras);
      
      printf("Forras string: %s\n", forras);
      printf("Cel string (masolas utan): %s\n", cel);
      
      // Ellenőrzés: az strcpy után a két tömb tartalma azonos kell legyen.
      // Az strcmp 0-t ad vissza, ha a két string azonos.
      if (strcmp(forras, cel) == 0) {
          printf("A masolas sikeres: a ket string azonos.\n");
      }
      
      return 0;
  }
  ```
</details>

---

## 2. Sztringek összefűzése (`strcat`)
**Feladat:** Kérjen be két stringet a felhasználótól, majd használja a `strcat` függvényt a két string összefűzésére, majd írja ki az eredményt.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  A feladatot előre definiált stringekkel oldjuk meg, hogy a beginner és a haladó kód egyaránt könnyen követhető legyen.

  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
      // Az első string: elegendő helyet kell hagyni a második fűzéséhez!
      // Az fűzés az első stringbe (cel) dolgozik bele, ezért elég nagynak kell lennie.
      // A sizeof az egész tömb méretét adja meg bájtban,
      // a strlen(cel) pedig az aktuálisan benne lévő szöveg karaktereinek számát.
      char elso[100] = "Hello, ";
      const char masodik[] = "Vilag!";
      
      printf("Elso string: \"%s\"\n", elso);
      printf("Masodik string: \"%s\"\n", masodik);
      
      // Az strcat(elso, masodik) a masodik tartalmát az elso VÉGÉHEZ fűzi hozzá.
      // Felülírja az elso lezáró '\0' karakterét, és a végén újat tesz.
      // Feltétel: az elso tömbnek elegendő szabad hellyel kell rendelkeznie!
      strcat(elso, masodik);
      
      printf("Összefuzott string: \"%s\"\n", elso);
      printf("Az eredmeny hossza: %zu karakter\n", strlen(elso));
      
      return 0;
  }
  ```
</details>

---

## 3. Négyzetgyök kiszámítása (`sqrt`)
**Feladat:** Írjon egy programot, amely bekér a felhasználótól egy pozitív számot, majd használja a `sqrt` függvényt a négyzetgyök kiszámítására és az eredmény kiírására.

### Elméleti háttér: `double` típus és a `<math.h>`
A `sqrt` (square root = négyzetgyök) a `<math.h>` könyvtárban található. `double` típusú paramétert vár és `double`-lal tér vissza. A `%f` formátumspecifikátor a `printf`-ben `double` értéket ír ki, míg a `scanf`-ben a `double`-höz `%lf`-et kell használni.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  #include <stdio.h>
  #include <math.h>

  int main() {
      double szam;
      
      printf("Adjon meg egy pozitiv szamot: ");
      // A double tipusu valtozokhoz scanf-ben a %lf formatumot kell hasznalni!
      scanf("%lf", &szam);
      
      // Ellenorzés: a negyzetgyok csak nem negativ szamoknal ertelmezett.
      if (szam < 0.0) {
          printf("Hiba: negativ szam negyzetgyoke nem szamithato!\n");
          return 1;
      }
      
      // Az sqrt() a parameter negyzetgyoket adja vissza double tipusként.
      double gyok = sqrt(szam);
      
      // %.4f: lebegoponton szam kiirasa 4 tizedesjegy pontossaggal
      printf("A szam: %.4f\n", szam);
      printf("A szam negyzetgyoke: %.4f\n", gyok);
      
      // Ellenorzes: gyok*gyok visszaadja az eredeti szamot
      printf("Ellenorzes: %.4f^2 = %.4f\n", gyok, gyok * gyok);
      
      return 0;
  }
  ```
</details>

---

## 4. Hatványozás (`pow`)
**Feladat:** Kérjen be egy alapot és egy kitevőt a felhasználótól, majd használja a `pow` függvényt az alap kitevőre emeléséhez, majd írja ki az eredményt.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  #include <stdio.h>
  #include <math.h>

  int main() {
      double alap, kitevo;
      
      printf("Adja meg az alapot: ");
      scanf("%lf", &alap);
      
      printf("Adja meg a kitevot: ");
      scanf("%lf", &kitevo);
      
      // A pow(alap, kitevo) kiszamitja az alap^kitevo erteket.
      // Mindket parametere double, es double-lal ter vissza.
      double eredmeny = pow(alap, kitevo);
      
      printf("%.2f ^ %.2f = %.2f\n", alap, kitevo, eredmeny);
      
      return 0;
  }
  ```
</details>

---

## 5. Pi szám (`M_PI`)
**Feladat:** Használja a `M_PI` konstans értékét a `math.h` könyvtárból a pi szám kiírására.

### Elméleti háttér: Konstansok a `<math.h>`-ban
A `M_PI` egy előre definiált makró a `<math.h>` fejlécben, amely a π (pi) értékét tárolja `double` pontossággal. Hasonló konstansok: `M_E` (Euler-szám, e≈2.718), `M_SQRT2` (√2≈1.414).

> **Megjegyzés:** A `M_PI` technikailag POSIX bővítmény, nem szorosan szabványos C. Néhány fordítón a `#define _USE_MATH_DEFINES` makró előzetes definiálása szükséges (elsősorban MSVC-n, Visual Studio alatt).

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  #define _USE_MATH_DEFINES  // Visual Studio (MSVC) alatt szükséges a M_PI-hoz
  #include <stdio.h>
  #include <math.h>

  int main() {
      // Az M_PI a math.h-ban definiált double pontosságú pi konstans (~3.14159265358979...)
      printf("Pi erteke: %f\n", M_PI);
      
      // Különböző pontosságú kiírások
      printf("Pi 2 tizedessel:  %.2f\n", M_PI);
      printf("Pi 6 tizedessel:  %.6f\n", M_PI);
      printf("Pi 15 tizedessel: %.15f\n", M_PI);
      
      // Euler-szám és gyök(2) kiírása ugyanabból a fejlécből
      printf("\nEuler-szam (e): %.10f\n", M_E);
      printf("Gyok(2):        %.10f\n", M_SQRT2);
      
      return 0;
  }
  ```
</details>

---

## 6. Szinusz, koszinusz, tangens (`sin`, `cos`, `tan`)
**Feladat:** Készítsen egy programot, amely bekér egy szög értékét fokban, majd használja a `sin`, `cos` és `tan` függvényeket a szög szinusz, koszinusz és tangens értékeinek kiszámítására, majd írja ki azokat.

### Elméleti háttér: Radiáns vs. Fok
A `sin()`, `cos()` és `tan()` függvények **radiánban** várják a szög értékét, nem fokokban. Az átváltás képlete:

**radiáns = fok × (π / 180)**

Egy teljes kör = 360° = 2π radiáns.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  ```c
  #define _USE_MATH_DEFINES
  #include <stdio.h>
  #include <math.h>

  int main() {
      double fokban;
      
      printf("Adja meg a szog erteket fokban: ");
      scanf("%lf", &fokban);
      
      // Ataltas fokbol radianba a sin/cos/tan fuggvenyek szamara.
      // M_PI / 180.0 az ataltas szorzoja: 1 fok = M_PI/180 radian.
      double radiansban = fokban * (M_PI / 180.0);
      
      printf("Szog: %.1f fok (%.6f rad)\n\n", fokban, radiansban);
      
      // Szinusz, koszinusz es tangens kiszamitasa
      double sz = sin(radiansban);
      double k  = cos(radiansban);
      double t  = tan(radiansban);
      
      printf("sin(%.1f fok) = %.6f\n", fokban, sz);
      printf("cos(%.1f fok) = %.6f\n", fokban, k);
      printf("tan(%.1f fok) = %.6f\n", fokban, t);
      
      // Ellenorzes: sin^2(theta) + cos^2(theta) = 1 (Pitagorasz-tetel egysegkoron)
      double ellenorzes = sz * sz + k * k;
      printf("\nEllenorzes (sin^2 + cos^2 = 1): %.10f\n", ellenorzes);
      
      return 0;
  }
  ```
</details>
