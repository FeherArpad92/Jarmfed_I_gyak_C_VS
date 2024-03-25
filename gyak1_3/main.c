/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
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
* Function:         int main(void)
* Description:      main function
* Input:
* Output:
* Notes:
******************************************************************************/
int main(void)
{
	//1. feladat
	/*
	int szam = 42;
	int* pointer;
	pointer = &szam;
	printf("Szam: %d\n", szam);
	printf("Memoriacim: %d\n", pointer);
	printf("%d", *pointer);
	*/
	//3. feladat
	printf("Adjon meg egy szamot: ");
	int meret = 0;
	scanf_s("%d", &meret);
	int* tomb = (int*)malloc(meret * sizeof(int));
	if (tomb == NULL)
	{
		printf("Sikertelen memoriafoglalas");
		return 1;
	}
	printf("Adja meg a szamokat: ");
	for (int i = 0; i < meret; i++)
	{
		scanf_s("%d", &tomb[i]);
		//scanf_s("%d", tomb+i);
	}
	free(tomb);
	//4. feladat

	const char szoveg[] = "Ez egy konstans karakterlanc.";

	const char* p = szoveg; // Pointer, amely végigiterál a stringen
	while (*p) // Amíg nem érünk a string végére (nulla karakter)
		p++;

	printf("A szoveg hossza: %d\n", p - szoveg); // A pointerek különbsége megadja a karakterek számát


	
	/* Replace with your application code */
	while (1)
	{

	}
}