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
struct node
{
	int x; //listaelem értékét reprezentálja
	struct node* next; //a következő listaelem memóriacíme
};


/******************************************************************************
* External Variables
******************************************************************************/


/******************************************************************************
* Local Function Declarations
******************************************************************************/
struct node* addnode(struct node* root, int value);
void listnodes(struct node* root);
struct node* searchnode(struct node* root, int value);
int deletenode(struct node* root, int position);

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
	struct node* root, *actual;

	root = (struct node *)malloc(sizeof(struct node));
	root->x = 0;
	root->next = NULL;

	actual = root;
	for (int i = 1; i < 10; i++) actual = addnode(actual, i);
	listnodes(root);

	actual = searchnode(root, 5);
	actual->x = 200;
	listnodes(root);

	printf("%d\n", insertnode(root, 3, 100));
	printf("%d\n", insertnode(root, 13, 100));
	listnodes(root);
	deletenode(root, 2); 
	listnodes(root);


	/* Replace with your application code */
	while (1)
	{

	}
}

/******************************************************************************
* Function:         int deletenode(struct node* root, int position)
* Description:		listaelem törlése
* Input:			első elem memóriacíme, törlendő elem pozíciója
* Output:			0: sikeres törlés, 1: sikertelen
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
* Description:      új listaelem beszúrása adott pozícióba
* Input:			az első listaelem memóriacíme, pozíció, új listaelem értéke
* Output:			0: ha sikerült a beszúrás, 1: ha nem
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
* Function:         struct node* searchnode(struct node* root, int value)
* Description:      Egy elemet keres a listában
* Input:			az első elem memóriacíme, keresendő érték
* Output:			a keresndő elem memóriacíme
* Notes:
******************************************************************************/
struct node* searchnode(struct node* root, int value)
{
	while (root != NULL)
	{
		if (root->x == value)
			return root;
		else
			root = root->next;
	}
	return NULL;
}

/******************************************************************************
* Function:         void listnodes(struct node* root)
* Description:      Listázza az összes elemet
* Input:			az első elem memóriacíme
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
* Description:      Új elemet ad hozzá a listához
* Input:			az előző elem memóriacíme, érték
* Output:			az új elem memóriacíme
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





