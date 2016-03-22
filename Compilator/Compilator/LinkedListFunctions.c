#include"LinkedList.h"
#include<string.h>

List* Create_list()
{
	List *list = ( List*)calloc(1, sizeof(List));
	list->size = 0;
	return list;
}

void PushToEnd( List *l, Token *TokenToAdd)
{
	//if the list is empty;
	List_node *node;
	if (l->Last == NULL && TokenToAdd != NULL)
	{
		node = (List_node*)malloc(sizeof(List_node));
		node->CurrentArrayIndex = 0;
		node->data[node->CurrentArrayIndex] = *TokenToAdd;
		l->First = node;
		l->Last = node;
	}
	//if the list is not empty and there is still place in the array
	else
	{
		node = l->Last;
		if (node->CurrentArrayIndex < 99)
		{
			node->CurrentArrayIndex++;
			node->data[node->CurrentArrayIndex] = *TokenToAdd;
		}
		//Let's spend more memmory! :)
		else
		{
			node = (List_node*)malloc(sizeof(List_node));
			node->CurrentArrayIndex = 0;
			node->data[node->CurrentArrayIndex] = *TokenToAdd;
			l->Last->next = node;
			node->previous = l->Last;
			l->Last = node;
			l->size++;
		}
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

//#Token Functions

void DefineTokenType(Token *TokenToCheck)
{
	int row, colum;
	/*is keyword*/
	if (TokenToCheck->Lexeme == "start")
	{
		TokenToCheck->Type = START;
	}
	else if (TokenToCheck->Lexeme == "end")
	{
		TokenToCheck->Type = END;
	}
	else if (TokenToCheck->Lexeme == "program")
	{
		TokenToCheck->Type = PROGRAM;
	}
	else if (TokenToCheck->Lexeme == "loop")
	{
		TokenToCheck->Type = LOOP;
	}
	else if (TokenToCheck->Lexeme == "until")
	{
		TokenToCheck->Type = UNTIL;
	}
	else if (TokenToCheck->Lexeme == "end_loop")
	{
		TokenToCheck->Type = END_LOOP;
	}
	else if (TokenToCheck->Lexeme == "if")
	{
		TokenToCheck->Type = IF;
	}
	else if (TokenToCheck->Lexeme == "end_if")
	{
		TokenToCheck->Type = END_IF;
	}
	else if (TokenToCheck->Lexeme == "else")
	{
		TokenToCheck->Type = ELSE;
	}
	else if (TokenToCheck->Lexeme == "int")
	{
		TokenToCheck->Type = INT;
	}
	else if (TokenToCheck->Lexeme == "real")
	{
		TokenToCheck->Type = REAL;
	}
	else if (TokenToCheck->Lexeme == "+")
	{
		TokenToCheck->Type = ADD_OP;
	}
	else if (TokenToCheck->Lexeme == "*")
	{
		TokenToCheck->Type = MUl_OP;
	}
	else if (TokenToCheck->Lexeme == ";")
	{
		TokenToCheck->Type = CMD_SEPERATOR;
	}
	else if (TokenToCheck->Lexeme == ",")
	{
		TokenToCheck->Type = COMMA;
	}
	else if (TokenToCheck->Lexeme == ":")
	{
		TokenToCheck->Type = COLON;
	}
	else if (TokenToCheck->Lexeme == "[")
	{
		TokenToCheck->Type = BRACKETS_OPEN;
	}
	else if (TokenToCheck->Lexeme == "]")
	{
		TokenToCheck->Type = BRACKETS_CLOSE;
	}
	else if (TokenToCheck->Lexeme == ">")
	{
		TokenToCheck->Type = BIGGER_THAN;
	}
	else if (TokenToCheck->Lexeme == "<")
	{
		TokenToCheck->Type = SMALLER_THAN;
	}
	else if (TokenToCheck->Lexeme == ">=")
	{
		TokenToCheck->Type = BIGGER_THAN_EQUALS;
	}
	else if (TokenToCheck->Lexeme == "<=")
	{
		TokenToCheck->Type = SMALLER_THAN_EQUALS;
	}
	else if (TokenToCheck->Lexeme == "==")
	{
		TokenToCheck->Type = EQUALS;
	}
	else if (TokenToCheck->Lexeme == "!=")
	{
		TokenToCheck->Type = NOT_EQUALS;
	}
	else if (TokenToCheck->Lexeme == "/*")
	{
		TokenToCheck->Type = COMMENT_START;
	}
	else if (TokenToCheck->Lexeme == "*/")
	{
		TokenToCheck->Type = COMMENT_END;
	}
	else if(!(TokenToCheck->Lexeme[0] >= '0' && TokenToCheck->Lexeme[0] < '9'))
	{
		TokenToCheck->Type = ID;
	}
	else //number
	{
		if (strstr(TokenToCheck->Lexeme, '.') != NULL)
		{
			TokenToCheck->Type = REAL_NUM;
		}
		else
		{
			TokenToCheck->Type = INT_NUM;
		}
	}
}

void CreateAndStoreToken(char* Lexeme, int LineNumber, List *TokensList)
{
	Token TokenToCreate;
	TokenToCreate.Lexeme = Lexeme;
	DefineTokenType(&TokenToCreate);
	TokenToCreate.LineNumber = LineNumber;
	TokenToCreate.I_AM_HERE = false;
	if (TokenToCreate.Type == ID)
	{
		if (CheckIsLegalIdToken(TokenToCreate.Lexeme, TokenToCreate.LineNumber))
		{
			PushToEnd(TokensList, &TokenToCreate);
		}
		else
		{
			printf("Syntax Error in line %d", TokenToCreate.LineNumber);
		}
	}
}

Token NextToken(List *TokensList)
{
	List_node *nodeCurrentToken;
	int indexCurrentToken;
	bool isNext = true;
	nodeCurrentToken = FindToken(TokensList, &indexCurrentToken, isNext);
	nodeCurrentToken->data[indexCurrentToken].I_AM_HERE = false;
	nodeCurrentToken->data[indexCurrentToken + 1].I_AM_HERE = true;
	return nodeCurrentToken->data[indexCurrentToken + 1];
}

Token BackToken(List *TokensList, int* IndexCurrentToken)
{
	List_node *nodeCurrentToken;
	int indexCurrentToken;
	bool isNext = false;
	nodeCurrentToken = FindToken(TokensList, &indexCurrentToken, isNext);
	nodeCurrentToken->data[indexCurrentToken].I_AM_HERE = false;
	nodeCurrentToken->data[indexCurrentToken - 1].I_AM_HERE = true;
	return nodeCurrentToken->data[indexCurrentToken - 1];
}

List_node *FindToken(List *TokensList, int *Index, bool Is_Next)
{
	int i, j = 0;
	List_node *currentNode = TokensList->First;
	while (j < TokensList->size)
	{
		for (i = 0; i < 100; i++)
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

bool CheckIsLegalIdToken(char* LexemeToCheck, int LineNumber)
{
	//Is the first char is a letter
	if ((LexemeToCheck[0] >= 'a' && LexemeToCheck[0] <= 'z') ||
		(LexemeToCheck[0] >= 'A' && LexemeToCheck[0] <= 'Z'))
	{
		if (strstr(LexemeToCheck,"__") && (LexemeToCheck[strlen(LexemeToCheck)] != '_'))
		return true;
	}

	return false;
}