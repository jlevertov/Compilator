/*lists*/
#include<stdio.h>
#include<stdlib.h>
#define bool int
#define true 1
#define false 0

typedef struct list_node
{
	void *data;
	 list_node *next;
	 list_node *previous;
}List_node;

typedef struct list
{
	List_node* First;
	int size;
	List_node *Last;
}List;

struct List* Create_list();
bool IsEmpty( List *l);
void PushToEnd( List *l, void *TokenToAdd);
int Size( List *l);
struct List_node* FindToken( List* TokensList, int* IndexCurrentToken);
