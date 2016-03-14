#include"LinkedList.h"

List* Create_list()
{
	List *list = (List*)calloc(1, sizeof(List));
	list->size = 0;
	return list;
}
void PushToEnd(List *l, Token TokenToAdd)
{
	List_node *node = (List_node*)calloc(1, sizeof(List_node));

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
int Size(List *l)
{
	return l->size;
}
bool IsEmpty(List *l)
{
	return l->size == 0;
}