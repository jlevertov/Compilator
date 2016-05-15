#include"header.h"
#include<string.h>

List* Create_list()
{
	List_node *node;
	List *list = (List*)calloc(1, sizeof(List));
	list->size = 0;
	node = (List_node*)malloc(sizeof(List_node));
	node->CurrentArrayIndex = -1;
	list->First = node;
	list->Last = node;
	list->size++;
	return list;
}

void PushToEnd(List *l, Token *TokenToAdd)
{
	//if the list is empty;
	List_node *node;
	//if the list is not empty and there is still place in the array
	node = l->Last;
	node->data[node->CurrentArrayIndex].I_AM_HERE = false;
	if (node->CurrentArrayIndex < 99)
	{
		node->CurrentArrayIndex++;
		node->data[node->CurrentArrayIndex] = *TokenToAdd;
		node->data[node->CurrentArrayIndex].I_AM_HERE = true;
	}
	//Let's spend more memmory! :)
	else
	{
		node = (List_node*)malloc(sizeof(List_node));
		node->CurrentArrayIndex = 0;
		node->data[node->CurrentArrayIndex] = *TokenToAdd;
		node->data[node->CurrentArrayIndex].I_AM_HERE = true;
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

//#Token Functions


void CreateAndStoreToken(char* Lexeme, int LineNumber, List *TokensList, enum KeyWords type)
{
	Token *TokenToCreate;
	TokenToCreate = (Token*)calloc(1, sizeof(Token));
	//TokenToCreate->Lexeme = Lexeme;
	TokenToCreate->LineNumber = LineNumber;
	strcpy(TokenToCreate->Lexeme, Lexeme);
	TokenToCreate->Type = type;
	TokenToCreate->I_AM_HERE = false;
	puts(Lexeme);
	if(TokenToCreate->Type == ERROR)
	{
		printf("Syntax Error in line %d\n", TokenToCreate->LineNumber);
	}
	else if(TokenToCreate->Type == ID)
	{
		if (CheckIsLegalIdToken(TokenToCreate->Lexeme) == true)
		{
			PushToEnd(TokensList, TokenToCreate);
		}
		else
		{
			printf("Syntax Error in line %d, %s\n", TokenToCreate->LineNumber, TokenToCreate->Lexeme);
		}
	}
	else //not an error and not an ID
	{
		PushToEnd(TokensList, TokenToCreate);
	}
}



Token BackToken(List *TokensList)
{
	List_node *nodeCurrentToken;
	int indexCurrentToken;
	bool isNext = false;
	nodeCurrentToken = FindToken(TokensList, &indexCurrentToken, isNext);
	if(nodeCurrentToken != NULL)
	{	
		nodeCurrentToken->data[indexCurrentToken].I_AM_HERE = false;
		nodeCurrentToken->data[indexCurrentToken - 1].I_AM_HERE = true;
		return nodeCurrentToken->data[indexCurrentToken - 1];
	}
	else
	{
		Token *t;
		t = (Token*)malloc(sizeof(Token));
		strcpy(t->Lexeme, "End Of Tokens");
		t->LineNumber = -1;
		t->Type = ERROR;
		return *t;
	}
}

List_node *FindToken(List *TokensList, int *Index, bool Is_Next)
{
	int i, j = 0;
	List_node *currentNode = TokensList->First;
	/*printf("Cuurent Array index: %d", currentNode->CurrentArrayIndex);
	printf("List Size: %d\n", TokensList->size);*/
	while (j < TokensList->size)
	{
		for (i = 0; i < currentNode->CurrentArrayIndex; i++)
		{
			if (currentNode->data[i].I_AM_HERE == true)
			{
				*Index = i;
				if (i == 99 && Is_Next)
				{
					if (currentNode->next != NULL)
					{
						*Index = 0;
						currentNode = currentNode->next;
					}
					else
					{
						return NULL;
					}
				}
				else if (i == 0 && !Is_Next)
				{
					if (currentNode->previous != NULL)
					{
						*Index = 99;
						currentNode = currentNode->previous;
					}
					else
					{
						return NULL;
					}

				}

				return currentNode;
			}
		}

		if (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
		}

		j++;
	}

	return NULL;
}

bool CheckIsLegalIdToken(char* LexemeToCheck)
{
	//Is the first char is a letter
	char *p;
	p = strstr(LexemeToCheck, "__");
	if ((LexemeToCheck[0] >= 'a' && LexemeToCheck[0] <= 'z') ||
		(LexemeToCheck[0] >= 'A' && LexemeToCheck[0] <= 'Z'))
	{
		if (p == NULL && (LexemeToCheck[strlen(LexemeToCheck)] != '_'))
			return true;
	}

	return false;
}