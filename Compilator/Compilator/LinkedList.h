/*lists*/
#include<stdio.h>
#include<stdlib.h>
#include"Token.h"
#define bool int
#define true 1
#define false 0

typedef struct List_node
{
	struct Token data;
	struct List_node *next;
	struct List_node *previous;
}List_node;

typedef struct List
{
	List_node* First;
	int size;
	List_node *Last;
}List;

List* Create_list();
bool IsEmpty(List *l);
void PushToEnd(List *l, Token TokenToAdd);
int Size(List *l);
List_node* FindToken(List *TokensList, int* IndexCurrentToken);
