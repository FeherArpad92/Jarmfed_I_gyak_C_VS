/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Constants
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/
uint16_t szamok[] = { 5,10,15,20,26,34,4,5,45,3,45 };


/******************************************************************************
* External Variables
******************************************************************************/


/******************************************************************************
* Local Function Declarations
******************************************************************************/
float atlag(uint16_t tomb[], uint8_t meret);

/******************************************************************************
* Local Function Definitions
******************************************************************************/

/******************************************************************************
* Function:         float atlag(uint16_t tomb[], uint8_t meret)
* Description:      Átlag számítása
* Input:			Számokat tartalmazó tömb, tömb mérete
* Output:			A számok átlaga
* Notes:
******************************************************************************/
float atlag(uint16_t tomb[], uint8_t meret)
{
	uint16_t osszeg = 0;
	for (uint8_t i = 0; i < meret; i++) osszeg += tomb[i];

	return (float)osszeg / (float)meret;
}

/******************************************************************************
* Function:         void negyzetEskob(int32_t szam, int32_t* negyzet, int32_t* kob)
* Description:      Négyzet és köb számítás
* Input:			Szám, amit négyzetre és köbre emelünk és ennek a kimenetei pointerei
* Output:			---
* Notes:
******************************************************************************/
void negyzetEskob(int32_t szam, int32_t* negyzet, int32_t* kob) {

	*negyzet = szam * szam;
	*kob = szam * szam * szam;
}

/******************************************************************************
* Function:         void tombRendez(int32_t tomb[], uint16_t meret)
* Description:      Rendezzi a tömböt
* Input:			egy tömb, és annak a mérete
* Output:			---
* Notes:
******************************************************************************/
void tombRendez(int32_t tomb[], uint16_t meret) {
	//Bubble sort (buborék rendezés)
	for (uint16_t i = 0; i < meret; i++) {
		for (uint16_t j = 0; j < meret - i - 1; j++) {
			if (tomb[j] > tomb[j + 1]) {
				int32_t temp = tomb[j];
				tomb[j] = tomb[j + 1];
				tomb[j + 1] = temp;
			}
		}
	}
}
/******************************************************************************
* Function:         void szovegMegfordit(char szover[])
* Description:      Megfordítja a astringet avagy a karakter tömböt
* Input:			egy char tömb
* Output:			---
* Notes:
******************************************************************************/
void szovegMegfordit(char szoveg[]) {
	uint16_t hossz = (uint16_t)strlen(szoveg);

	for (int i = 0; i < hossz / 2; i++) {
		char temp = szoveg[i];
		szoveg[i] = szoveg[hossz - i - 1];
		szoveg[hossz - i - 1] = temp;
	}
}

/******************************************************************************
* Function:         void tombKiir(int32_t tomb[], uint16_t meret)
* Description:      Kiírja a tömböt
* Input:			egy tömb, és annak a mérete
* Output:			---
* Notes:
******************************************************************************/
void tombKiir(int32_t tomb[], uint16_t meret) {
	for (int i = 0; i < meret; i++) {
		printf("%d ", tomb[i]);
	}
	printf("\n");
}

/******************************************************************************
* Function:         int main(void)
* Description:      main function
* Input:
* Output:
* Notes:
******************************************************************************/
int main(void)
{
	//uint8_t meret = sizeof(szamok)/ sizeof(szamok[0]);

	//printf("%d", meret);
	//float eredmeny = atlag(szamok, meret);
	//printf("A szamok atlaga: %f\n \n \n", eredmeny);
	/* Replace with your application code */

	char szoveg[] = "Hello vilag!";
	printf("Eredeti szoveg %s\n", szoveg);

	szovegMegfordit(szoveg);
	printf("Forditott szoveg %s\n", szoveg);

	int32_t szamok[] = { 63,43,12,35,114,1 };
	uint16_t meret = sizeof(szamok) / sizeof(szamok[0]);
	printf("Rendezes elott:\n");
	tombKiir(szamok, meret);

	tombRendez(szamok, meret);

	printf("Rendezes utan:\n");
	tombKiir(szamok, meret);


	int32_t szam = 4;
	int32_t neg, kob;

	negyzetEskob(szam, &neg, &kob);
	printf("Az eredeti szam: %d \n", szam);
	printf("Az eredeti szam negyzete: %d \n", neg);
	printf("Az eredeti szam kobe: %d \n", kob);

	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/





