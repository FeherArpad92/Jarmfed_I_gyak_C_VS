/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <string.h>

/******************************************************************************
* Macros
******************************************************************************/
//1. feladat
#define MAXIMUM(a, b) ((a>b) ? a : b)
//2. feladat
#define BEOLVAS(kor) \
	printf("Kerem adja meg a szemely korat: "); \
	scanf_s("%d", &kor);
//3. feladat
#define DEBUG(s) (printf("Hiba a(z) %d. sorban: ",__LINE__), printf("%s\n",s))
//4. feladat
#define HIBA_KEZELESE(feltetel, uzenet) \
	if(feltetel) \
	{ \
		printf("Hiba: %s\n", uzenet); \
		return 1; \
	}

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
float atlag(int tomb[], int meret);
void negyzet_es_kob(int szam, int* negyzet, int* kob);
void buborekRendezes(int tomb[], int meret);
void szovegMegforditasa(char szoveg[]);

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
	//int a;
	//a = 5;
	//int b = 6, c;
	//c = MAXIMUM(a, b);
	//printf("A nagyobb szam: %d\n", c);
	//2. feladat
	//unsigned int kor;
	//BEOLVAS(kor);
	//printf("A szemely kora: %u\n", kor);
	//3. feladat
	//int d = 3;
	//int t = 0;
	
	/*
	if (t == 0)
	{
		DEBUG("nullaval valo osztas!!");
	}
	else
	{
		printf("%f", ((float)d / (float)t));
	}
	*/
	//4. feladat
	//HIBA_KEZELESE(t == 0, "Nullaval valo osztas!!");
	//5. feladat
	
	//int tomb_merete = 5;

	/*
	int tomb[TOMB_MERETE];
	for (int i = 0; i < TOMB_MERETE; i++)
	{
		scanf_s("%d", &tomb[i]);
	}
	float eredmeny = atlag(tomb, TOMB_MERETE);
	printf("%f", eredmeny);
	*/
	//6. feladat
	/*
	printf("Adjon meg egy szamot: ");
	int szam = 0;
	scanf_s("%d", &szam);
	int negyzet = 0, kob = 0;
	negyzet_es_kob(szam, &negyzet, &kob);
	printf("\n%d szam negyzete: %d, kobe: %d", szam, negyzet, kob);
	*/
	//7. feladat
	/*
	int tomb[TOMB_MERETE];
	for (int i = 0; i < TOMB_MERETE; i++)
	{
		scanf_s("%d", &tomb[i]);
	}
	for (int i = 0; i < TOMB_MERETE; i++) printf("%d", tomb[i]);
	buborekRendezes(tomb, TOMB_MERETE);
	printf("\n");
	for (int i = 0; i < TOMB_MERETE; i++) printf("%d", tomb[i]);
	*/

	//8. feladat
	char szoveg[] = {"0123456789\0"};
	szovegMegforditasa(szoveg);
	printf("%s", szoveg);

	/* Replace with your application code */
	while (1)
	{

	}
}

/******************************************************************************
* Function:         float atlag(int tomb[], int meret)
* Description:      Átlag számítása
* Input:			számokat tartalmazó tömb, tömb mérete
* Output:			a számok átlaga
* Notes:
******************************************************************************/
float atlag(int tomb[], int meret)
{
	int osszeg = 0;
	for (int i = 0; i < meret; i++)
	{
		osszeg = osszeg + tomb[i];
	}
	return ((float)osszeg / (float)meret);
}

/******************************************************************************
* Function:         fvoid negyzet_es_kob(int szam, int* negyzet, int* kob)
* Description:      Négzet és harmadik hatvány számítása
* Input:			A szám és az eredmények memóriacíme
* Output:			
* Notes:
******************************************************************************/
void negyzet_es_kob(int szam, int* negyzet, int* kob)
{
	*negyzet = szam * szam;
	*kob = (*negyzet) * szam;
}

/******************************************************************************
* Function:         void buborekRendezes(int tomb[], int meret)
* Description:      Buborékos rendezés
* Input:			A tömb, a tömb mérete
* Output:
* Notes:
******************************************************************************/
void buborekRendezes(int tomb[], int meret)
{
	int volt_csere = 0;
	for (int i = 0; i < meret-1; i++)
	{
		volt_csere = 0;
		for (int j = 0; j < meret-1-i; j++)
		{
			if (tomb[j] > tomb[j + 1])
			{
				int temp = tomb[j];
				tomb[j] = tomb[j + 1];
				tomb[j + 1] = temp;
				volt_csere++;
			}
		}
		if (volt_csere == 0) return;
	}
}

/******************************************************************************
* Function:         void szovegMegforditasa(char szoveg[])
* Description:      Karaktersorozat megfordítása
* Input:			A karaktersorozatot tartalmazó tömb
* Output:
* Notes:
******************************************************************************/
void szovegMegforditasa(char szoveg[])
{
	int hossz = strlen(szoveg);
	for (int i = 0; i < hossz / 2; i++)
	{
		char temp = szoveg[i];
		szoveg[i] = szoveg[hossz - 1 - i];
		szoveg[hossz - 1 - i] = temp;
	}
	//printf("%d", hossz);

}