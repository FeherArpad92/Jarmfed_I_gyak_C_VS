---
layout: default
title: 2. Gyakorlat - Függvények
nav_order: 3
---

# 2. Gyakorlat: Függvények
{: .no_toc }

A mai gyakorlat célja a C programozási nyelv függvényeinek megismerése és használatuk gyakorlása. A feladatok során különböző típusú, paraméterezésű és visszatérési értékű függvényeket kell elkészíteni. A teljes megoldás letölthető innen: [main.c]({{ site.github.repository_url }}/blob/main/2_fuggvenyek/main.c)

## Tartalomjegyzék
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## 1. Tömb átlagának kiszámítása
**Feladat:** Írjon egy függvényt, amely egy számokból álló tömböt kap meg, majd kiszámítja a számok átlagát. Írjon egy programot, amely használja ezt a függvényt egy tetszőleges számokból álló tömbre.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>
  
  ```c
  #include <stdio.h>
  #include <inttypes.h>

  /******************************************************************************
  * Function:         float atlag(uint16_t tomb[], uint8_t meret)
  * Description:      Átlag számítása
  * Input:            szamokat tartalmazó tömb, tömb mérete
  * Output:           a számok átlaga
  * Notes:            Fontos: C-ben a tömb méretét is át kell adni paraméterként!
  ******************************************************************************/
  float atlag(uint16_t tomb[], uint8_t meret)
  {
      // A kezdő összeg 0. Fontos az inicializálás, mert memóriaszemetet tartalmazhatna.
      uint16_t osszeg = 0;
      
      // Végigmegyünk a tömb elemein 0-tól (meret-1)-ig.
      for (uint8_t i = 0; i < meret; i++)
        osszeg += tomb[i]; // Hozzáadjuk az aktuális elemet az összeghez
        
      // A visszatérési érték kiszámításánál float-tá alakítjuk (típuskonverzió/cast),
      // hogy ne egész osztást végezzen a gép, hanem megtartsa a tizedeseket.
      return (float)osszeg / (float)meret;
  }

  int main() {
      // Deklarálunk és inicializálunk egy 5 elemű tömböt
      uint16_t szamok[] = {5, 10, 15, 20, 25};
      
      // A tömb elemeinek számát így is kiszámolhatjuk automatikusan:
      // A teljes tömb mérete bájtokban osztva egy elem méretével bájtokban.
      uint8_t meret = sizeof(szamok) / sizeof(szamok[0]);
      
      // Függvény hívása és az eredmény eltárolása
      float eredmeny = atlag(szamok, meret);
      
      printf("A tömb elemei: ");
      for (uint8_t i = 0; i < meret; i++) {
          printf("%u ", szamok[i]); // %u: unsigned (előjel nélküli) egész számok kiírására
      }
      printf("\n");
      
      // %.2f: lebegőpontos szám kiírása 2 tizedesjegy pontossággal
      printf("A számok átlaga: %.2f\n", eredmeny);

      // %f: lebegőpontos szám kiírása
      printf("A számok átlaga: %f\n", eredmeny);
      
      return 0;
  }
  ```
</details>

---

## 2. Négyzet és köb kiszámítása
**Feladat:** Írjon egy függvényt, amely megkap egy számot, majd visszaadja annak négyzetét és harmadik hatványát. Írjon egy programot, amely használja ezt a függvényt, hogy kiírja egy adott szám négyzetét és harmadik hatványát.

### Elméleti háttér: Címszerzés és Mutatók (Pointerek)
A C nyelvben egy függvény alapvetően csak **egyetlen** értékkel tud visszatérni a `return` utasítás segítségével. Mi a teendő, ha nekünk kettő (vagy több) eredményre van szükségünk (például egyszerre a négyzetre és a köbre)?

Ilyenkor **mutatókat (pointer)** használunk. 
Ahelyett, hogy a függvény adná vissza az értéket, a függvényhívó (mondjuk a `main` függvény) létrehoz két üres változót, és átadja a függvénynek ezeknek a változóknak a **memóriacímét** az `&` (címképző) operátor segítségével.
A függvény a paraméterlistában ezeket a memóriacímeket várja. A paraméter típusában a `*` (csillag) jelzi, hogy az egy mutató: `int *negyzet` (egy olyan változó, ami egy egész szám memóriacímét tárolja).

A függvényen belül a `*` (dereferáló) operátorral tudunk "belenyúlni" ezen a memóriacímen lévő dobozba, és közvetlenül beleírni az eredményt a `main` függvény változójába: `*negyzet = szam * szam`.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>
  
  ```c
  #include <stdio.h>
  #include <inttypes.h>

  /******************************************************************************
  * Function:         void negyzetEsKob(int32_t szam, int32_t *negyzet, int32_t *kob)
  * Description:      Egy szám négyzetének és köbének kiszámítása
  * Input:            szam: a bemeneti szám
  * Output:           negyzet: a szám négyzete (pointeren keresztül mutatva)
  *                   kob: a szám köbe (pointeren keresztül mutatva)
  * Notes:            A függvény nem tér vissza értékkel (void), hanem pointereken keresztül
  *                   módosítja a hívó által átadott változók értékét a memóriában.
  ******************************************************************************/
  void negyzetEsKob(int32_t szam, int32_t *negyzet, int32_t *kob) {
      // A csillag (*) itt a dereferálás jele: arra a változóra hivatkozunk, 
      // amire a pointer (mutató) mutat, és abba írjuk bele az eredményt.
      *negyzet = szam * szam;
      *kob = szam * szam * szam;
  }

  int main() {
      int32_t szam = 4;
      int32_t n, k; // Ezekbe a változókba fog kerülni az eredmény, kezdetben beállítatlanok.
      
      // A függvényhívásnál a változók memóriacímét (& operátor) kell átadni, 
      // mivel a függvény pointereket vár. Így a függvény közvetlenül tudja módosítani őket.
      negyzetEsKob(szam, &n, &k);
      
      printf("A szám: %d\n", szam);
      printf("Négyzete: %d\n", n);
      printf("Harmadik hatványa: %d\n", k);
      
      return 0;
  }
  ```
</details>

---

## 3. Tömb rendezése
**Feladat:** Írjon egy függvényt, amely egy számokból álló tömböt kap meg, majd rendezze a tömb elemeit növekvő sorrendbe. Írjon egy programot, amely használja ezt a függvényt egy tetszőleges számokból álló tömbre.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  A megoldáshoz a legegyszerűbb rendezési algoritmust, a buborékrendezést (bubble sort) használjuk.
  
  ```c
  #include <stdio.h>
  #include <inttypes.h>

  /******************************************************************************
  * Function:         void tombRendez(int32_t tomb[], uint16_t meret)
  * Description:      Egy tömb elemeinek buborékrendezése növekvő sorrendbe
  * Input:            tomb: a rendezendő tömb
  *                   meret: a tömb mérete
  * Output:           A tömb elemei rendezve lesznek (helyben módosítva)
  * Notes:            A tömböt pointerként (memóriacímként) kapja meg a függvény,
  *                   így a rendezés (módosítások) a hívó oldalon az eredeti tömbben is érvényesül.
  ******************************************************************************/
  void tombRendez(int32_t tomb[], uint16_t meret) {
      // Buborékrendezés (Bubble Sort): Két egymásba ágyazott ciklussal dolgozik.
      // A külső ciklus azt szabályozza, hányszor kell elvégezni a szomszédos elemek vizsgalátát.
      for (uint16_t i = 0; i < meret - 1; i++) {
          // A belső ciklus végzi a szomszédok összehasonlítását és cseréjét.
          // Az 'i' kivonása is kell, mert minden külső kör után az utolsó 'i' elem már a helyére került.
          for (uint16_t j = 0; j < meret - i - 1; j++) {
              // Ha a bal oldali elem nagyobb, mint a jobb oldali, cseréljük fel őket (növekvő sorrend)
              if (tomb[j] > tomb[j + 1]) {
                  // A cseréhez mindig szükség van egy ideiglenes (temp) változóra
                  int32_t temp = tomb[j];
                  tomb[j] = tomb[j + 1];
                  tomb[j + 1] = temp;
              }
          }
      }
  }

  /******************************************************************************
  * Function:         void tombKiir(int32_t tomb[], uint16_t meret)
  * Description:      Tömb elemeinek kiíratása a konzolra
  * Input:            tomb: a kiírandó tömb
  *                   meret: a tömb mérete
  * Output:           Nincs (konzolra ír)
  * Notes:            Egyszerű bejárás hurok (for loop) segítségével.
  ******************************************************************************/
  void tombKiir(int32_t tomb[], uint16_t meret) {
      for (uint16_t i = 0; i < meret; i++) {
          printf("%d ", tomb[i]);
      }
      printf("\n"); // A végén soremelést is teszünk
  }

  int main() {
      // Tömb deklarálása tetszőleges számokkal
      int32_t szamok[] = {64, 34, 25, 12, 22, 11, 90};
      uint16_t meret = sizeof(szamok) / sizeof(szamok[0]);
      
      printf("Rendezés előtt: \n");
      tombKiir(szamok, meret);
      
      // Mivel C-ben a tömb neve eleve a tömb legelső elemének a memóriacímét jelenti (mutató/pointer),
      // a tombRendez függvényen belül végrehajtott cserék közvetlenül ezen a tömbön fognak érvényesülni.
      tombRendez(szamok, meret);
      
      printf("Rendezés után: \n");
      tombKiir(szamok, meret);
      
      return 0;
  }
  ```
</details>

---

## 4. Szöveg megfordítása
**Feladat:** Írjon egy függvényt, amely megfordítja egy karaktertömb tartalmát. Írjon egy programot, amely bekér egy szót vagy mondatot, majd használja ezt a függvényt a szöveg megfordításához és kiírásához.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  A megoldáshoz a `string.h` fejlécfájl `strlen` függvényét is használjuk a szöveg hosszának meghatározására.
  
  ```c
  #include <stdio.h>
  #include <string.h>
  #include <inttypes.h>

  /******************************************************************************
  * Function:         void szovegMegfordit(char szoveg[])
  * Description:      Egy karakterlánc megfordítása helyben (in-place)
  * Input:            szoveg: a megfordítandó null-terminált string
  * Output:           A megfordított string a bemeneti változóban tárolódik
  * Notes:            Eljárás a szöveg megfordítására a memóriában
  ******************************************************************************/
  void szovegMegfordit(char szoveg[]) {
      // Az strlen megadja a szöveg valós hosszát a lezáró nullakarakter ('\0') nélkül. 
      // (uint16_t) típuskényszerítésre (cast) van szükség, mert az strlen alapértelmezetten size_t típussal tér vissza.
      uint16_t hossz = (uint16_t)strlen(szoveg);

      // Kicseréljük az elsőt az utolsóval, a másodikat az utolsó előttivel, stb., 
      // ehhez elegendő a szöveg feléig elmenni, különben visszacserélnénk őket az eredeti állapotra!
      for (uint16_t i = 0; i < hossz/2; i++)
      {
          // Karakter csere temporális változó segítségével
          char temp = szoveg[i];
          szoveg[i] = szoveg[hossz - 1 - i];
          szoveg[hossz - 1 - i] = temp;
      }
  }

  int main() {
      // Előre definiált szöveg egy karaktertömbben.
      // Fontos, hogy char[] legyen (nem const char*), mert a megfordító függvény módosítja a tartalmat.
      char szoveg[] = "Hello Vilag";
      
      printf("Eredeti szoveg: %s\n", szoveg);
      
      // A szöveget karaktertömbként (pointer) kapja meg a függvény, így helyben (in-place) módosítja.
      szovegMegfordit(szoveg);
      
      printf("Megforditott szoveg: %s\n", szoveg);
      
      return 0;
  }
  ```
</details>
