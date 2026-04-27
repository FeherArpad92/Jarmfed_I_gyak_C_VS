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
* Function:         uint16_t stringHossz(const char *str)
* Description:      String hossz számítás
* Input:			konstans karater tömböt várunk
* Output:			String hossza
* Notes:
******************************************************************************/
uint16_t stringHossz(const char* str) {
	uint16_t hossz = 0;
	while (*str != '\0') {
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
	const char* szoveg = "Hello vilag, tomb";

	uint16_t hossz = stringHossz(szoveg);

	printf("A szoveg: %s\nA hossza:%d\n", szoveg, hossz);

	int32_t szam = 42;

	int32_t* ptr = &szam;

	printf("A szam erteke: %d\n", szam);
	printf("A pointer altal mutatott erekte: %d\n", *ptr);
	printf("A szam memoriacime: %p\n\n\n", (void*)ptr);

	*ptr = 20;

	printf("A szam erteke: %d\n", szam);
	printf("A pointer altal mutatott erekte: %d\n", *ptr);
	printf("A szam memoriacime: %p\n\n\n", (void*)ptr);

	int32_t** pp = &ptr;

	printf("A szam erteke: %d\n", szam);
	printf("A pointer altal mutatott erekte: %d\n", *ptr);
	printf("A pointer-pointer altal mutatott erekte: %d\n", **pp);
	printf("A szam memoriacime: %p\n", (void*)ptr);
	printf("A ptr memoriacime: %p\n\n\n", (void*)pp);

	**pp = 67;
	printf("A szam erteke: %d\n", szam);
	printf("A pointer altal mutatott erekte: %d\n", *ptr);
	printf("A pointer-pointer altal mutatott erekte: %d\n", **pp);
	printf("A szam memoriacime: %p\n", (void*)ptr);
	printf("A ptr memoriacime: %p\n\n\n", (void*)pp);

	printf("Hany elemet szeretne eltarolni a tomb-ben? ");
	uint16_t meret = 0;
	scanf_s("%hu", &meret);

	//dinamikus mmemoria allokáció
	int32_t* tomb = (int32_t*)malloc(meret * sizeof(int32_t));

	if (tomb == NULL) {
		printf("Sikertelen volt a memoria foglalas");
		return 1;
	}

	//feltöltés
	printf("Kerem adja meg a valtozokat a tombbe\n");
	for (uint16_t i = 0; i < meret; i++)
	{
		printf(" %u. elem: ", i + 1);
		scanf_s("%d", &tomb[i]);
	}

	//kiírjuk
	printf("\nA tömb elemei:\n");
	for (uint16_t i = 0; i < meret; i++)
	{
		printf(" tomb[%hu] = %d \n", i, tomb[i]);
	}

	free(tomb);

	//jó szokás
	tomb = NULL;

	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/





