#include <stdio.h>

int main(void)
{
    // --- Változók deklarációja és inicializálása ---
    int a = 0;
    int b = 10;
    int c = 0;
    int d = 0;
    float r = 1.4f;
    double w = 1.5;
    char kar = 'a';
    char op = 0;

    // --- Alapvetõ kimenet és bemenet ---
    printf("Hello World!\n\n");

    printf("Adjon meg egy egesz erteket (a): ");
    scanf_s("%d", &a);
    printf("A beolvasott ertekek - a: %d, b: %d\n\n", a, b);

    // --- Feltételes elágazások bemutatása ---
    printf("Adja meg 'd' erteket a feltetelvizsgalathoz: ");
    scanf_s("%d", &d);

    // Hagyományos if-else szerkezet
    if (d < 5)
    {
        c = 3;
        d = 5;
    }
    else
    {
        c = 4;
    }
    printf("Hagyomanyos if-else utan 'c' erteke: %d\n", c);

    // Ternáris operátor használata
    c = (d < 5) ? 3 : 4;
    printf("Ternaris operator utan 'c' erteke: %d\n", c);

    // --- Matematikai manipulációk ---
    c++;
    c += 1;
    c--;
    printf("Matematikai manipulaciok (++, +=, --) utan 'c' erteke: %d\n\n", c);

    // --- Lebegõpontos számok és karakterek ---
    printf("Lebegopontos valtozok - r erteke: %.2f, w erteke: %f\n", r, w);
    printf("A '%c' karakter hexadecimalis kodja: %x\n\n", kar, kar);

    // --- Bemeneti puffer ürítése a karakter beolvasása elõtt ---
    while (getchar() != '\n');

    // --- Switch-case szerkezet ---
    printf("Adjon meg egy muveleti jelet (* vagy +): ");
    scanf_s("%c", &op, 1);

    switch (op)
    {
    case '*':
        printf("A szorzat: %f\n\n", r * w);
        break;
    case '+':
        printf("Az osszeg: %f\n\n", r + w);
        break;
    default:
        printf("Nem ertelmezett muvelet.\n\n");
        break;
    }

    // --- Ciklusok bemutatása (while, do-while, for) ---
    printf("--- Ciklusok bemutatasa ---\n");

    // while ciklus (elöltesztelõs)
    int i = 0;
    printf("while ciklus (0-tol 2-ig):\n");
    while (i < 3)
    {
        printf("i erteke: %d\n", i);
        i++;
    }
    printf("\n");

    // do-while ciklus (hátultesztelõs - legalább egyszer lefut)
    int j = 5;
    printf("do-while ciklus (a feltetel hamis, megis lefut egyszer):\n");
    do
    {
        printf("j erteke: %d\n", j);
        j++;
    } while (j < 5);
    printf("\n");

    // for ciklus (számlálós)
    printf("for ciklus (visszaszamlalas 3-tol 1-ig):\n");
    for (int k = 3; k > 0; k--)
    {
        printf("k erteke: %d\n", k);
    }

    return 0;
}