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
    char celString[50]; // Fel kell k�sz�teni egy c�lsztringet, ami elegend?en nagy a forr�s sz�veg t�rol�s�hoz.
    printf("A string hossza: %d", (int)strlen(forrasString));
    // A strcpy f�ggv�ny m�solja a forrasString tartalm�t a celString-be.
    strcpy_s(celString, strlen(forrasString) + 1, forrasString);
    // Ki�rjuk a m�solt stringet.
    printf("A masolt string: %s\n", celString);

    //2. feladat
    char elsoString[] = "0123456789", masodikString[] = "1011123414151617";
    char* osszefuzottString = (char*)malloc(strlen(elsoString) + strlen(masodikString) + 10); // El?sz�r lefoglalunk egy el�g nagy ter�letet az �sszef?z�tt stringnek

    // �sszef?zz�k a k�t stringet
    // El?sz�r m�soljuk az els? stringet az �sszef?z�tt stringbe
    strcpy_s(osszefuzottString, strlen(elsoString) + strlen(masodikString) + 1, elsoString);
    // Majd hozz�f?zz�k a m�sodik stringet
    strcat_s(osszefuzottString, strlen(elsoString) + strlen(masodikString) + 1, masodikString);

    // Ki�rjuk az �sszef?z�tt stringet
    printf("Az osszefuzotttt string: %s\n", osszefuzottString);
    free(osszefuzottString);

    //3. feladat
    double szam;

    printf("Kerem adjon meg egy pozitiv szamot: ");
    scanf_s("%lf", &szam);

    // Ellen?rizz�k, hogy a sz�m pozit�v-e
    if (szam < 0) {
        printf("Hiba: A megadott szam nem pozitiv.\n");
    }
    else {
        // Sz�m�tjuk a n�gyzetgy�k�t �s ki�rjuk
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

    // �tv�lt�s fokb�l radi�nba
    double radian = fok * (M_PI / 180.0);

    // Szinusz, koszinusz �s tangens sz�m�t�sa
    double szinusz = sin(radian);
    double koszinusz = cos(radian);
    double tangens = tan(radian);

    printf("Szinusz: %f\n", szinusz);
    printf("Koszinusz: %f\n", koszinusz);
    printf("Tangens: %f\n", tangens);
    return 0;
}