/*lists*/
#include<stdio.h>
#include<stdlib.h>
#define bool int
#define true 1
#define false 0

typedef struct Token
{
	char* Type;
	char* Lexeme;
	int LineNumber;
	bool I_AM_HERE;
}Token;

typedef struct List_node
{
	 Token data[100];
	 int CurrentArrayIndex;
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
bool IsEmpty( List *l);
void PushToEnd( List *l, Token *TokenToAdd);
int Size( List *l);
struct List_node* FindToken( List* TokensList, int* Index, bool Is_Next);

void DefineTokenType(Token StringToCheck);
void CreateAndStoreToken(char* Lexeme, int LineNumber, List *TokensList);
Token NextToken(List *TokensList, int Size, int indexCurrentToken);
Token BackToken(List *TokensList, int Size, int indexCurrentToken);
bool CheckIsLegalIdToken(char* LexemeToCheck, int LineNumber);

enum KeyWords
{
	START, //keyword
	END,//keyword
	PROGRAM,//keyword
	LOOP,//keyword
	UNTIL,// keyword
	END_LOOP,// keyword
	IF,// keyword
	ELSE,// keyword
	END_IF,// keyword
	INT,// keyword
	REAL,// keyword
	ADD_OP, //+
	MUl_OP, //*
	CMD_SEPERATOR, // ;
	COMMA, // ,
	COLON,// :
	BRACKETS_OPEN,// [
	BRACKETS_CLOSE,// ]
	BIGGER_THAN, // >
	SMALLER_THAN, //<
	EQUALS, // ==
	NOT_EQUALS, //!=
	BIGGER_THAN_EQUALS, // >=
	SMALLER_THAN_EQUALS, // <=
	ID,
	ERROR,
	COMMENT_START, // /*
	COMMENT_END, // */
	INT_NUM,
	REAL_NUM,
};
