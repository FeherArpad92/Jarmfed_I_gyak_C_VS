/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
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
* Function:         int main(void)
* Description:      main function
* Input:
* Output:
* Notes:
******************************************************************************/
int main(void)
{
	//1. feladat
	/*char forrasstring[] = "0123456789";
	char celstring[50];
	strcpy_s(celstring, strlen(forrasstring)+1, forrasstring);

	printf("A masolt string: %s", celstring);*/

	////2. feladat
	//char elsostring[] = "0123456789";
	//char masodikstring[] = "1011121314";

	//char* osszefuzottstring = malloc(strlen(elsostring) + strlen(masodikstring) + 2);

	////strcpy_s
	//strcpy_s(osszefuzottstring, strlen(elsostring) + 1, elsostring);

	////strcat_s
	//strcat_s(osszefuzottstring, strlen(elsostring) + strlen(masodikstring) + 1, masodikstring);

	//printf("%s", osszefuzottstring);

	//3. feladat
	//double szam = 0;
	//scanf_s("%lf", &szam);

	//if (szam < 0) printf("Hiba, a szám nem pozitiv!");
	//else
	//{
	//	double negyzetgyok = sqrt(szam);
	//	printf("A szam negyzetgyoke: %lf", negyzetgyok);
	//}

	//sqrt()
	//4. feladat
	/*double alap, kitevo;
	printf("Adja meg az alapot: ");
	scanf_s("%lf", &alap);
	printf("Adja meg az kitevot: ");
	scanf_s("%lf", &kitevo);
	
	double eredmeny = pow(alap, kitevo);
	printf("A hatvanyozas eredmenye: %lf", eredmeny);*/

	//5. feladat
	//printf("A pi erteke: %.20lf", M_PI);
	//6. feladat
	double fok = 0;
	printf("Adja meg a szoget: ");
	scanf_s("%lf", &fok);
	double radian = fok * (M_PI / 180.0);

	printf("Sinus: %lf", sin(radian));
	printf("Cosinus: %lf", cos(radian));
	printf("Tangent: %lf", tan(radian));




	/* Replace with your application code */
	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/





