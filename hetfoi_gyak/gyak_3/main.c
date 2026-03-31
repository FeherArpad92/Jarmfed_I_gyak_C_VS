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

/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Constants
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/
int32_t szam = 42;
int32_t* ptr = &szam;

int32_t szam_2 = 10;
int32_t* ptr_2 = &szam_2;
/******************************************************************************
* External Variables
******************************************************************************/


/******************************************************************************
* Local Function Declarations
******************************************************************************/
uint16_t stringhossz(char* str);

/******************************************************************************
* Local Function Definitions
******************************************************************************/

/******************************************************************************
* Function:         uint16_t stringhossz(char* str)
* Description:      karaktertömb méretet adja vissza
* Input:			karaktertomb elso elemenek memoriacime
* Output:			tömb mérete
* Notes:
******************************************************************************/
uint16_t stringhossz(char* str)
{
	uint16_t hossz=0;
	while (*str != '\0')
	{
		hossz++;
		str++;
	}


	return hossz;
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
	//printf("A szam erteke: %d\n", szam);
	//printf("A szam memoriacime: %p\n", ptr);
	//printf("A szam erteke ptr hasznalataval: %d", *ptr);
	
	//2. feladat	
	//printf("A szam erteke: %d\n", szam_2);
	//*ptr_2 = 20;
	//printf("A szam erteke: %d\n", szam_2);
	//int32_t** pp = &ptr_2;
	//**pp = 70;
	//printf("A szam erteke: %d", szam_2);

	//3. feladat
	/*uint16_t meret;
	printf("Adja meg az elemszamot: ");
	scanf_s("%d", &meret);

	int32_t* tomb = (int32_t*)malloc(meret * sizeof(int32_t));
	printf("Adja meg a tomb elemeit!\n");
	for (uint16_t i = 0; i < meret; i++)
	{
		printf("%d. elem: ", i + 1);
		scanf_s("%d", &tomb[i]);

	}
	for (uint16_t i = 0; i < meret; i++)
	{
		printf("%d. elem: %d", i + 1, tomb[i]);

	}

	free(tomb);*/

	//4. feladat
	char *szoveg = "4. feladat szovege";

	uint16_t hossz = stringhossz(szoveg);

	printf("A szoveg hossza: %d", hossz);



	/* Replace with your application code */
	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/