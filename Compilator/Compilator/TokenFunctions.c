#include "Token.h"
#include"LinkedList.h"
#include<string.h>

void DefineTokenType(Token StringToCheck, char** KeyWordsArray, int NumOfKeyWords)
{
	int row, colum;
	/*is keyword*/
	for (row = 0; row < NumOfKeyWords; row++)
	{
		if (strcmp(*KeyWordsArray + row, StringToCheck.Lexeme) == 0)
		{
			StringToCheck.Type = "KeyWord";
			return;
		}
	}

	/*is Seperator*/
	if (StringToCheck.Lexeme == ":" || StringToCheck.Lexeme == ";" || StringToCheck.Lexeme == "[" || StringToCheck.Lexeme == "]")
	{
		StringToCheck.Type = "Seperator";
		return;
	}

	/*else, id*/

	else
	{
		StringToCheck.Type = "ID";
		return;
	}
}

void CreateAndStoreToken(char* Lexeme, int LineNumber, List *TokensList)
{
	Token TokenToCreate;
	TokenToCreate.Lexeme = Lexeme;
	TokenToCreate.LineNumber = LineNumber;

	PushToEnd(TokensList, TokenToCreate);
}

Token NextToken(List *TokensList, int* IndexCurrentToken)
{
	Token tToReturn;
	if (*IndexCurrentToken < TokensList->size)
	{
		tToReturn = FindToken(TokensList, IndexCurrentToken)->next->data;
		return tToReturn;
	}
	else
	{
		Token fake;
		fake.Lexeme = "EOF";
		return fake;
	}
}

Token BackToken(List *TokensList, int* IndexCurrentToken)
{
	Token tToReturn;
	if (*IndexCurrentToken < TokensList->size)
	{
		tToReturn = FindToken(TokensList, IndexCurrentToken)->previous->data;
		return tToReturn;
	}
	else
	{
		Token fake;
		fake.Lexeme = "EOF";
		return fake;
	}
}

List_node* FindToken(List *TokensList, int* IndexCurrentToken)
{
	int i;
	List_node *temp = TokensList->First;
	if (*IndexCurrentToken < TokensList->size)
	{
		for (i = 0; i != *IndexCurrentToken; i++)
		{
			temp = temp->next;
		}
		return temp;
	}
}