#include"LinkedList.h"

struct List* Create_list()
{
	 List *list = ( List*)calloc(1, sizeof(List));
	list->size = 0;
	return list;
}
void PushToEnd( List *l, void *TokenToAdd)
{
	 List_node *node = ( List_node*)calloc(1, sizeof( List_node));

	node->data = TokenToAdd;
	if (l->Last == NULL)
	{
		l->First = node;
		l->Last = node;
	}
	else
	{
		l->Last->next = node;
		node->previous = l->Last;
		l->Last = node;
		l->size++;
	}
}
int Size( List *l)
{
	return l->size;
}
bool IsEmpty( List *l)
{
	return l->size == 0;
}