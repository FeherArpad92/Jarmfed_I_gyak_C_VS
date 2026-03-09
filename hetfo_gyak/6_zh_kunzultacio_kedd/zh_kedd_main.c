/******************************************************************************
 * Created: 
 * Author :
 * ZH kedd
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
#define IS_UPPER(c, nagy)  ((c) >= 65 && (c) <= 90 ? (nagy = 1) : (nagy = 0))

/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Global Variables
******************************************************************************/
struct node
{
	char* varosnev;
	struct node* next;
};

const char szoveg[] = "Ez egy mondat.";

/******************************************************************************
* External Variables
******************************************************************************/

/******************************************************************************
* Local Function Declarations
******************************************************************************/
void listnodes(struct node* root);
struct node* addnode(struct node* root, char* varos_nev);
void print_binary(uint8_t szam);
uint8_t varos_keres(struct node* root, char* keresett_varos);
uint8_t leghosszabb_szo(const char* mondat);

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
	// print_binary teszt
	uint8_t szam = 0b01011111;
	printf("Szám binárisan: ");
	print_binary(szam);

	// IS_UPPER teszt
	char karakter = 'a';
	uint8_t nagy = 0;
	IS_UPPER(karakter, nagy);
	printf("Karakter %c nagybetű? %d\n", karakter, nagy);

	
	// láncolt lista - városok

	struct node* actual;
	struct node* root = (struct node*)malloc(sizeof(struct node));

	root->varosnev = (char*)malloc(strlen("Budapest") + 1);
	strcpy_s(root->varosnev,strlen("Budapest")+1, "Budapest");
	root->next = NULL;


	actual = addnode(root, "Szeged");
	actual = addnode(actual, "Debrecen");

	listnodes(root);

	printf("Keresés eredménye (Szeged): %d\n", varos_keres(root, "Szeged"));
	printf("Keresés eredménye (Pécs): %d\n", varos_keres(root, "Pécs"));

	// leghosszabb szó teszt
	printf("Leghosszabb szó hossza: %d\n", leghosszabb_szo(szoveg));

	/* Replace with your application code */
	while (1)
	{
	}
}





/******************************************************************************
* Function:         void print_binary(uint8_t szam)
* Description:      Kiírja a számot bináris formátumban
* Input:			szám
* Output:
* Notes:
******************************************************************************/
//void print_binary(uint8_t szam)
//{
//	for (int8_t i = 7; i >= 0; i--)
//	{
//		printf("%d", (szam >> i) & 1);
//	}
//	printf("\n");
//}

void print_binary(uint8_t szam)
{
	for (int8_t i = 7; i >= 0; i--)
	{
		uint16_t ketto_hatvany = 1;
		for (int8_t j = 0; j < i; j++)
		{
			ketto_hatvany *= 2; // 2^i kiszámítása szorzásokkal
		}

		if ((szam / ketto_hatvany) % 2 == 1)
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

/******************************************************************************
* Function:         struct node* addnode(struct node* root, int value)
* Description:      Új elemet ad hozzá a láncolt listához
* Input:			szülő elem memóriacíme, kor, név
* Output:			új elem memóriacíme
* Notes:
******************************************************************************/
struct node* addnode(struct node* root, char* varos_nev)
{
	root->next = (struct node*)malloc(sizeof(struct node));
	root->next->varosnev = (char*)malloc(strlen(varos_nev) + 1); // +1 a '\0' miatt
	strcpy_s(root->next->varosnev, strlen(varos_nev) + 1, varos_nev);
	root->next->next = NULL;
	return root->next;
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
		printf("nev: %s", root->varosnev);
		root = root->next;
		printf("\n");
	}

}

/******************************************************************************
* Function:         uint8_t varos_keres(struct node* root, char *keresett_varos)
* Description:      Keres egy várost a láncolt listában
* Input:			root elem memóriacíme, keresett város neve
* Output:			1 ha megtalálta, 0 ha nem
* Notes:
******************************************************************************/
uint8_t varos_keres(struct node* root, char* keresett_varos)
{
	while (root != NULL)
	{
		if (strcmp(root->varosnev, keresett_varos) == 0)
		{
			return 1;
		}
		root = root->next;
	}
	return 0;
}

/******************************************************************************
* Function:         uint8_t leghosszabb_szo(const char *mondat)
* Description:      Visszatér a leghosszabb szó hosszával
* Input:			mondat kezdőcíme
* Output:
* Notes:
******************************************************************************/
uint8_t leghosszabb_szo(const char* mondat)
{
	uint8_t max_hossz = 0;
	uint8_t aktualis_hossz = 0;
	uint8_t i = 0;

	while (mondat[i] != '\0')
	{
		if (mondat[i] != ' ' && mondat[i] != '.' && mondat[i] != ',' && mondat[i] != '!' && mondat[i] != '?')
		{
			aktualis_hossz++;
			if (aktualis_hossz > max_hossz)
			{
				max_hossz = aktualis_hossz;
			}
		}
		else
		{
			aktualis_hossz = 0;
		}
		i++;
	}
	return max_hossz;
}

/******************************************************************************
* Interrupt Routines
******************************************************************************/