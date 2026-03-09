---
layout: default
title: 1. Gyakorlat - Makrók
nav_order: 2
---

# 1. Gyakorlat: Preprocessor és Makrók
{: .no_toc }

A mai gyakorlat célja a C előfeldolgozó (preprocessor) működésének megértése. Bár a modern C++ fejlesztésben a makrókat gyakran felváltják a `template` és `inline` megoldások, beágyazott környezetben (mint a járműfedélzeti rendszerek) és C-ben továbbra is kikerülhetetlenek. A feladatok megoldása során törekedjünk a "biztonságos" makrók írására, ügyelve a mellékhatásokra. A teljes megoldás letölthető innen: [main.c]({{ site.github.repository_url }}/blob/main/1_makrok/main.c)

## Elméleti háttér: Szöveg vs. Függvény
Mielőtt a feladatokat megnéznénk, fontos tisztázni a C preprocessor működését. A makróhívás **nem függvényhívás**. A fordító előfeldolgozója a fordítás legelső fázisában egyszerű szöveges behelyettesítést végez (copy-paste), még mielőtt a szintaktikai elemzés vagy a típusellenőrzés megtörténne.

Ez két kritikus hibalehetőséget rejt magában:
1.  **Műveleti sorrend (Precedencia):** Ha a makró környezete vagy paramétere kifejezést tartalmaz, a behelyettesítés után a műveleti sorrend felborulhat.
2.  **Többszöri kiértékelés (Side effects):** Mivel a makró kódja bemásolódik, a paraméterek is többször szerepelhetnek a kimenetben, így a mellékhatással járó műveletek (pl. `i++`) többször futhatnak le.

## Tartalomjegyzék
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## 1. Maximum keresés
**Feladat:** Írjon egy makrót, amely visszaadja két szám maximumát! Írjon egy rövid tesztprogramot is, amely bemutatja a működését.



<details markdown="1">
  <summary>Megoldás megjelenítése</summary>
  
  Mivel a makró szöveges helyettesítés, a paramétereket és a teljes kifejezést is zárójelbe kell tenni a precedencia-hibák elkerülése végett.
  
  ```c
  #include <stdio.h>

  // Kritikus pont: Zárójelezzünk mindent!
  // Ha nem tennénk, egy MAX(a!=b, c) hívás hibásan működhetne.
  #define MAXIMUM(a, b) ( ((a) > (b)) ? (a) : (b))

  int main() {
      int x = 10;
      int y = 25;
      
      printf("A nagyobb szám: %d\n", MAXIMUM(x, y));
      
      // Teszt kifejezéssel is:
      printf("Kifejezés maximuma: %d\n", MAXIMUM(x+5, y-10));
      
      return 0;
  }
  ```
</details>

---

## 2. Életkor beolvasása (Többsoros makrók)

**Feladat:** Írjon egy makrót, amely segít beolvasni egy személy korát a felhasználótól, majd írja ki ezt a képernyőre egy formázott üzenetben.

### Elméleti háttér: A sorfolytonosság jele
A C preprocessor alapértelmezetten sor-orientált: egy sor, egy utasítás. Ha egy makró definíciója túl hosszú, vagy az átláthatóság kedvéért több sorba szeretnénk tördelni, a sor végét egy `\` (backslash) jellel kell "kiszabadítanunk" (escape).

**Fontos:** Sortörés esetén a `\` után közvetlenül **nem állhat semmilyen karakter** (még szóköz sem!), és azonnal új sornak kell következnie.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>
  
  A megoldásban láthatjuk, hogy a változó nevét (`kor`) paraméterként adjuk át. Mivel a `scanf` (vagy `scanf_s`) címet vár, a makrón belül a `&` operátort a paraméter elé kell írnunk. Ez az operátor a változó címét adja meg, így a beolvasott érték helyesen kerül a változóba.
  
  ```c
  #include <stdio.h>

  // A backslash (\) jelzi a preprocessornak, hogy a definíció
  // a következő sorban folytatódik.
  #define BEOLVAS(valtozo) \
      printf("Kerem adja meg a szemely korat: "); \
      scanf_s("%d", &valtozo);

  int main() {
      int szemely_kora = 0;
      
      // A makró hívása itt történik.
      // A preprocessor a fenti két sort másolja be ide a fordítás előtt.
      BEOLVAS(szemely_kora);
      
      // Ellenőrzésképpen kiírjuk, hol járunk. Ezzel láthatjuk, hogy a makró helyére a teljes kód beillesztődik.
      printf("Beolvasas kesz. A kod a %d. sorban jar.\n", __LINE__);
      printf("A beolvasott kor: %d\n", szemely_kora);
      
      return 0;
  }
  ```

</details>

---

## 3. Hibakeresés
**Feladat:** Írjon egy makrót, amely a programban lévő hibakereséshez használható. A makró automatikusan kiírja a forráskód sorának a számát és a hibát tartalmazó üzenetet. Használja ezt a makrót egy egyszerű programban.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  A hibakereséshez a fordító által biztosított előre definiált makrókat (`__LINE__`, `__FILE__`) érdemes használni. Ezek fordítási időben cserélődnek le az aktuális sor számára és fájl nevére. A szabványos hibakimenetre (`stderr`) írás is jó gyakorlat ilyen esetekben.

  ```c
  #include <stdio.h>

  // A __LINE__ és __FILE__ makrók a fordító által beépített definíciók.
  // A __LINE__ az aktuális sor sorszámára cserélődik.
  // A __FILE__ az aktuális fájl nevére cserélődik.
  // A (msg) zárójelezése itt is fontos, bár string literálnál (olyan érték, amely futási időben nem változik) ritkán okoz gondot, 
  // de kifejezések esetén (pl. függvény visszatérési értéke) biztonságosabb.
  // Az stderr (standard error) használata azért javasolt hibák kiírására, mert az oprendszer szintjén
  // elválik a normál kimenettől (stdout), így a hibák átirányításkor sem vesznek el.
  #define HIBA(msg) fprintf(stderr, "[HIBA] Fájl: %s, Sor: %d: %s\n", __FILE__, __LINE__, (msg))

  int main() {
      int homereseklet = 150;
      
      printf("Hőmérséklet ellenőrzése...\n");

      if (homereseklet > 100) {
          // Itt hívjuk meg a makrót. A kimeneten pontosan látni fogjuk,
          // hogy a forráskód melyik sorában történt a hívás.
          HIBA("Túl magas a hőmérséklet!");
      } else {
          printf("Hőmérséklet rendben.\n");
      }
      
      return 0;
  }
  ```

</details>

---

## 4. Feltételes hibakezelés
**Feladat:** Írjon egy makrót, amely segít kezelni hibákat. A makró ellenőrizzen egy feltételt, és ha a feltétel igaz, kiír egy hibaüzenetet és leállítja a programot. Használja ezt a makrót egy programban, amely például egy osztást végez, és ellenőrzi, hogy ne osszon nullával.

<details markdown="1">
  <summary>Megoldás megjelenítése</summary>

  Ennél a feladatnál gyakori hiba a makró blokkjának helytelen kezelése. Nézzük meg, miért fontos a `do-while(0)` szerkezet!

  **Hibás megoldás (Simán kapcsos zárójel)**
  Ha csak simán kapcsos zárójelek közé tesszük a kódot:
  ```c
  #define CHECK_BAD(feltetel, uzenet) { \
      if(feltetel) { \
          printf(uzenet); \
          exit(1); \
      } \
  }
  ```
  Ez addig működik, amíg nem használjuk egy `if-else` szerkezetben. Például:
  ```c
  if (x > 0)
      CHECK_BAD(x == 0, "Hiba"); // Itt a pontosvessző miatt a fordító lezárja az if-et...
  else
      // ... és ez az else ág "lógva marad" (syntax error), mert a makró utáni pontosvessző üres utasításnak számít.
      printf("X rendben");
  ```

  **Helyes megoldás (do-while(0) szerkezet)**
  A `do { ... } while(0)` garantálja, hogy a makró egyetlen, zárt utasításként viselkedjen, és "elnyeli" a sor végi pontosvesszőt.

  ```c
  #include <stdio.h>
  #include <stdlib.h> // exit() miatt szükséges

  // A do-while(0) szerkezet biztosítja, hogy a makró egyetlen utasításként viselkedjen,
  // és szintaktikailag helyes legyen if-else ágakban is.
  #define CHECK_ERROR(feltetel, uzenet) \
      do { \
          if (feltetel) { \
              fprintf(stderr, "Végzetes hiba: %s\n", (uzenet)); \
              exit(1); \
          } \
      } while(0)

  int main() {
      int osztando = 100;
      int oszto = 0;
      
      printf("Osztás művelet: %d / %d\n", osztando, oszto);

      // Ellenőrizzük, hogy a nevező nulla-e. Ha igen, a program itt leáll.
      CHECK_ERROR(oszto == 0, "Nullával való osztás nem megengedett!");
      
      // Ez a sor már nem fog lefutni, ha a hiba bekövetkezett.
      int eredmeny = osztando / oszto;
      printf("Eredmény: %d\n", eredmeny);
      
      return 0;
  }
  ```

</details>


