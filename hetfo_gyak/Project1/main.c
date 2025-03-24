/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <corecrt_math_defines.h>

/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Constants
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/


/******************************************************************************
* External Variables
******************************************************************************/


/******************************************************************************
* Local Function Declarations
******************************************************************************/


/******************************************************************************
* Local Function Definitions
******************************************************************************/


/******************************************************************************
* Global Function Definitions
******************************************************************************/
/******************************************************************************
* Function:         int main()
* Description: 	main function
* Input:
* Output:
* Notes:
******************************************************************************/
int main(void)
{
    //1. feladat
    char forrasString[] = "0123456789";
    char celString[50]; // Fel kell készíteni egy célsztringet, ami elegend?en nagy a forrás szöveg tárolásához.
    printf("A string hossza: %d", (int)strlen(forrasString));
    // A strcpy függvény másolja a forrasString tartalmát a celString-be.
    strcpy_s(celString, strlen(forrasString) + 1, forrasString);
    // Kiírjuk a másolt stringet.
    printf("A masolt string: %s\n", celString);

    //2. feladat
    char elsoString[] = "0123456789", masodikString[] = "1011123414151617";
    char* osszefuzottString = (char*)malloc(strlen(elsoString) + strlen(masodikString) + 10); // El?ször lefoglalunk egy elég nagy területet az összef?zött stringnek

    // Összef?zzük a két stringet
    // El?ször másoljuk az els? stringet az összef?zött stringbe
    strcpy_s(osszefuzottString, strlen(elsoString) + strlen(masodikString) + 1, elsoString);
    // Majd hozzáf?zzük a második stringet
    strcat_s(osszefuzottString, strlen(elsoString) + strlen(masodikString) + 1, masodikString);

    // Kiírjuk az összef?zött stringet
    printf("Az osszefuzotttt string: %s\n", osszefuzottString);
    free(osszefuzottString);

    //3. feladat
    double szam;

    printf("Kerem adjon meg egy pozitiv szamot: ");
    scanf_s("%lf", &szam);

    // Ellen?rizzük, hogy a szám pozitív-e
    if (szam < 0) {
        printf("Hiba: A megadott szam nem pozitiv.\n");
    }
    else {
        // Számítjuk a négyzetgyökét és kiírjuk
        double negyzetgyok = sqrt(szam);
        printf("A(z) %lf szam negyzetgyoke: %lf\n", szam, negyzetgyok);
    }
    //4. feladat
    double alap, kitevo;

    printf("Adja meg az alapot: ");
    scanf_s("%lf", &alap);
    printf("Adja meg a kitevot: ");
    scanf_s("%lf", &kitevo);

    double eredmeny = pow(alap, kitevo);
    printf("Eredmeny: %lf ^ %lf = %lf\n", alap, kitevo, eredmeny);
    //5. feldat
    printf("A pi erteke: %f\n", M_PI);
    //6. feldat
    double fok;
    printf("Adja meg a szoget fokban: ");
    scanf_s("%lf", &fok);

    // Átváltás fokból radiánba
    double radian = fok * (M_PI / 180.0);

    // Szinusz, koszinusz és tangens számítása
    double szinusz = sin(radian);
    double koszinusz = cos(radian);
    double tangens = tan(radian);

    printf("Szinusz: %f\n", szinusz);
    printf("Koszinusz: %f\n", koszinusz);
    printf("Tangens: %f\n", tangens);
    return 0;
}