/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <inttypes.h>

/******************************************************************************
* Macros
******************************************************************************/
#define TOMB_MERETE 5

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
float atlag(uint16_t tomb[], uint8_t meret);
void negyzet_es_kob(uint16_t szam, uint16_t* negyzet, uint16_t* kob);
void buborekRendezes(uint16_t tomb[], uint16_t meret);

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
	uint16_t tomb[TOMB_MERETE];
	//1. feladat
	/*for (uint8_t i = 0; i < TOMB_MERETE; i++)
	{
		scanf_s("%d", &tomb[i]);
	}
	float eredmeny = atlag(tomb, TOMB_MERETE);
	printf("%f", eredmeny);*/

	//2.feladat
	/*printf("Adjon meg egy számot: ");
	uint16_t szam = 0;
	scanf_s("%d", &szam);
	uint16_t n, k;
	negyzet_es_kob(szam, &n, &k);
	printf("A szam negyzete: %d, kobe: %d", n, k);*/

	//3. feladat
	for (uint8_t i = 0; i < TOMB_MERETE; i++) scanf_s("%d", &tomb[i]);
	buborekRendezes(tomb, TOMB_MERETE);
	for (uint8_t i = 0; i < TOMB_MERETE; i++) printf("%d ", tomb[i]);

	/* Replace with your application code */
	while (1)
	{

	}
}

/******************************************************************************
* Function:         float atlag(uint16_t tomb[], uint8_t meret)
* Description:      Átlag számítása
* Input:			szamokat tartalmazó tömb, tömb mérete
* Output:			a számok átlaga
* Notes:
******************************************************************************/
float atlag(uint16_t tomb[], uint8_t meret)
{
	uint16_t osszeg = 0;
	for (uint8_t i = 0; i < meret; i++) osszeg += tomb[i];
	return ((float)osszeg / (float)meret);
}

/******************************************************************************
* Function:         void negyzet_es_kob(uint16_t szam, uint16_t* negyzet, uint16_t* kob)
* Description:      négyzet és köb számítása
* Input:			uint16_t szám, negyzet pointer(uint16_t), köb(uint16_t) pointer
* Output:			
* Notes:
******************************************************************************/
void negyzet_es_kob(uint16_t szam, uint16_t* negyzet, uint16_t* kob)
{
	*negyzet = szam * szam;
	*kob = (*negyzet) * szam;
}

/******************************************************************************
* Function:         void buborekRendezes(uint16_t tomb[], uint16_t meret)
* Description:      buborékos rendezés
* Input:			tömb, tömb mérete
* Output:
* Notes:
******************************************************************************/
void buborekRendezes(uint16_t tomb[], uint16_t meret)
{
	for (uint16_t i = 0; i < meret; i++)
	{
		for (uint16_t j = 0; j < meret-1; j++)
		{

			if (tomb[j + 1] < tomb[j])
			{
				uint16_t temp = tomb[j];
				tomb[j] = tomb[j + 1];
				tomb[j + 1] = temp;
			}
		}
	}
}

void szovegMegfroditasa(char szoveg[])
{
	uint16_t hossz = strlen(szoveg);
	for (uint16_t i = 0; i < hossz; i++)
	{

	}
}

/******************************************************************************
* Interrupt Routines
******************************************************************************/





