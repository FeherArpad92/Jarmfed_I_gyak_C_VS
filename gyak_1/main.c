/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/******************************************************************************
* Macros
******************************************************************************/
#define TRUE 1
#define FALSE 0

//1. feladat
#define MAXIMUM(a, b) ((a>b) ? a : b)
//2. feladat
#define BEOLVAS(kor) \
	printf("Adja meg a kort: "); \
	scanf_s("%d", &kor);
//3. feladat
#define DEBUG(s) (printf("A hiba a(z) %d. sorban: ", __LINE__), printf("%s\n",s))
//4. feladat
#define HIBA_KEZELESE(feltetel, uzenet) \
		if(feltetel) \
		{ \
			printf("Hiba: %s\n", uzenet); \
			return 1; \
		}
/******************************************************************************
* Constants
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/
int a=0, b;

/******************************************************************************
* External Variables
******************************************************************************/


/******************************************************************************
* Local Function Declarations
******************************************************************************/
float atlag(int tomb[], int meret);
void NegyzetEsKob(int szam, int* negyzet, int* kob);
void buborekRendezes(int tomb[], int meret);

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
	int c = -1;

	//printf("Adja meg a-t:");
	//scanf_s("%d", &a);

	//printf("Adja meg b-t:");
	//scanf_s("%d", &b);

	//1. feladat
	//c = MAXIMUM(a, b);
	//printf("c erteke: %d", c);
	//2. feladat
	//unsigned int eletkor = -1;
	//BEOLVAS(eletkor);
	//printf("A szemely eletkora: %u", eletkor);
	//3. fedat

	/*int a = 3;
	int b = 1;

	if (b == 0)
	{
		DEBUG("Nullaval valo osztas");
	}
	else
	{
		printf("Az osztas eredmenye: %f\n", (float)a / (float)b);
	}*/
	//4. feladat
	/*HIBA_KEZELESE(b == 0, "Nullaval valo osztas");

	if(TRUE)
	{
		printf("Lefutott");
	}*/
	//5. feladat
	/*int tomb[5];
	for (int i = 0; i < 5; i++)
	{
		scanf_s("%d", &tomb[i]);
	}
	float eredmeny = atlag(tomb, 5);
	printf("átlag: %f", eredmeny);*/
	//6. feladat
	/*int szam = 0;
	printf("Adja meg a szamot: ");
	scanf_s("%d", &szam);
	int negyzet, kob;
	NegyzetEsKob(szam, &negyzet, &kob);
	printf("A %d negyzete: %d, kobe: %d", szam, negyzet, kob);*/
	
	//7. feladat
	srand(time(NULL));
	int tomb[100];
	for (int i = 0; i < 100; i++)
	{
		tomb[i] = rand() % 100 + 1;
		//scanf_s("%d", &tomb[i]);
	}
	buborekRendezes(tomb, 100);
	printf("A rendezett tomb: ");
	for (int i = 0; i < 100; i++) printf("%d ", tomb[i]);

	/* Replace with your application code */
	while (1)
	{

	}
}


/******************************************************************************
* Function:         float atlag(int tomb[], int meret)
* Description:      Függvény átlag számításához
* Input:			számok tömbben és a tömb mérete
* Output:			átlag
* Notes:
******************************************************************************/
float atlag(int tomb[], int meret)
{
	int osszeg = 0;
	for (int i = 0; i < meret; i++)
	{
		//osszeg = osszeg + tomb[i];
		osszeg += tomb[i];
	}
	return (float)osszeg / (float)meret;
}

/******************************************************************************
* Function:         void NegyzetEsKob(int szam, int* negyzet, int* kob)
* Description:      Függvény a második és harmadik hatvány számításához
* Input:			szám, pointer a négyzet eredményének tárolásához, pointer a köb eredményének tárolásához
* Output:			
* Notes:
******************************************************************************/
void NegyzetEsKob(int szam, int* negyzet, int* kob)
{
	*negyzet = szam * szam;
	//*kob = szam * szam * szam;
	*kob = szam * (*negyzet);
}


/******************************************************************************
* Function:         void buborekRendezes(int tomb[], int meret)
* Description:      Buburékos sorbarendezés
* Input:			tömb memóriacíme, tömb mérete
* Output:
* Notes:
******************************************************************************/
void buborekRendezes(int tomb[], int meret)
{
	for (int i = 0; i < meret-1; i++)
	{
		for (int j = 0; j < meret-1; j++)
		{
			if (tomb[j] > tomb[j + 1])
			{
				int temp = tomb[j];
				tomb[j] = tomb[j + 1];
				tomb[j + 1] = temp;
			}
		}
	}
}






