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
	char celstring[20];

	strcpy_s(celstring, strlen(forrasstring)+1, forrasstring);
	printf("%s", celstring);*/
	//2. feladat
	//char elsostring[] = "0123456789";
	//char masodikstring[] = "1011121314";
	//
	////malloc
	//char* osszefuzottstring = malloc(strlen(elsostring) + strlen(masodikstring) + 2);

	////strcpy osszefuzottstring <- elsostring
	//strcpy_s(osszefuzottstring, strlen(elsostring) + 1, elsostring);
	//
	////strcat osszefuzottstring + masodikstring
	//strcat_s(osszefuzottstring,strlen(elsostring)+ strlen(masodikstring)+1, masodikstring);
	//
	//printf("%s", osszefuzottstring);

	//3. feladat 
	/*double szam;
	scanf_s("%lf", &szam);
	if (szam < 0)
	{
		printf("Hiba, a szam nem pozitiv");
	}
	else
	{
		double negyzetgyok = sqrt(szam);
		printf("A szam negzetgyöke: %lf", negyzetgyok);
	}*/

	//4. feladat
	/*double alap, kitevo;
	printf("Adja meg az alapot: ");
	scanf_s("%lf", &alap);
	printf("Adja meg az kitevot: ");
	scanf_s("%lf", &kitevo);

	double eredmeny = pow(alap, kitevo);
	printf("Eredmény: %lf", eredmeny);*/
	
	//5. feladat
	//printf("pi erteke: %.20lf", M_PI);

	//6. feladat
	double szog_fokban;
	printf("Ada meg a szoget fogban: ");
	scanf_s("%lf", &szog_fokban);

	double szog_radianban = szog_fokban * (M_PI / 180.0);
	double sinus = sin(szog_radianban);
	double cosinus = cos(szog_radianban);
	double tangent = tan(szog_radianban);

	printf("sin: %lf, cos: %lf, tan: %lf", sinus, cosinus, tangent);




	/* Replace with your application code */
	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/





