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
//1. feladat
#define MAXIMUM(a, b) ((a>b) ? a : b)
//2. feladat
#define BEOLVAS(kor) \
	printf("Kerem adja meg a szemely korat: "); \
	scanf_s("%d", &kor);

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
	int a;
	a = 5;
	int b = 6, c;
	c = MAXIMUM(a, b);
	printf("A nagyobb szam: %d\n", c);
	//2. feladat
	unsigned int kor;
	BEOLVAS(kor);
	printf("A szemely kora: %u\n", kor);

	/* Replace with your application code */
	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/






