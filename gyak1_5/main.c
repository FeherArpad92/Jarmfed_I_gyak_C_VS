/******************************************************************************
* Ez a C program, amely egy egyszerű láncolt lista (linked list) működését demonstrálja.
* Láncolt listák olyan adatszerkezetek, amelyek segítségével sorba rendezett elemeket lehet tárolni,
* és a programban számos műveletet mutat be, például elem hozzáadását, törlését, keresését és listázását.
******************************************************************************/

/******************************************************************************
* Include files
******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Constants
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/

struct node {
	int x; // x: egy egész számot tárol, amely az adott listaelem értékét reprezentálja.
	struct node* next; // next: egy mutató a következő listaelemre.Ennek a mutatónak a segítségével épül fel a láncolt lista, ahol minden elem egy másik elemre mutat.
};

/******************************************************************************
* External Variables
******************************************************************************/


/******************************************************************************
* Local Function Declarations
******************************************************************************/
int deletenode(struct node* root, int position);
int insertnode(struct node* root, int position, int value);
struct node* searchnode(struct node* root, int value);
void listnodes(struct node* root);
struct node* addnode(struct node* root, int value);

/******************************************************************************
* Local Function Definitions
******************************************************************************/


/******************************************************************************
* Function:         int main()
* Description:		a main függvény a program belépési pontja
* Input:
* Output:
* Notes:
******************************************************************************/
int main()
{
	struct node* root, * actual;
	root = (struct node*)malloc(sizeof(struct node));
	root->x = 0;
	root->next = NULL;
	actual = root;
	for (int i = 1; i < 10; i++)
		actual = addnode(actual, i);
	listnodes(root); //0 1 2 3 4 5 6 7 8 9
	actual = searchnode(root, 5);
	actual->x = 0;
	listnodes(root); //0 1 2 3 4 0 6 7 8 9
	printf("%d\n", insertnode(root, 3, 0)); //0
	printf("%d\n", insertnode(root, 12, 0)); //1
	listnodes(root); //0 1 2 0 3 4 0 6 7 8 9
	deletenode(root, 1);
	listnodes(root); //0 2 0 3 4 0 6 7 8 9 

	while (1) //Végtelen ciklus a kontrolleres szemléletmód miatt 
	{

	}
}

/******************************************************************************
* Function:         int deletenode(struct node* root, int position)
* Description:		A deletenode függvény eltávolít egy elemet a listáról a megadott pozíció alapján.
* Input:
* Output:
* Notes:
******************************************************************************/
int deletenode(struct node* root, int position)
{
	struct node* temp;
	while (--position)
	{
		root = root->next;
		if (root->next == NULL) return 1;
	}
	temp = root->next;
	root->next = root->next->next;
	free(temp);
	return 0;
}
/******************************************************************************
* Function:         int insertnode(struct node* root, int position, int value)
* Description:		Az insertnode függvény beszúr egy új elemet a listába a megadott pozícióra.
* Input:
* Output:
* Notes:
******************************************************************************/
int insertnode(struct node* root, int position, int value)
{
	struct node* savenext;
	while (--position)
	{
		root = root->next;
		if (root == NULL) return 1;
	}
	savenext = root->next;
	root = addnode(root, value);
	root->next = savenext;
	return 0;
}
/******************************************************************************
* Function:			struct node* searchnode(struct node* root, int value)
* Description:		A searchnode függvény egy elemet keres a listán belül az érték alapján,
					és visszaadja a talált elemre mutató mutatót.
* Input:
* Output:
* Notes:
******************************************************************************/
struct node* searchnode(struct node* root, int value)
{
	while (root != NULL)
	{
		if (root->x == value) return root;
		else root = root->next;
	}
	return NULL;
}
/******************************************************************************
* Function:         void listnodes(struct node* root)
* Description:		A listnodes függvény segítségével kiírásra kerül a lista összes eleme a konzolra.
* Input:
* Output:
* Notes:
******************************************************************************/
void listnodes(struct node* root)
{
	while (root != NULL)
	{
		printf("%d ", root->x);
		root = root->next;
	}
	printf("\n");
}
/******************************************************************************
* Function:         struct node* addnode(struct node* root, int value)
* Description:		Az addnode függvény egy új elemet ad hozzá a láncolt listához, és visszaadja a hozzáadott elemre mutató mutatót.
* Input:
* Output:
* Notes:
******************************************************************************/
struct node* addnode(struct node* root, int value)
{
	root->next = (struct node*)malloc(sizeof(struct node));
	root->next->x = value;
	root->next->next = NULL;
	return root->next;
}

/******************************************************************************
* Interrupt Routines
******************************************************************************/