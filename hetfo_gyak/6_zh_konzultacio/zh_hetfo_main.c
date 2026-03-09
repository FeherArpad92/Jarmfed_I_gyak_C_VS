/******************************************************************************
 * Created:
 * Author :
 * ZH hétfő
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h> // kell a strcpy, strcmp miatt

/******************************************************************************
* Macros
******************************************************************************/
#define SWAP(x, y, temp)  temp = x; x = y; y = temp
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
uint8_t atlageletkor(struct node* root);
uint8_t szoszam(char* mondat);
uint8_t tukorkep(uint8_t szam);
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

	// SWAP teszt
	int a = 5, b = 10, temp;
	SWAP(a, b, temp);
	printf("SWAP után: a = %d, b = %d\n", a, b);

	// 2. Szöveg konstans
	char szoveg[] = "Ez egy hat szóból álló mondat.";

	// szoszam teszt
	printf("Szavak száma: %d\n", szoszam(szoveg));



	// tukorkep teszt
	uint8_t szam=241;
	printf("A szám tükörképe: %d\n", tukorkep(szam));

	
	struct node* root, * actual;
	root = (struct node*)malloc(sizeof(struct node));
	root->eletkor = 19;
	char tanulo_neve[] = "Elso tanulo";
	root->nev = (char*)malloc(strlen(tanulo_neve) + 1); // +1 a '\0' miatt
	strcpy_s(root->nev, strlen(tanulo_neve) + 1, tanulo_neve);
	root->next = NULL;

	actual = addnode(root,21,"Masodik tnulo");
	actual = addnode(actual, 22, "Harmadik tnulo");
	actual = addnode(actual, 31, "Negyedik tnulo");
	actual = addnode(actual, 27, "Otodik tnulo");

	

	listnodes(root);
	printf("Atlag eletkor: %d", atlageletkor(root));

	/* Replace with your application code */
	while (1)
	{

	}
}

/******************************************************************************
* Function:         uint8_t tukorkep(uint8_t szam)
* Description:      Visszatér a szám tükörképével
* Input:			1 bájtos szám
* Output:
* Notes:
******************************************************************************/
uint8_t tukorkep(uint8_t szam)
{
	uint8_t tukor = 0;

	uint8_t szaz = szam / 100;
	uint8_t tiz = (szam - szaz*100) / 10;
	uint8_t egy = (szam - szaz * 100 - tiz * 10);


	return egy*100 + tiz*10 + szaz;
}

/******************************************************************************
* Function:         uint8_t szoszam(char* mondat)
* Description:      Visszatér a szavak számával
* Input:			Karaktersorozat kezdőcíme
* Output:
* Notes:
******************************************************************************/
uint8_t szoszam(char* mondat)
{
	uint8_t szamlalo = 0;
	uint8_t i = 0;

	if (mondat[0] != '\0') {
		szamlalo = 1;
	}

	while (mondat[i] != '\0') 
	{
		if (mondat[i] == ' ' && mondat[i + 1] != '\0') 
		{
			szamlalo++;
		}
		i++;
	}
	return szamlalo;
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
		printf("kor: %d nev: %s", root->eletkor, root->nev);
		root = root->next;
		printf("\n");
	}
	
}

/******************************************************************************
* Function:         uint8_t atlageletkor(struct node* root)
* Description:      Kiírásra kerül az átlag
* Input:			root elem memóriacíme
* Output:
* Notes:
******************************************************************************/
uint8_t atlageletkor(struct node* root)
{
	uint16_t osszeg = 0;
	uint8_t darab = 0;

	while (root != NULL)
	{
		darab++;
		osszeg += root->eletkor;
		root = root->next;
	}
	if (darab == 0) return 0;
	return osszeg / darab;
}

/******************************************************************************
* Function:         struct node* addnode(struct node* root, int value)
* Description:      Új elemet ad hozzá a láncolt listához
* Input:			szülő elem memóriacíme, kor, név
* Output:			új elem memóriacíme
* Notes:
******************************************************************************/
struct node* addnode(struct node* root, int kor, char *tanulo_nev)
{
	root->next = (struct node*)malloc(sizeof(struct node));
	root->next->eletkor = kor;
	root->next->nev = (char*)malloc(strlen(tanulo_nev) + 1); // +1 a '\0' miatt
	strcpy_s(root->next->nev, strlen(tanulo_nev) + 1, tanulo_nev);
	root->next->next = NULL;
	return root->next;
}

/******************************************************************************
* Interrupt Routines
******************************************************************************/