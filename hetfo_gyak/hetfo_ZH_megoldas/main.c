/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/******************************************************************************
* Macros
******************************************************************************/
#define SWAP(x,y,temp) temp = x; x = y; y = temp;

/******************************************************************************
* Constants
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/
struct node
{
	int eletkor;
	char* nev;
	//char nev[100];
	struct node* next; // mutató a következő listaelemre
};


/******************************************************************************
* External Variables
******************************************************************************/


/******************************************************************************
* Local Function Declarations
******************************************************************************/
struct node* addnode(struct node* root, int kor, char* tanulo_nev);
void listnodes(struct node* root);

uint8_t szoszam(char* mondat);
uint8_t tukorkep(uint8_t szam);
void print_binary(uint8_t szam);
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
	////1. feladat
	//int a = 5, b = 10, temp;
	//SWAP(a, b, temp);
	//printf("SWAP utan: a:%d, b:%d\n", a, b);
	////2. feladat
	//const char szoveg[] = "Ez egy hat szóból álló mondat.";
	//printf("A szoveg hossza: %d\n", szoszam(szoveg));
	////3. feladt
	//uint8_t szam = 231;
	//printf("tukorkep: %d\n", tukorkep(szam));



	////4. feladat
	//struct node* root, * actual;
	//root = (struct node*)malloc(sizeof(struct node));
	//root->eletkor = 34;

	//char tanulo_neve[] = "Elso tanulo";

	//root->nev = (char*)malloc(strlen(tanulo_neve) + 1);
	//strcpy_s(root->nev, strlen(tanulo_neve) + 1, tanulo_neve);
	//root->next = NULL;

	//actual = root;
	//actual = addnode(actual, 21, "Masodik tanulo");
	//actual = addnode(actual, 24, "Harmadik tanulo");
	//actual = addnode(actual, 22, "Negyedik tanulo");
	//actual = addnode(actual, 31, "Otodik tanulo");

	//listnodes(root);


	uint8_t binaris_szam = 0b01011111;
	print_binary(binaris_szam);


	/* Replace with your application code */
	while (1)
	{

	}
}

void print_binary(uint8_t szam)
{
	for (int i = 7; i >= 0; i--)
	{
		uint16_t ketto_hatvany = 1;
		for (int j = 0; j < i; j++) ketto_hatvany = ketto_hatvany * 2;

		if ((szam / ketto_hatvany) % 2 == 1)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	}
}

uint8_t tukorkep(uint8_t szam)
{
	uint8_t tukor = 0;

	uint8_t szaz = szam / 100;
	uint8_t tiz = (szam - szaz * 100) / 10;
	uint8_t egy = (szam - szaz * 100 - tiz * 10);

	tukor = egy * 100 + tiz * 10 + szaz;

	return tukor;
}

uint8_t szoszam(char* mondat) 
{

	uint8_t szoszam = 0;
	uint8_t i = 0;
	if (mondat[0] != '\0') szoszam = 1;

	while (mondat[i] != '\0')
	{
		if (mondat[i] == ' ' && mondat[i + i] != '\0') szoszam++;
		i++;
	}
	return szoszam;
}





/******************************************************************************
* Function:         void listnodes(struct node* root)
* Description:      Kiírásra kerül a lista összes eleme
* Input:			root elem memóriacíme
* Output:
* Notes:
******************************************************************************/
void listnodes(struct node* root)
{
	while (root != NULL)
	{
		printf("nev: %s, eletkor: %d ",root->nev, root->eletkor);
		root = root->next;
		printf("\n");
	}
	
}

/******************************************************************************
* Function:         struct node* addnode(struct node* root, int value)
* Description:      Új elemet ad hozzá a láncolt listához
* Input:			szülő elem memóriacíme, érték
* Output:			új elem memóriacíme
* Notes:
******************************************************************************/
struct node* addnode(struct node* root, int kor, char* tanulo_nev)
{
	root->next = (struct node*)malloc(sizeof(struct node));
	root->next->eletkor = kor;
	root->next->nev = (char*)malloc(strlen(tanulo_nev) + 1);
	strcpy_s(root->next->nev, strlen(tanulo_nev) + 1, tanulo_nev);
	root->next->next = NULL;
	return root->next;
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/





