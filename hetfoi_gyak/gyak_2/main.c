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
uint16_t szamok[] = { 5, 10, 15, 27, 25 };

/******************************************************************************
* External Variables
******************************************************************************/


/******************************************************************************
* Local Function Declarations
******************************************************************************/
float atlag(uint16_t tomb[], uint8_t meret);
void negyzeteskob(int32_t szam, int32_t* negyzet, int32_t* kob);
void tombrendez(int32_t tomb[], uint16_t meret);
void tombkiir(int32_t tomb[], uint16_t meret);
void szovegmegfordit(char szoveg[]);

/******************************************************************************
* Local Function Definitions
******************************************************************************/

/******************************************************************************
* Function:         void negyzeteskob(int32_t szam, int32_t* negyzet, int32_t* kob)
* Description:      Egy szam negyzetet és harmadik hatványát számolja ki
* Input:			szám, a négyzetre mutató memóriacím, kobre mutató memóriacím
* Output:			-
* Notes:
******************************************************************************/
void negyzeteskob(int32_t szam, int32_t* negyzet, int32_t* kob)
{
	*negyzet = szam * szam;
	*kob = szam * szam * szam;
}

/******************************************************************************
* Function:         float atlag(uint16_t tomb[], uint8_t meret)
* Description:      Átlag számítása
* Input:			számokat tartalmazó tömb, tömb mérete
* Output:			a számok átlaga
* Notes:
******************************************************************************/
float atlag(uint16_t tomb[], uint8_t meret)
{
	uint16_t osszeg = 0;

	for (uint8_t i = 0; i < meret; i++) osszeg += tomb[i];

	return (float)osszeg / (float)meret;
}

/******************************************************************************
* Function:         void tombrendez(int32_t tomb[], uint16_t meret)
* Description:      Buborekos rendezés
* Input:			rendezendo tomb, tomb merete
* Output:			-
* Notes:			-
******************************************************************************/
void tombrendez(int32_t tomb[], uint16_t meret)
{
	uint8_t volt_csere = 0;

	for (uint16_t i = 0; i < meret - 1; i++)
	{
		for (uint16_t j = 0; j < meret - 1-i; j++)
		{
			if (tomb[j] > tomb[j + 1])
			{
				int32_t temp = tomb[j];
				tomb[j] = tomb[j + 1];
				tomb[j + 1] = temp;
				volt_csere = 1;
			}
		}
		if (volt_csere == 0) return;

	}
}

/******************************************************************************
* Function:         void tombkiir(int32_t tomb[], uint16_t meret)
* Description:      kiirja a tomb elemeit
* Input:			tomb, tomb elemszama
* Output:
* Notes:
******************************************************************************/
void tombkiir(int32_t tomb[], uint16_t meret)
{
	for (uint16_t i = 0; i < meret; i++) printf("%d ", tomb[i]);
	printf("\n");
}

/******************************************************************************
* Function:         void szovegmegfordit(char szoveg[])
* Description:      szoveg megforditasas
* Input:			szoveg
* Output:			-
* Notes:			-
******************************************************************************/
void szovegmegfordit(char szoveg[])
{
	uint16_t hossz = strlen(szoveg);

	for (uint16_t i = 0; i < hossz / 2; i++)
	{
		char temp = szoveg[i];
		szoveg[i] = szoveg[hossz - i - 1];
		szoveg[hossz - i - 1] = temp;
	}
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
	//1. feladat
	float eredmeny = atlag(szamok, 5);
	printf("Szamok atlaga: %f", eredmeny);
	
	//2. feladat
	int32_t szam = 4;
	int32_t n, k;

	negyzeteskob(szam, &n, &k);

	printf("A %d szam negyzete: %d, kobe: %d", szam, n, k);

	//3. feladat
	int32_t szamok[] = { 64, 34, 25, 12, 22, 11, 90 };
	uint16_t elemszam = sizeof(szamok) / sizeof(szamok[0]);

	tombkiir(szamok, elemszam);
	tombrendez(szamok, elemszam);
	tombkiir(szamok, elemszam);

	//4. feladat

	char szoveg[] = "Hello vilag";
	printf("\n%s\n", szoveg);
	szovegmegfordit(szoveg);
	printf("%s", szoveg);



	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/