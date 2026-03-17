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

#define MAXIMUM(a,b) ( ( (a) > (b) ) ) ? (a) : (b)

#define BEOLVAS(kor) \
	printf("Kerem adja meg a korat!"); \
	scanf_s("%d",&kor)

#define HIBA(msg) printf("[HIBA] fajl: %s, sor: %d, hibauzenet: %s",__FILE__, __LINE__, msg)

#define CHECK_ERROR(feltetel, uzenet)\
	do{\
		if (feltetel)\
		{\
			printf("Vegzetes hiba: %s", uzenet);\
			exit(1);\
		}\
	} while(0);

int main(void)
{
	////1. feladat
	//int x = 12;
	//int y = 26;

	//printf("A nagyobb szam: %d\n", MAXIMUM(x, y));

	////2. feladat
	//int szemely_kora = 0;
	//BEOLVAS(szemely_kora);

	//printf("A beolvasott kor: %d", szemely_kora);

	//3. feladat
	/*int homerseklet = 150;

	if (homerseklet > 100)
	{
		HIBA("Tul magas homerseklet!");
	}*/

	//4.feladat 
	int oszto = 0;
	int osztando = 100;

	CHECK_ERROR(oszto == 0, "Nullaval valo osztas nem lehetseges!");


	/* Replace with your application code */
	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/





