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
#define TOMB_M 5

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
float szamokAtlaga(uint16_t tomb[], uint8_t meret);
void szamNegyzetKob(uint16_t szam, uint16_t* n, uint16_t* k);
void buborekosRendezes(uint16_t tomb[], uint16_t meret);

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
	//1.feladat
	/*uint16_t t[TOMB_M];
	for (uint8_t i=0; i < TOMB_M; i++) scanf_s("%d", &t[i]);
	float eredmeny = szamokAtlaga(t, TOMB_M);
	printf("%f", eredmeny);*/

	//2.feladat
	/*printf("Adjon megy egy sz�mot: ");
	uint16_t sz, negyzet, kob;
	scanf_s("%d", &sz);
	szamNegyzetKob(sz, &negyzet, &kob);
	printf("A szam negyzete: %d, kobe: %d", negyzet, kob);*/

	//3. feladat
	uint16_t t[TOMB_M];
	for (uint8_t i = 0; i < TOMB_M; i++) scanf_s("%d", &t[i]);
	buborekosRendezes(t, TOMB_M);
	for (uint8_t i = 0; i < TOMB_M; i++) printf("%d ", t[i]);
	/* Replace with your application code */
	while (1)
	{

	}
}

/******************************************************************************
* Function:         float szamokAtlaga(uint16_t tomb[], uint8_t meret)
* Description:      Kisz�molja a sz�mok �tlag�s
* Input:			t�mb, t�mb m�rete
* Output:			�tlag
* Notes:
******************************************************************************/
float szamokAtlaga(uint16_t tomb[], uint8_t meret)
{
	float osszeg = 0;
	for (uint8_t i = 0; i < meret; i++)
	{
		osszeg = osszeg + tomb[i];
	}
	return osszeg / (float)meret;
}

/******************************************************************************
* Function:         void szamNegyzetKob(uint16_t szam, uint16_t *n, uint16_t *k)
* Description:      Kisz�molja egy sz�m n�gyzet�t �s harmadik hatv�ny�t
* Input:			sz�m, n�gyzet pointer, k�b pointer
* Output:			
* Notes:
******************************************************************************/
void szamNegyzetKob(uint16_t szam, uint16_t *n, uint16_t *k)
{
	*n = szam * szam;
	*k = (*n) * szam;
}

/******************************************************************************
* Function:         void buborekosRendezes(uint16_t tomb[], uint16_t meret)
* Description:      bubor�kos sorbarendez�s
* Input:			t�mb, t�mb m�rete
* Output:
* Notes:
******************************************************************************/
void buborekosRendezes(uint16_t tomb[], uint16_t meret)
{
	int volt_csere = 0;
	for (uint16_t i = 0; i < meret; i++)
	{
		for (uint16_t j = 0; j < meret-1-i; j++)
		{
			if (tomb[j] > tomb[j + 1])
			{
				uint16_t temp = tomb[j];
				tomb[j] = tomb[j + 1];
				tomb[j + 1] = temp;
				volt_csere++;
			}
		}
		if (volt_csere == 0) return;
	}
}

void szovegMegforditasa(char szoveg[])
{
	uint16_t hossz = strlen(szoveg);


}



/******************************************************************************
* Interrupt Routines
******************************************************************************/





