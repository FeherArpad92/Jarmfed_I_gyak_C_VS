/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
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
	//1.feladat
	/*uint8_t sz = 42;
	uint8_t* p;
	p = &sz;
	printf("Szam: %d\n", sz);
	printf("Memoriacim: %lld\n", p);
	printf("Memoriateruleten levo ertek: %d", *p);*/

	//2. feladat
	/*uint8_t number = 10;
	uint8_t* pointer;
	pointer = &number;
	printf("%d\n", number);
	(*pointer) = 20;
	printf("%d\n", number);
	uint8_t** ptr_to_ptr;
	ptr_to_ptr = &pointer;
	(**ptr_to_ptr) = 30;
	printf("%d", number);*/
	//3. feladat
	//printf("Adjon meg egy meretet: ");
	//uint64_t meret = 0;
	//scanf_s("%lld", &meret);

	//uint16_t* tomb = (uint16_t*) malloc(sizeof(uint16_t) * meret);
	//if (tomb == NULL)
	//{
	//	printf("Sikertelen memoriafoglalas");
	//	return 1;
	//}
	//printf("Adjon meg szamokat: ");
	//for (uint64_t i = 0; i < meret; i++)
	//{
	//	//scanf_s("%d", tomb + i);
	//	scanf_s("%d", &tomb[i]);
	//}
	//for (uint64_t i = 0; i < meret; i++) printf("%d ", *(tomb + i));
	//printf("masik modszer a kiiratasra: ");
	//for (uint64_t i = 0; i < meret; i++) printf("%d ", tomb[i]);
	//free(tomb);
	//4. feladat

	const char szoveg[] = "Ez egy konstans karakterlanc";
	printf("A karakterlanc hossza (strlen): %d\n", strlen(szoveg));
	printf("A karakterlanc hossza (sizeof): %d\n", sizeof(szoveg));

	const char* p = szoveg;
	while(*p) p++;

	printf("A karakterlanc hossza (pointerekkel): %d", (p-szoveg));

	/* Replace with your application code */
	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/





