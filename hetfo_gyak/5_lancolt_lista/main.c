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
	int x; //a listeelem értékét reprezentálja
	struct node* next; // mutató a következő listaelemre
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
int insertnode(struct node* root, int position, int value);
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
	struct node *root, *actual;
	root = (struct node*) malloc(sizeof(struct node));
	root->x = 0;
	root->next = NULL;

	actual = root;
	for (int i = 1; i < 10; i++) actual = addnode(actual, i);
	listnodes(root);

	actual = searchnode(root, 5);
	actual->x = 0;
	listnodes(root);

	printf("%d\n", insertnode(root, 3, 100));
	printf("%d\n", insertnode(root, 12, 100));

	listnodes(root);
	deletenode(root, 1);
	listnodes(root);




	/* Replace with your application code */
	while (1)
	{

	}
}

/******************************************************************************
* Function:         int deletenode(struct node* root, int position)
* Description:      elem törlése
* Input:			root elem memóriacíme, törlandő elem pozíciója
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
* Description:      új listaelem beszúrása
* Input:			root elem memóriacíme, pozíció, érték
* Output:			0: ha sikerült beszúrni, 1: ha nem 
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
* Description:      listaelem keresése
* Input:			root elem memóriacíme, keresendő érték
* Output:			keresendő értéket tartalmazó listaelem memóriacíme
* Notes:
******************************************************************************/
struct node* searchnode(struct node* root, int value)
{
	while (root != NULL)
	{
		if (value == root->x)
			return root;
		else
			root = root->next;
	}
	return NULL;
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
		printf("%d ", root->x);
		root = root->next;
	}
	printf("\n");
}

/******************************************************************************
* Function:         struct node* addnode(struct node* root, int value)
* Description:      Új elemet ad hozzá a láncolt listához
* Input:			szülő elem memóriacíme, érték
* Output:			új elem memóriacíme
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





