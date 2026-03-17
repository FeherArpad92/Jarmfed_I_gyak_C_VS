/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>

/******************************************************************************
* Macros
******************************************************************************/
#define MAXIMUM(a,b) ((a>b) ? a : b)

#define BEOLVAS(valtozo) \
	printf("Adja meg a szemely korat! ");\
	scanf_s("%d", &valtozo)

#define HIBA(msg) printf("Hiba a %d. sorban: %s, file: %s",__LINE__, msg, __FILE__)

#define CHECK_ERROR(feltetel, uzenet)\
	do{\
		if(feltetel) {\
			printf("Vegzetes hiba: %s", uzenet);\
			exit(1);\
		}\
	} while(0)

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
	//int x = 20;
	//int y = 24;

	//int m = MAXIMUM(x, y);

	//printf("A nagyobb szam: %d", m);

	//2. feladat
	//unsigned int szemely_kora = 0;

	//BEOLVAS(szemely_kora);

	//printf("A beolvasás kész. A kod a %d. sorban jár.\n", __LINE__);
	//printf("A beolvasott kor: %d", szemely_kora);

	//3. feladat
	/*int homerseklet = 150;

	printf("A hőmérséklet ellenőrzése\n");

	if (homerseklet > 100)
	{
		HIBA("Tul magas homerseklet!");
	}
	else
	{
		printf("Homerseklet rendben");
	}*/

	//4. feladat
	int osztando = 100;
	int oszto = 0;

	CHECK_ERROR(oszto == 0, "Nullaval valo osztas nem megengedett!");

	/* Replace with your application code */
	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/