#define _CRT_SECURE_NO_WARNINGS
#include "Parser.h"
#include <string.h>
#define SIZE 1000

static Token t;
static bool wasError = false;
static List* tokenList;
static Table* currentHashTable;
static int keysForType[20];
static int INDEX = 0;
<<<<<<< HEAD

void UpdateTable(Table* hashTable, Attribute type);
bool MultiMatch(Token* gottenToken, Token* expectedToken);
bool match(Token* gottenToken, Token* expectedToken);
=======
>>>>>>> origin/master

void Parse_Program(List* TokenList)
{
	//Hash Table
	Table* rootHashTable = (Table*)malloc(sizeof(Table));
	rootHashTable->ParentTable = NULL;
	currentHashTable = rootHashTable;

	tokenList = TokenList;
	t = tokenList->First->data[0];
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			t = NextToken(tokenList);
		}
		printf("\n%s\n", t.Lexeme);
	switch (t.Kind)
	{
	case PROGRAM:
		Parse_Declerations();
		printf("\nProgram->Declerations");
		Token* expectedToken = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken->Lexeme, ";");
		expectedToken->Kind = CMD_SEPERATOR;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		printf("\nProgram->Declerations->;");
		Parse_Statements();
		printf("\nProgram->Declerations->;->Statemants");
		/*if(t.Kind != EOF_)*/
			//t = NextToken(tokenList);
		strcpy(expectedToken->Lexeme, "end");
		expectedToken->Kind = END;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		free(expectedToken); //freeing the memory
		printf("\nProgram->Declerations->;->Statemants->end");
		if(wasError == true)
		{
			printf("\n-----------------\nParser Finished, There were errors");
		}
		else
		{
			printf("\n-----------------\nParser Finished with full success");
		}
		break; //End of case PROGRAM
	default:
			printf("\n-----------------\nParser Error at %s, expected program, line %d\n", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file\n");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token\n");
			}

		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Declerations()
{
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case INT_NUM:
	case ID:
		t = BackToken(tokenList);
		Parse_Decleration();
		printf("\nDeclerations->Decleration");
		Token* expectedToken = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken->Lexeme, ";");
		expectedToken->Kind = CMD_SEPERATOR;

<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		printf("\nDeclerations->Decleration->;");
		t = NextToken(tokenList);
		if (t.Kind == IF || t.Kind == LOOP || t.Kind == START) //Finished Decleration starting Statemants
		{
			t = BackToken(tokenList);
		}
		else if (t.Kind == INT_NUM)
		{
			t = BackToken(tokenList);
			t = BackToken(tokenList);
			Parse_Decleration_T();
			printf("\nDeclerations->Decleration->;->Decleration_Tag");
		}
		else if (t.Kind == ID)
		{
			t = NextToken(tokenList);
			
			if (t.Kind == COMMA || t.Kind == COLON)
			{
				t = BackToken(tokenList);
				t = BackToken(tokenList);
				t = BackToken(tokenList);
				Parse_Decleration_T();
				printf("\nDeclerations->Decleration->;->Decleration_Tag");
			}
			else if (t.Kind == BRACKETS_OPEN)
			{
				int i = 1;
				while (t.Kind != INSERTION && t.Kind != COLON)
				{
					t = NextToken(tokenList);
					i++;
				}

				if (t.Kind == INSERTION)
				{
					while (i > 0)
					{
						t = BackToken(tokenList);
						i--;
					}
					
					t = BackToken(tokenList);
				}
				else if (t.Kind == COLON)
				{
					while (i > 0)
					{
						t = BackToken(tokenList);
						i--;
					}

					Parse_Decleration_T();
					printf("\nDeclerations->Decleration->;->Decleration_Tag");
				}
			}
			else if (t.Kind == INSERTION)
			{
				t = BackToken(tokenList);
				t = BackToken(tokenList);
			} 

		}

<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		printf("\nDeclerations->;");
		free(expectedToken);
		break; //End of cases INT_NUM, ID

	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			Parse_Declerations();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected id or an int number, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != CMD_SEPERATOR && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Decleration()
{
	Attribute VS_type, T_type;
	Token* expectedToken;
	t = NextToken(tokenList);
	T_type = Parse_Type();
	//VS_type = T_type;
	switch (t.Kind)
	{
	case INT_NUM:
	case ID:
<<<<<<< HEAD
		expectedToken = (Token*)malloc(sizeof(Token));
=======
		Token* expectedToken = (Token*)malloc(sizeof(Token));
>>>>>>> origin/master
		strcpy(expectedToken->Lexeme, ":");
		expectedToken->Kind = COLON;

		t = BackToken(tokenList);
		Parse_Variables_List();
		printf("\nDecleration->Variables_List");
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		printf("\nDecleration->Variables_List->:");
		Parse_Type();
		VS_type = T_type;
		UpdateTable(currentHashTable, VS_type);
		t = NextToken(tokenList);
		printf("\nDecleration->Variables_List->:->Kind");
		strcpy(expectedToken->Lexeme, ";");
		expectedToken->Kind = CMD_SEPERATOR;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		printf("\nDecleration->Variables_List->:->Kind->;");
		free(expectedToken);
		break; //End of cases INT_NUM, ID
	default:
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Decleration();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected an id or an int number, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != CMD_SEPERATOR && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Decleration_T()
{
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case CMD_SEPERATOR:
		Parse_Declerations();
		printf("\nDecleration_Tag->Decleration");
		break; //End of case CMD_SEPERATOR
	default:
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Decleration_T();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected ;, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != CMD_SEPERATOR && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; // End of default case
	} //End of switch (t.Kind)
}

Attribute Parse_Type()
{
	Attribute T_Type;
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case INT: 
	case REAL:
		printf("\nKind->Integer|Real");
		T_Type.type = t.Kind;
		break; //End of cases INT, REAL
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Type();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected 'integer' or 'real', line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != CMD_SEPERATOR && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}
		
		break; //End of default case
	} //End of switch (t.Kind)

	return T_Type;
}

void Parse_Variables_List()
{
	//Attribute V_type, VS_T_type;
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case ID:
	case INT_NUM:
		t = BackToken(tokenList);
		/*V_type = VS_type;
		VS_T_type = VS_type;*/
		Parse_Variable();
		printf("\nVariables_List->Variable");
		t = NextToken(tokenList);
		 if (t.Kind == COMMA)
		{
			t = BackToken(tokenList);
			Parse_Variables_List_T();
			printf("Varialbles_List->Variable->,->Variables_List_Tag");
		}
		printf("\nVariables_List->Variable->,->Variables_List_Tag->:");
		printf("\n|Variables_List->Variable->:");
		printf("Now at %s", t.Lexeme);
		Token* expectedToken = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken->Lexeme, ":");
		expectedToken->Kind = COLON;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		free(expectedToken);
		break; //End of cases ID, INT_NUM
	default:
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Variables_List();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected id or an int number , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != COLON && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Variables_List_T()
{
	//Attribute V_type, VS_T_R_type;
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case COMMA:
		//V_type = VS_T_type;
		Parse_Variable();
		printf("\nVariables_List_Tag->Variable");
		t = NextToken(tokenList);
		if (t.Kind == COMMA)
		{
			t = BackToken(tokenList);
			//VS_T_R_type = VS_T_type;
			Parse_Variables_List_T();
			printf("\nVariables_List_Tag->Variable->,->Variables_List_Tag");
		}
		else if(t.Kind != COLON)
		{
			wasError = true;
		}
		break; //End of case COMMA
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			//VS_T_R_type = VS_T_type;
			Parse_Variables_List_T();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected ',', line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != COLON && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Variable()
{
<<<<<<< HEAD
	bool isSuccess = false;
=======
>>>>>>> origin/master
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	/*case INT_NUM:
		printf("\nVariable->Number");
		break; //End of case INT_NUM*/
	case ID:
<<<<<<< HEAD
		isSuccess = Insert(currentHashTable, t.key, ERROR, t.Lexeme);
		if (isSuccess != true)
		{
			printf("The %s in line %d already exists in the currnet block", t.Lexeme, t.LineNumber);
		}
=======
		Insert(currentHashTable, t.key, ERROR, t.Lexeme);
>>>>>>> origin/master
		keysForType[INDEX++] = t.key;
		t = NextToken(tokenList);
		printf("\nVariable->id");
		if (t.Kind == COMMA || t.Kind == COLON)
		{
			t = BackToken(tokenList);
		}
		else if (t.Kind == BRACKETS_OPEN)
		{
			t = BackToken(tokenList);
<<<<<<< HEAD
			TableNode* tn = Search(currentHashTable, t.key);
=======
			TableNode *tn = Search(currentHashTable, t.key);
>>>>>>> origin/master
			tn->Type = ARRAY;
			Parse_Variable_T();
			printf("\nVariable->id->Variable_Tag");
		}
		else
		{
			wasError = true;
		}

		break; //End of case ID
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Variable();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected an int num or an id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != COMMA && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}
			
			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Variable_T()
{
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case BRACKETS_OPEN:
		t = NextToken(tokenList);
		printf("Variable_Tag->[");
		if (t.Kind == INT_NUM)
		{
			t = BackToken(tokenList);
			t = BackToken(tokenList); //now at id

			TableNode *tn = Search(currentHashTable, t.key);

<<<<<<< HEAD
			t = NextToken(tokenList);
			t = NextToken(tokenList); //now at int_num
			
			tn->sizeOfArray = atoi(t.Lexeme); //The array now has a size;

			t = NextToken(tokenList);
			Token* expectedToken = (Token*)malloc(sizeof(Token));
			strcpy(expectedToken->Lexeme, "]");
			expectedToken->Kind = BRACKETS_CLOSE;
			match(&t, expectedToken);
=======
			t = NextToken(tokenList);
			t = NextToken(tokenList); //now at int_num
			
			tn->sizeOfArray = atoi(t.Lexeme); //The array now has a size;

			t = NextToken(tokenList);
			Token* expectedToken = (Token*)malloc(sizeof(Token));
			strcpy(expectedToken->Lexeme, "]");
			expectedToken->Kind = BRACKETS_CLOSE;
			match(t.Lexeme, expectedToken);
>>>>>>> origin/master
			free(expectedToken);
			printf("Variable_Tag->[Number]");
		}

		break; //End of case BRACKETS_OPEN
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Variable_T();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected [ , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != COMMA && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Statements()
{
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case IF:
	case LOOP:
	case START:
	case ID:
		t = BackToken(tokenList);
		Parse_Statement(tokenList);
		printf("\nStatements->Statemant");
		//t = NextToken(tokenList);
		if (t.Kind == CMD_SEPERATOR)
		{
			t = BackToken(tokenList);
			Parse_Statements_T(tokenList);
			printf("\nStatements->Statemant->;->Statemants_Tag");
		}
		Token* expectedToken = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken->Lexeme, "end");
		expectedToken->Kind = END;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		printf("\nStatements->Statemant->end");
		free(expectedToken);
		break; //End of cases IF, LOOP, START, ID

	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Statements(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected if or loop or start or id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != END && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Statements_T()
{
	t = NextToken(tokenList);
	//match(&t, ";");
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case IF:
	case LOOP:
	case START:
	case ID:
		t = BackToken(tokenList);
		Parse_Statements(tokenList);
		//t = NextToken(tokenList);
		Token* expectedToken = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken->Lexeme, "end");
		expectedToken->Kind = END;
<<<<<<< HEAD
		match(&t, expectedToken); 
=======
		match(t.Lexeme, expectedToken); 
>>>>>>> origin/master
		printf("\nStatements_Tag->Statemants->end");
		free(expectedToken);
		break; //End of cases IF, LOOP, START, ID
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Statements_T(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected if or loop or start or id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;	  
			while (t.Kind != END && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Kind)
}

void Parse_Statement()
{
	Attribute R_Type, E_Type;
	t = NextToken(tokenList);
	Token* expectedToken = (Token*)malloc(sizeof(Token));
<<<<<<< HEAD
	Table *ht = (Table*)malloc(sizeof(Table));
	switch (t.Kind)
	{
	case IF:
		Parse_Condition();
		strcpy(expectedToken->Lexeme, "then");
		expectedToken->Kind = THEN;
		match(&t, expectedToken);
=======
	switch (t.Kind)
	{
	case IF:
		Parse_Condition(tokenList);
		strcpy(expectedToken->Lexeme, "then");
		expectedToken->Kind = THEN;
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		
		Parse_Statement(tokenList);
		strcpy(expectedToken->Lexeme, "else");
		expectedToken->Kind = ELSE;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		
		Parse_Statement(tokenList);
		strcpy(expectedToken->Lexeme, "end_if");
		expectedToken->Kind = END_IF;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		
		t = NextToken(tokenList);
		printf("\nStatement->if->Condition->then->Statemant->else->Statemant->end_if");
		break; //End of case IF
	case LOOP:
		Parse_Statement(tokenList);
		strcpy(expectedToken->Lexeme, "until");
		expectedToken->Kind = UNTIL;
<<<<<<< HEAD
		match(&t, expectedToken);
		
		Parse_Condition();
		strcpy(expectedToken->Lexeme, "end_loop");
		expectedToken->Kind = END_LOOP;
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
		
		Parse_Condition(tokenList);
		strcpy(expectedToken->Lexeme, "end_loop");
		expectedToken->Kind = END_LOOP;
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		printf("\nStatement->loop->Statemant->until->Condition->end_loop");
		break; //End of case LOOP
	case START:
		//Create new Hash table, make her the current
<<<<<<< HEAD
=======
		Table *ht = (Table*)malloc(sizeof(Table));
>>>>>>> origin/master
		ht->ParentTable = currentHashTable;
		currentHashTable = ht;

		Parse_Declerations(tokenList);
		strcpy(expectedToken->Lexeme, ";");
		expectedToken->Kind = CMD_SEPERATOR;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		
		Parse_Statements(tokenList);
		strcpy(expectedToken->Lexeme, "end");
		expectedToken->Kind = END;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		
		printf("\nStatement->Start->Declerations->;->Statemants->end");
		break; //End of case START
	case ID:
		t = BackToken(tokenList);
		
		R_Type = Parse_Receiver();
		strcpy(expectedToken->Lexeme, "=");
		expectedToken->Kind = INSERTION;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		E_Type = Parse_Expression();
		printf("\nStatement->Receiver->=->Expression");
		
		strcpy(expectedToken->Lexeme, ";");
		expectedToken->Kind = CMD_SEPERATOR;

		Token* expectedToken2 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken2->Lexeme, "else");
		expectedToken2->Kind = ELSE;
		
		Token* expectedToken3 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken3->Lexeme, "end_if");
		expectedToken3->Kind = END_IF;
		
		Token* expectedToken4 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken4->Lexeme, "end");
		expectedToken4->Kind = END;
		
		Token* expectedToken5 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken5->Lexeme, "until");
		expectedToken5->Kind = UNTIL;
		
<<<<<<< HEAD
		if (!(MultiMatch(&t, expectedToken) ||
			MultiMatch(&t, expectedToken2) ||
			MultiMatch(&t, expectedToken3) ||
			MultiMatch(&t, expectedToken4) ||
			MultiMatch(&t, expectedToken5)))
=======
		if (!(MultiMatch(t.Lexeme, expectedToken) ||
			MultiMatch(t.Lexeme, expectedToken2) ||
			MultiMatch(t.Lexeme, expectedToken3) ||
			MultiMatch(t.Lexeme, expectedToken4) ||
			MultiMatch(t.Lexeme, expectedToken5)))
>>>>>>> origin/master
		{
			wasError = true;
		}
		
		if (R_Type.type != E_Type.type)
		{
<<<<<<< HEAD
			printf("\nSemantic Error, type missmatch in line: %d",t.LineNumber);
=======
			printf("Semantic Error");
>>>>>>> origin/master
		}
		free(expectedToken);
		free(expectedToken2);
		free(expectedToken3);
		free(expectedToken4);
		free(expectedToken5);
		break; //End of case ID
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Statement();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected if or loop or start or id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != END_IF && t.Kind != UNTIL && t.Kind != END && t.Kind != CMD_SEPERATOR  && t.Kind != ELSE && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}
		
		break; //End of default case
	} //End of switch (t.Kind)
}

Attribute Parse_Receiver()
{
	Attribute R_Type, R_T_Type;
<<<<<<< HEAD
	TableNode *tb;
=======
>>>>>>> origin/master
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case ID:
<<<<<<< HEAD
		tb = Search(currentHashTable, t.key);
		if (tb == NULL)
		{
			printf("\nVariable %s doesn't exist.", t.Lexeme);
			R_Type.type = ERROR;
		}
		else
		{
			R_Type.type = tb->Type;
		}
		/*if (strcmp(tb->LexemeOfID, t.Lexeme) != 0)
		{
			printf("Semantic Error, ");
		}*/
=======
		TableNode *tb = Search(currentHashTable, t.key);
		R_Type.type = tb->Type;
		if (strcmp(tb->LexemeOfID, t.Lexeme) != 0)
		{
			printf("Semantic Error");
		}
>>>>>>> origin/master
		
		t = NextToken(tokenList);
		printf("\nReceiver->id");
		if (t.Kind == BRACKETS_OPEN)
		{
			if (R_Type.type != ARRAY_OF_INTEGERS && R_Type.type != ARRAY_OF_REALS)
			{
<<<<<<< HEAD
				t = BackToken(tokenList);
				printf("Semantic Error, %s is not difined as an array (line: %d)", t.Lexeme, t.LineNumber);
				t = NextToken(tokenList);
=======
				printf("Semantic Error");
>>>>>>> origin/master
				R_T_Type.type = ERROR;
			}
			else
			{
				R_T_Type.type = tb->Type;
				t = BackToken(tokenList);
				Parse_Receiver_T(R_T_Type);
				t = NextToken(tokenList);
				printf("\nReceiver->id->Receiver_Tag");
			}
		}
		Token* expectedToken = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken->Lexeme, "=");
		expectedToken->Kind = INSERTION;
<<<<<<< HEAD
		match(&t, expectedToken);
=======
		match(t.Lexeme, expectedToken);
>>>>>>> origin/master
		printf("Receiver->id->Receiver_Tag->=");
		printf("\n|Receiver->id->=");
		free(expectedToken);
		break; //End of case ID
	default:
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Receiver();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected an id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != EQUALS && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}
			
			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Kind)

	return R_Type;
}

void Parse_Receiver_T(Attribute R_T_type)
{
	Attribute E_Type;
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case BRACKETS_OPEN:
<<<<<<< HEAD
		E_Type = Parse_Expression();
		Token* expectedToken = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken->Lexeme, "]");
		expectedToken->Kind = BRACKETS_CLOSE;
		match(&t, expectedToken);
		printf("\nReceiver_Tag->[->Expression->]");
		free(expectedToken);
		if ((R_T_type.type != ARRAY_OF_INTEGERS && R_T_type.type != ARRAY_OF_REALS))
		{
			t = BackToken(tokenList);
			printf("Semantic Error, %s is not difined as an array (line: %d)", t.Lexeme, t.LineNumber);
			t = NextToken(tokenList);
			R_T_type.type = ERROR;
		}
		if (E_Type.type != INT_NUM)
		{
			printf("Semantic Error, the expression is not an integer line: %d",t.LineNumber);
=======
		Parse_Expression(tokenList);
		Token* expectedToken = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken->Lexeme, "]");
		expectedToken->Kind = BRACKETS_CLOSE;
		match(t.Lexeme, expectedToken);
		printf("\nReceiver_Tag->[->Expression->]");
		free(expectedToken);
		if ((R_T_type.type != ARRAY_OF_INTEGERS || R_T_type.type != ARRAY_OF_REALS)
			&& E_Type.type != INT_NUM)
		{
			printf("Semantic Error");
>>>>>>> origin/master
		}
		break; //End of case BRACKETS_OPEN
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Receiver_T(R_T_type);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected [ , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != INSERTION && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; //End of default case
	} //End of switch (t.Kind)
}

Attribute Parse_Expression()
{
	Attribute E_Type, E_T_Type;
<<<<<<< HEAD
	TableNode *tb = Search(currentHashTable, t.key);
=======
>>>>>>> origin/master
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case INT_NUM:
	case REAL_NUM:
		if (t.Kind == INT_NUM)
		{
			E_Type.type = INT_NUM;
		}
		else
		{
			E_Type.type = REAL_NUM;
		}
		t = NextToken(tokenList);
		printf("\nExpression->number");
		break; //End of case INT_NUM, REAL_NUM
	case ID:
<<<<<<< HEAD
		tb = Search(currentHashTable, t.key);
		if (tb == NULL)
		{
			E_T_Type.type = ERROR;
			E_Type.type = ERROR;
		}
		else
		{
			E_Type.type = tb->Type;
			E_T_Type.type = E_Type.type;
		}
		/*if (strcmp(t.Lexeme, tb->LexemeOfID) != 0)
		{
			printf("Semantic Error, ");
			E_T_Type.type = ERROR;
			E_Type.type = ERROR;
		}*/						          
=======
		TableNode *tb = Search(currentHashTable, t.key);
		E_Type.type = tb->Type;
		E_T_Type.type = E_Type.type;
		if (strcmp(t.Lexeme, tb->LexemeOfID) != 0)
		{
			printf("Semantic Error");
			E_T_Type.type = ERROR;
			E_Type.type = ERROR;
		}
>>>>>>> origin/master
		t = NextToken(tokenList);
		if (t.Kind == BRACKETS_OPEN ||
			t.Kind == ADD_OP ||
			t.Kind == MUL_OP)
		{
			t = BackToken(tokenList);
			E_T_Type = Parse_Expression_T(E_T_Type);
			if (E_Type.type != E_T_Type.type)
			{
				if (!(E_Type.type == REAL_NUM && E_T_Type.type == INT_NUM)
					|| E_T_Type.type == ERROR || E_Type.type == ERROR)
				{
<<<<<<< HEAD
					printf("\nSemantic Error, type missmatch in line: %d.",t.LineNumber);
=======
					printf("Semantic Error");
>>>>>>> origin/master
					E_Type.type = ERROR;
				}
				else if (E_Type.type == REAL_NUM && E_T_Type.type == INT_NUM)
				{
					E_Type.type = REAL_NUM;
				}
			}
			printf("\nExpression->id->[|+|*->Expression_Tag");
		}
		break; //End of case ID

		
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Expression();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected a number or an id , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != BRACKETS_CLOSE && t.Kind != REAL_NUM && t.Kind != CMD_SEPERATOR && t.Kind != END_IF && t.Kind != ELSE && t.Kind != END && t.Kind != UNTIL && t.Kind != EOF_
				&& t.Kind != BIGGER_THAN && t.Kind != SMALLER_THAN && t.Kind != BIGGER_THAN_EQUALS && t.Kind != SMALLER_THAN_EQUALS && t.Kind != EQUALS && t.Kind != NOT_EQUALS && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End if default case
	} //End of switch (t.Kind)
	Token* expectedToken1 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken1->Lexeme, "]");
	expectedToken1->Kind = BRACKETS_CLOSE;

	Token* expectedToken2 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken2->Lexeme, "else");
	expectedToken2->Kind = ELSE;

	Token* expectedToken3 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken3->Lexeme, "end");
	expectedToken3->Kind = END;

	Token* expectedToken4 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken4->Lexeme, "end_loop");
	expectedToken4->Kind = END_LOOP;

	Token* expectedToken5 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken5->Lexeme, ">=");
	expectedToken5->Kind = BIGGER_THAN_EQUALS;

	Token* expectedToken6 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken6->Lexeme, "==");
	expectedToken6->Kind = EQUALS;

	Token* expectedToken7 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken7->Lexeme, "then");
	expectedToken7->Kind = THEN;
<<<<<<< HEAD

	Token* expectedToken8 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken8->Lexeme, ";");
	expectedToken8->Kind = CMD_SEPERATOR;

	Token* expectedToken9 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken9->Lexeme, "end_if");
	expectedToken9->Kind = END_IF;

	Token* expectedToken10 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken10->Lexeme, "until");
	expectedToken10->Kind = UNTIL;

	Token* expectedToken11 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken11->Lexeme, ">");
	expectedToken11->Kind = BIGGER_THAN;

	Token* expectedToken12 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken12->Lexeme, "<");
	expectedToken12->Kind = SMALLER_THAN;

	Token* expectedToken13 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken13->Lexeme, "<=");
	expectedToken13->Kind = SMALLER_THAN_EQUALS;

=======

	Token* expectedToken8 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken8->Lexeme, ";");
	expectedToken8->Kind = CMD_SEPERATOR;

	Token* expectedToken9 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken9->Lexeme, "end_if");
	expectedToken9->Kind = END_IF;

	Token* expectedToken10 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken10->Lexeme, "until");
	expectedToken10->Kind = UNTIL;

	Token* expectedToken11 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken11->Lexeme, ">");
	expectedToken11->Kind = BIGGER_THAN;

	Token* expectedToken12 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken12->Lexeme, "<");
	expectedToken12->Kind = SMALLER_THAN;

	Token* expectedToken13 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken13->Lexeme, "<=");
	expectedToken13->Kind = SMALLER_THAN_EQUALS;

>>>>>>> origin/master
	Token* expectedToken14 = (Token*)malloc(sizeof(Token));
	strcpy(expectedToken14->Lexeme, "!=");
	expectedToken14->Kind = NOT_EQUALS;
	
<<<<<<< HEAD
	if (!(MultiMatch(&t, expectedToken1) ||
		MultiMatch(&t, expectedToken2) ||
		MultiMatch(&t, expectedToken3) ||
		MultiMatch(&t, expectedToken4) ||
		MultiMatch(&t, expectedToken5) ||
		MultiMatch(&t, expectedToken6) ||
		MultiMatch(&t, expectedToken7) ||
		MultiMatch(&t, expectedToken8) ||
		MultiMatch(&t, expectedToken9) ||
		MultiMatch(&t, expectedToken10) ||
		MultiMatch(&t, expectedToken11) ||
		MultiMatch(&t, expectedToken12) ||
		MultiMatch(&t, expectedToken13) ||
		MultiMatch(&t, expectedToken14))) //if all are false
=======
	if (!(MultiMatch(t.Lexeme, expectedToken1) ||
		MultiMatch(t.Lexeme, expectedToken2) ||
		MultiMatch(t.Lexeme, expectedToken3) ||
		MultiMatch(t.Lexeme, expectedToken4) ||
		MultiMatch(t.Lexeme, expectedToken5) ||
		MultiMatch(t.Lexeme, expectedToken6) ||
		MultiMatch(t.Lexeme, expectedToken7)	||
		MultiMatch(t.Lexeme, expectedToken8) ||
		MultiMatch(t.Lexeme, expectedToken9) ||
		MultiMatch(t.Lexeme, expectedToken10) ||
		MultiMatch(t.Lexeme, expectedToken11) ||
		MultiMatch(t.Lexeme, expectedToken12) ||
		MultiMatch(t.Lexeme, expectedToken13) ||
		MultiMatch(t.Lexeme, expectedToken14))) //if all are false
>>>>>>> origin/master
	{
		wasError = true;
	}

	free(expectedToken1);
	free(expectedToken2);
	free(expectedToken3);
	free(expectedToken4);
	free(expectedToken5);
	free(expectedToken6);
	free(expectedToken7);
	free(expectedToken8);
	free(expectedToken9);
	free(expectedToken10);
	free(expectedToken11);
	free(expectedToken12);
	free(expectedToken13);
	free(expectedToken14);

	return E_Type;
}

Attribute Parse_Expression_T(Attribute E_T_type)
{
	Attribute E_Type;
	t = NextToken(tokenList);
	Token* expectedToken = (Token*)malloc(sizeof(Token));
	switch (t.Kind)
	{
	case BRACKETS_OPEN:
<<<<<<< HEAD
		E_Type = Parse_Expression();
		strcpy(expectedToken->Lexeme, "]");
		expectedToken->Kind = BRACKETS_CLOSE;
		match(&t, expectedToken);
		printf("\nExpression_Tag->[->Expression->]");
		if ((E_T_type.type != ARRAY_OF_INTEGERS && E_T_type.type != ARRAY_OF_REALS))
		{
			t = BackToken(tokenList);
			printf("Semantic Error, %s is not difined as an array (line: %d)", t.Lexeme, t.LineNumber);
			t = NextToken(tokenList);
			E_T_type.type = ERROR;
		}
		if (E_Type.type != INT_NUM)
		{
			printf("Semantic Error, the expression is not an integer line: %d", t.LineNumber);
=======
		E_Type = Parse_Expression(tokenList);
		strcpy(expectedToken->Lexeme, "]");
		expectedToken->Kind = BRACKETS_CLOSE;
		match(t.Lexeme, expectedToken);
		printf("\nExpression_Tag->[->Expression->]");
		if ((E_T_type.type != ARRAY_OF_INTEGERS || E_T_type.type != ARRAY_OF_REALS) &&
			E_Type.type != INT_NUM)
		{
			printf("Semantic Error");
>>>>>>> origin/master
			E_T_type.type = ERROR;
		}
		free(expectedToken);
		break; //End of case BRACKETS_OPEN
	case ADD_OP:
	case MUL_OP:
<<<<<<< HEAD
		E_Type = Parse_Expression();
=======
		E_Type = Parse_Expression(tokenList);
>>>>>>> origin/master
		Token* expectedToken1 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken1->Lexeme, "]");
		expectedToken1->Kind = BRACKETS_CLOSE;

		Token* expectedToken2 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken2->Lexeme, "else");
		expectedToken2->Kind = ELSE;

		Token* expectedToken3 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken3->Lexeme, "end");
		expectedToken3->Kind = END;

		Token* expectedToken4 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken4->Lexeme, "end_loop");
		expectedToken4->Kind = END_LOOP;

		Token* expectedToken5 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken5->Lexeme, ">=");
		expectedToken5->Kind = BIGGER_THAN_EQUALS;

		Token* expectedToken6 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken6->Lexeme, "==");
		expectedToken6->Kind = EQUALS;

		Token* expectedToken8 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken8->Lexeme, ";");
		expectedToken8->Kind = CMD_SEPERATOR;

		Token* expectedToken9 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken9->Lexeme, "end_if");
		expectedToken9->Kind = END_IF;

		Token* expectedToken10 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken10->Lexeme, "until");
		expectedToken10->Kind = UNTIL;

		Token* expectedToken11 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken11->Lexeme, ">");
		expectedToken11->Kind = BIGGER_THAN;

		Token* expectedToken12 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken12->Lexeme, "<");
		expectedToken12->Kind = SMALLER_THAN;

		Token* expectedToken13 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken13->Lexeme, "<=");
		expectedToken13->Kind = SMALLER_THAN_EQUALS;

		Token* expectedToken14 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken14->Lexeme, "!=");
		expectedToken14->Kind = NOT_EQUALS;
		printf("\nExpression_Tag->+|*->Expression");
<<<<<<< HEAD
		if (!(MultiMatch(&t, expectedToken1) ||
			MultiMatch(&t, expectedToken2) ||
			MultiMatch(&t, expectedToken3) ||
			MultiMatch(&t, expectedToken4) ||
			MultiMatch(&t, expectedToken5) ||
			MultiMatch(&t, expectedToken6) ||
			MultiMatch(&t, expectedToken8) ||
			MultiMatch(&t, expectedToken9) ||
			MultiMatch(&t, expectedToken10) ||
			MultiMatch(&t, expectedToken11) ||
			MultiMatch(&t, expectedToken12) ||
			MultiMatch(&t, expectedToken13) ||
			MultiMatch(&t, expectedToken14))) //if all are false
=======
		if (!(MultiMatch(t.Lexeme, expectedToken1) ||
			MultiMatch(t.Lexeme, expectedToken2) ||
			MultiMatch(t.Lexeme, expectedToken3) ||
			MultiMatch(t.Lexeme, expectedToken4) ||
			MultiMatch(t.Lexeme, expectedToken5) ||
			MultiMatch(t.Lexeme, expectedToken6) ||
			MultiMatch(t.Lexeme, expectedToken8) ||
			MultiMatch(t.Lexeme, expectedToken9) ||
			MultiMatch(t.Lexeme, expectedToken10) ||
			MultiMatch(t.Lexeme, expectedToken11) ||
			MultiMatch(t.Lexeme, expectedToken12) ||
			MultiMatch(t.Lexeme, expectedToken13) ||
			MultiMatch(t.Lexeme, expectedToken14))) //if all are false
>>>>>>> origin/master
		{
			wasError = true;
		}

		if (E_Type.type != E_T_type.type)
		{
			if (!(E_T_type.type == REAL_NUM && E_Type.type == INT_NUM)
				|| E_T_type.type == ERROR || E_Type.type == ERROR)
			{
<<<<<<< HEAD
				printf("Semantic Error, type missmatch line: %d", t.LineNumber);
=======
				printf("Semantic Error");
>>>>>>> origin/master
				E_T_type.type = ERROR;
			}
			else if (E_T_type.type == REAL_NUM && E_Type.type == INT_NUM)
			{
				E_T_type.type = REAL_NUM;
			}
		}
		free(expectedToken1);
		free(expectedToken2);
		free(expectedToken3);
		free(expectedToken4);
		free(expectedToken5);
		free(expectedToken6);
		free(expectedToken8);
		free(expectedToken9);
		free(expectedToken10);
		free(expectedToken11);
		free(expectedToken12);
		free(expectedToken13);
		free(expectedToken14);
		break; //End of case ADD_OP, MUL_OP
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Expression_T(E_T_type);
		}
		else
		{	
			printf("\n-----------------\nParser Error at %s, expected + or * or [ , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != BRACKETS_CLOSE && t.Kind != CMD_SEPERATOR && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Kind == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; //End of default case
	} //End of switch (t.Kind)

	return E_T_type;
}

void Parse_Condition()
{
	Attribute E_L_Type, E_R_Type;
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case INT_NUM:
	case REAL_NUM:
	case ID:
		t = BackToken(tokenList);

		Token* expectedToken7 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken7->Lexeme, "end_loop");
		expectedToken7->Kind = END_LOOP;

		Token* expectedToken2 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken2->Lexeme, ">=");
		expectedToken2->Kind = BIGGER_THAN_EQUALS;

		Token* expectedToken3 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken3->Lexeme, "==");
		expectedToken3->Kind = EQUALS;

		Token* expectedToken4 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken4->Lexeme, ">");
		expectedToken4->Kind = BIGGER_THAN;

		Token* expectedToken5 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken5->Lexeme, "<");
		expectedToken5->Kind = SMALLER_THAN;

		Token* expectedToken6 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken6->Lexeme, "<=");
		expectedToken6->Kind = SMALLER_THAN_EQUALS;

		Token* expectedToken1 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken1->Lexeme, "!=");
		expectedToken1->Kind = NOT_EQUALS;

		Token* expectedToken8 = (Token*)malloc(sizeof(Token));
		strcpy(expectedToken8->Lexeme, "then");
		expectedToken8->Kind = THEN;

		E_L_Type = Parse_Expression();
<<<<<<< HEAD
		if (MultiMatch(&t, expectedToken1) ||
			MultiMatch(&t, expectedToken2) ||
			MultiMatch(&t, expectedToken3) ||
			MultiMatch(&t, expectedToken4) ||
			MultiMatch(&t, expectedToken5) ||
			MultiMatch(&t, expectedToken6))
		{
			E_R_Type = Parse_Expression();
			if (!(MultiMatch(&t, expectedToken7) ||
				MultiMatch(&t, expectedToken8)))
=======
		if (MultiMatch(t.Lexeme, expectedToken1) ||
			MultiMatch(t.Lexeme, expectedToken2) ||
			MultiMatch(t.Lexeme, expectedToken3) ||
			MultiMatch(t.Lexeme, expectedToken4) ||
			MultiMatch(t.Lexeme, expectedToken5) ||
			MultiMatch(t.Lexeme, expectedToken6))
		{
			E_R_Type = Parse_Expression();
			if (!(MultiMatch(t.Lexeme, expectedToken7) ||
				MultiMatch(t.Lexeme, expectedToken8)))
>>>>>>> origin/master
			{
				printf("\n-----------------\nParser Error at %s, expected end_loop or then, line %d", t.Lexeme, t.LineNumber);
				wasError = true;
			}
			
			printf("\nCondition->id|number->Expression->end_loop|then");

			if (E_L_Type.type != E_R_Type.type)
			{
<<<<<<< HEAD
				printf("Semantic Error, type missmatch line: %d",t.LineNumber);
=======
				printf("Semantic Error");
>>>>>>> origin/master
			}
		}
		else
		{
			wasError = true;
			printf("\n-----------------\nParser Error at %s, expected a relation operation, line %d", t.Lexeme, t.LineNumber);
		}	
		free(expectedToken1);
		free(expectedToken2);
		free(expectedToken3);
		free(expectedToken4);
		free(expectedToken5);
		free(expectedToken6);
		free(expectedToken7);
		free(expectedToken8);
		break; // End of case INT_NUM, REAL_NUM, ID
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Condition();
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected a number or an id , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Kind != THEN && t.Kind != END_LOOP && t.Kind != EOF_ && t.Kind != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Kind == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if(t.Kind != ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch(t.Kind)

}

bool match(Token* gottenToken, Token* expectedToken)
{
	if (wasError == false)
	{
		if (gottenToken->Kind != expectedToken->Kind)
		{
			printf("\n-----------------\nParser Error at %s, expected %s at line %d", gottenToken->Lexeme, expectedToken->Lexeme, gottenToken->LineNumber);
			wasError = true;
			return false;
		}
	}

	return true;
}

//Same as match but not changing wasError to true
bool MultiMatch(Token* gottenToken, Token* expectedToken)
{
	if (gottenToken->Kind != expectedToken->Kind)
	{
		return false;
	}

	return true;
}

void UpdateTable(Table* hashTable, Attribute type)
{
	
	for (int i = 0; i < INDEX; i++)
	{
		TableNode* currentKeyValue = Search(hashTable, keysForType[i]);
		if (currentKeyValue->Type == ARRAY) //If it is an array, now the array gets the type
		{
			currentKeyValue->Type = (type.type == INT ? ARRAY_OF_INTEGERS : ARRAY_OF_REALS);
		}
		else //Else, regular veriable now gets the type
		{
			currentKeyValue->Type = type.type;
		}
	}

	INDEX = 0;
}