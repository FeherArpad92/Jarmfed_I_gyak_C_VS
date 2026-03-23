---
layout: default
title: 3. Gyakorlat - Pointerek
nav_order: 4
---

# 3. Gyakorlat: Pointerek
{: .no_toc }

A mai gyakorlat célja a C nyelv egyik legfontosabb és legösszetettebb témájának, a mutatóknak (pointereknek) a megismerése. A pointerek lehetővé teszik a memória közvetlen elérését, ami hatékony programozást tesz lehetővé, de egyben a hibák leggyakoribb forrása is. A feladatok során lépésről lépésre haladunk az egyszerű pointer deklarációtól a dinamikus memóriakezelésig.

## Elméleti háttér: Mi az a pointer?

Egy pointer (mutató) egy olyan változó, amely **nem egy értéket**, hanem egy **memóriacímet** tárol. Minden változó a számítógép memóriájában egy adott címen helyezkedik el, és a pointer éppen ezt a címet tárolja el.

Alapvető operátorok:
- `&` **(címképző operátor – „address-of"):** Egy változó memóriacímét adja vissza. Pl.: `&szam` → a `szam` változó memóriacíme.
- `*` **(dereferáló operátor – „dereference"):** A pointer által mutatott memóriacímen lévő értéket adja vissza. Pl.: `*ptr` → a `ptr` által mutatott cím tartalma.
- `*` **(deklarációban):** Jelzi, hogy a változó egy pointer típusú. Pl.: `int *ptr;` → `ptr` egy `int`-re mutató pointer.

## Tartalomjegyzék
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## 1. Pointer deklarálása és használata
**Feladat:** Deklaráljon egy egész számot, hozzon létre egy pointer-t rá, és írja ki mind a számot, mind a pointer által hivatkozott értéket.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>
  
  ```c
  #include <stdio.h>
  #include <inttypes.h>

  int main() {
      // Deklarálunk egy egész számot és értéket adunk neki
      int32_t szam = 42;
      
      // Pointer deklarálása: 'ptr' egy int32_t típusú változóra mutató pointer.
      // Az '&szam' a 'szam' változó memóriacímét adja vissza.
      int32_t *ptr = &szam;
      
      // A szám értékének kiírása közvetlenül
      printf("A szam erteke: %" PRId32 "\n", szam);
      
      // A pointer által mutatott érték kiírása a '*' (dereferáló) operátorral.
      // A '*ptr' azt jelenti: "olvasd ki az értéket arról a memóriacímről, amire ptr mutat."
      printf("A pointer altal mutatott ertek: %" PRId32 "\n", *ptr);
      
      // A pointer értékének (azaz a memóriacímnek) a kiírása.
      // A %p formátum a memóriacímek kiírására szolgál.
      printf("A szam memoriacime: %p\n", (void*)ptr);
      
      return 0;
  }
  ```
</details>

---

## 2. Pointer a pointerre (dupla pointer)
**Feladat:** Hozzon létre egy egész számot és egy pointert, amely erre mutat. Ezután módosítsa az egész szám értékét kizárólag a pointer segítségével, majd írja ki az eredményt. Végül hozzon létre egy másik pointert, amely az első pointer címére mutat (pointer a pointerre), és ezen keresztül módosítsa újra az egész szám értékét. Írja ki az eredményt minden lépés után.

### Elméleti háttér: Pointer a pointerre
Ahogy egy pointer egy változó memóriacímét tárolja, egy **dupla pointer** (`int **pp`) egy **pointer memóriacímét** tárolja. Ez azt jelenti, hogy a dupla pointeren keresztül két lépésben jutunk el az eredeti értékig:
1. `*pp` → az első pointer (amire a dupla pointer mutat)
2. `**pp` → az eredeti változó értéke (kétszeres dereferálás)

Ez a koncepció különösen fontos a dinamikus memóriakezelésnél és a függvényparaméter-átadásnál.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>
  
  ```c
  #include <stdio.h>
  #include <inttypes.h>

  int main() {
      // 1. lépés: Egész szám és pointer létrehozása
      int32_t szam = 10;
      int32_t *ptr = &szam; // ptr a 'szam' memóriacímére mutat
      
      printf("--- Kezdeti allapot ---\n");
      printf("szam erteke: %" PRId32 "\n", szam);
      printf("*ptr erteke (pointeren keresztul): %" PRId32 "\n", *ptr);
      
      // 2. lépés: Érték módosítása a pointeren keresztül.
      // A '*ptr = 20' azt jelenti: "írd a 20-as értéket arra a memóriacímre, amire ptr mutat."
      // Mivel ptr a 'szam'-ra mutat, ez közvetlenül a 'szam' értékét változtatja meg.
      *ptr = 20;
      
      printf("\n--- Modositas pointeren keresztul (*ptr = 20) ---\n");
      printf("szam erteke: %" PRId32 "\n", szam);
      printf("*ptr erteke: %" PRId32 "\n", *ptr);
      
      // 3. lépés: Dupla pointer (pointer a pointerre) létrehozása.
      // 'pp' egy int32_t** típusú változó, ami a 'ptr' memóriacímét tárolja.
      // Tehát: pp -> ptr -> szam
      int32_t **pp = &ptr;
      
      // Kétszeres dereferálás: **pp először a ptr-t kapja meg (*pp == ptr),
      // majd onnan az eredeti szam értékét (**pp == *ptr == szam).
      **pp = 30;
      
      printf("\n--- Modositas dupla pointeren keresztul (**pp = 30) ---\n");
      printf("szam erteke: %" PRId32 "\n", szam);
      printf("*ptr erteke: %" PRId32 "\n", *ptr);
      printf("**pp erteke: %" PRId32 "\n", **pp);
      
      return 0;
  }
  ```
</details>

---

## 3. Dinamikus memóriakezelés
**Feladat:** Kérjen be egy pozitív egész számot a felhasználótól. Allokáljon dinamikusan egy egész szám tömböt a megadott mérettel, majd olvasson be értékeket és tárolja el őket a tömbben. Használjon pointereket a dinamikus memória kezelésére.

### Elméleti háttér: A `malloc` és a `free`
Eddig a tömbjeinket mindig fix mérettel deklaráltuk (pl. `int tomb[5]`). De mi van, ha a program futása közben derül ki, hogy mekkora tömbre van szükség? Ilyenkor **dinamikus memóriafoglalást** használunk.

- **`malloc(meret)`**: A `stdlib.h`-ban definiált függvény, amely a megadott bájtmennyiséget foglalja le a memóriában (heap), és egy `void*` típusú pointert ad vissza a lefoglalt terület elejére. A `void*`-ot típuskonverzióval (cast) alakítjuk a kívánt típusra.
- **`free(ptr)`**: Felszabadítja a korábban `malloc`-kal lefoglalt memóriát. **Kritikus fontosságú**: ha nem szabadítjuk fel, a program „memória-szivárgást" (memory leak) okoz, ami hosszú futás esetén az összes rendelkezésre álló memóriát felemésztheti.
- **`sizeof(típus)`**: Megadja egy adott típus méretét bájtokban, ami fontos a helyes memóriamennyiség kiszámításához.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>
  
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <inttypes.h>

  int main() {
      uint16_t meret;
      
      printf("Hany elemet szeretne tarolni? ");
      scanf("%hu", &meret);
      
      // Dinamikus memóriafoglalás: a malloc lefoglal 'meret' darab int32_t méretű blokkot a heap-en.
      // A (int32_t*) típuskényszerítés (cast) szükséges, mert a malloc void*-ot ad vissza.
      int32_t *tomb = (int32_t*)malloc(meret * sizeof(int32_t));
      
      // Fontos ellenőrizni, hogy a malloc sikeres volt-e!
      // Ha nincs elég memória, a malloc NULL pointert ad vissza.
      if (tomb == NULL) {
          printf("Memoriafoglalas sikertelen!\n");
          return 1; // Kilépés hibakóddal
      }
      
      // Értékek beolvasása: a 'tomb' pointert használjuk index operátorral (tomb[i]),
      // ami valójában pointer-aritmetika: *(tomb + i)
      printf("Kerem adja meg az elemeket:\n");
      for (uint16_t i = 0; i < meret; i++) {
          printf("  %u. elem: ", i + 1);
          scanf("%" SCNd32, &tomb[i]);
      }
      
      // Tárolt értékek kiírása
      printf("\nA tarolt ertekek:\n");
      for (uint16_t i = 0; i < meret; i++) {
          printf("  tomb[%u] = %" PRId32 "\n", i, tomb[i]);
      }
      
      // A dinamikusan foglalt memória felszabadítása.
      // Ha ezt elmulasztjuk, memória-szivárgás (memory leak) keletkezik!
      free(tomb);
      
      // Jó szokás a pointer NULL-ra állítása felszabadítás után,
      // hogy elkerüljük a "dangling pointer" (érvénytelen mutatójú pointer) hibákat.
      tomb = NULL;
      
      return 0;
  }
  ```
</details>

---

## 4. Karakterlánc hosszának meghatározása pointerrel
**Feladat:** Számolja meg, hány karakterből áll egy konstans karakterláncból felépített szöveg. Használjon pointereket a karakterlánc kezelésére.

### Elméleti háttér: Stringek és pointerek
C-ben a stringek valójában karaktertömbök (`char[]`), amelyek egy **nullakarakterrel** (`'\0'`) végződnek. Egy `char*` típusú pointer a string első karakterére mutat, és a pointer léptetésével (`ptr++`) egyenként bejárhatjuk a string összes karakterét egészen a lezáró `'\0'`-ig.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>
  
  ```c
  #include <stdio.h>
  #include <inttypes.h>

  /******************************************************************************
  * Function:         uint16_t stringHossz(const char *str)
  * Description:      Karakterlánc hosszának meghatározása pointerrel
  * Input:            str: a lezáró nullakarakterrel végződő karakterlánc
  * Output:           A string hossza (a lezáró '\0' nélkül)
  * Notes:            A 'const' kulcsszó biztosítja, hogy a függvény nem módosítja
  *                   az eredeti stringet, csak olvassa azt.
  ******************************************************************************/
  uint16_t stringHossz(const char *str) {
      uint16_t hossz = 0;
      
      // A pointer léptetésével haladunk végig a stringen.
      // Ameddig a pointer által mutatott karakter nem a lezáró nullakarakter ('\0'),
      // addig növeljük a számlálót és léptetjük a pointert a következő karakterre.
      while (*str != '\0') {
          hossz++;   // Számláló növelése
          str++;     // Pointer léptetése a következő karakterre (pointer aritmetika)
      }
      
      return hossz;
  }

  int main() {
      // A 'const' kulcsszó jelzi, hogy ez a string nem módosítható.
      // A fordító a stringet a memória csak olvasható (read-only) szegmensébe helyezi.
      const char *szoveg = "Hello, Pointer Vilag!";
      
      // A függvénynek a string első karakterének a memóriacímét (azaz magát a pointert) adjuk át.
      uint16_t hossz = stringHossz(szoveg);
      
      printf("A szoveg: \"%s\"\n", szoveg);
      printf("A szoveg hossza: %" PRIu16 " karakter\n", hossz);
      
      return 0;
  }
  ```
</details>
