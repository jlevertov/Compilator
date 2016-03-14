#include<stdio.h>

typedef struct Token
{
	char* Type;
	char* Lexeme;
	int LineNumber;
}Token;

void DefineTokenType(Token StringToCheck, char** KeyWordsArray, int NumOfKeyWords);
void CreateAndStoreToken(char* Lexeme, int LineNumber, List *TokensList);
Token NextToken(List *TokensList, int Size, int indexCurrentToken);
Token BackToken(List *TokensList, int Size, int indexCurrentToken);
