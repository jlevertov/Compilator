#include "Parser.h"
#include <string.h>

static Token t;
static bool wasError = false;
static List* tokenList;

void Parse_Program(List* TokenList)
{
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
		Parse_Declerations(tokenList);
		printf("\nProgram->Declerations");
		match(t.Lexeme, ";");
		printf("\nProgram->Declerations->;");
		Parse_Statements(tokenList);
		printf("\nProgram->Declerations->;->Statemants");
		/*if(t.Kind != EOF_)*/
			//t = NextToken(tokenList);
		match(t.Lexeme, "end");
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
		Parse_Decleration(tokenList);
		printf("\nDeclerations->Decleration");
		match(t.Lexeme, ";");
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
			Parse_Decleration_T(tokenList);
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
				Parse_Decleration_T(tokenList);
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

					Parse_Decleration_T(tokenList);
					printf("\nDeclerations->Decleration->;->Decleration_Tag");
				}
			}
			else if (t.Kind == INSERTION)
			{
				t = BackToken(tokenList);
				t = BackToken(tokenList);
			} 

		}

		match(t.Lexeme, ";");
		printf("\nDeclerations->;");
		break; //End of cases INT_NUM, ID

	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			Parse_Declerations(tokenList);
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
	Token currentToken;
	Attribute VS_type, T_type;
	t = NextToken(tokenList);
	currentToken = t;
	while (t.Kind != COLON && t.Kind!=EOF_)
	{
		t = NextToken(tokenList);
	}
	if (t.Kind == EOF_)
	{
		printf("\nUnexpected end of file");
		exit(1);
	} 
	//else
	T_type = Parse_Type();
	VS_type = T_type;
	while (&t != &currentToken) //maybe will work
	{
		t = BackToken(tokenList);
	}
	switch (t.Kind)
	{
	case INT_NUM:
	case ID:
		t = BackToken(tokenList);
		Parse_Variables_List(VS_type);
		printf("\nDecleration->Variables_List");
		match(t.Lexeme, ":");
		printf("\nDecleration->Variables_List->:");
		// Parse_Type(); in order to solve the problem of inherited from T to VS
		//t = NextToken(tokenList);
		while (t.Kind != CMD_SEPERATOR && t.Kind != EOF_)
		{
			t = NextToken(tokenList);
		}
		if (t.Kind == EOF_)
		{
			printf("\nUnexpected end of file");
			exit(1);
		}
		printf("\nDecleration->Variables_List->:->Kind");
		match(t.Lexeme, ";");
		printf("\nDecleration->Variables_List->:->Kind->;");
		break; //End of cases INT_NUM, ID
	default:
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Decleration(tokenList);
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
		Parse_Declerations(tokenList);
		printf("\nDecleration_Tag->Decleration");
		break; //End of case CMD_SEPERATOR
	default:
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Decleration_T(tokenList);
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
			
			Parse_Kind(tokenList);
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

void Parse_Variables_List(Attribute VS_type)
{
	Attribute V_type, VS_T_type;
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case ID:
	case INT_NUM:
		t = BackToken(tokenList);
		V_type = VS_type;
		VS_T_type = VS_type;
		Parse_Variable(V_type);
		printf("\nVariables_List->Variable");
		t = NextToken(tokenList);
		 if (t.Kind == COMMA)
		{
			t = BackToken(tokenList);
			Parse_Variables_List_T(VS_T_type);
			printf("Varialbles_List->Variable->,->Variables_List_Tag");
		}
		printf("\nVariables_List->Variable->,->Variables_List_Tag->:");
		printf("\n|Variables_List->Variable->:");
		printf("Now at %s", t.Lexeme);
		match(t.Lexeme, ":");
		break; //End of cases ID, INT_NUM
	default:
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Variables_List(VS_T_type);
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

void Parse_Variables_List_T(Attribute VS_T_type)
{
	Attribute V_type, VS_T_R_type;
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case COMMA:
		V_type = VS_T_type;
		Parse_Variable(V_type);
		printf("\nVariables_List_Tag->Variable");
		t = NextToken(tokenList);
		if (t.Kind == COMMA)
		{
			t = BackToken(tokenList);
			VS_T_R_type = VS_T_type;
			Parse_Variables_List_T(VS_T_R_type);
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
			VS_T_R_type = VS_T_type;
			Parse_Variables_List_T(VS_T_R_type);
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

void Parse_Variable(Attribute V_type)
{
	Attribute v;
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case INT_NUM:
		printf("\nVariable->Number");
		break; //End of case INT_NUM
	case ID:
		t = NextToken(tokenList);
		printf("\nVariable->id");
		if (t.Kind == COMMA || t.Kind == COLON)
		{
			t = BackToken(tokenList);
		}
		else if (t.Kind == BRACKETS_OPEN)
		{
			t = BackToken(tokenList);
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

void Parse_Variable_T(Attribute V_type)
{
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case BRACKETS_OPEN:
		t = NextToken(tokenList);
		printf("Variable_Tag->[");
		if (t.Kind == INT_NUM)
		{
			t = NextToken(tokenList);
			match(t.Lexeme, "]");
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

		match(t.Lexeme, "end");
		printf("\nStatements->Statemant->end");
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
	//match(t.Lexeme, ";");
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
		match(t.Lexeme, "end"); 
		printf("\nStatements_Tag->Statemants->end");
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
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case IF:
		Parse_Condition(tokenList);
		match(t.Lexeme, "then");
		Parse_Statement(tokenList);
		match(t.Lexeme, "else");
		Parse_Statement(tokenList);
		match(t.Lexeme, "end_if");
		t = NextToken(tokenList);
		printf("\nStatement->if->Condition->then->Statemant->else->Statemant->end_if");
		break; //End of case IF
	case LOOP:
		Parse_Statement(tokenList);
		match(t.Lexeme, "until");
		Parse_Condition(tokenList);
		match(t.Lexeme, "end_loop");
		printf("\nStatement->loop->Statemant->until->Condition->end_loop");
		break; //End of case LOOP
	case START:
		Parse_Declerations(tokenList);
		match(t.Lexeme, ";");
		Parse_Statements(tokenList);
		match(t.Lexeme, "end");
		printf("\nStatement->Start->Declerations->;->Statemants->end");
		break; //End of case START
	case ID:
		t = BackToken(tokenList);
		Parse_Receiver(tokenList);
		match(t.Lexeme, "=");
		Parse_Expression(tokenList);
		printf("\nStatement->Receiver->=->Expression");
		if (!(MultiMatch(t.Lexeme, ";") ||
			MultiMatch(t.Lexeme, "else") ||
			MultiMatch(t.Lexeme, "end_if") ||
			MultiMatch(t.Lexeme, "end") ||
			MultiMatch(t.Lexeme, "until")))
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
			
			Parse_Statement(tokenList);
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
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case ID:
		t = NextToken(tokenList);
		printf("\nReceiver->id");
		if (t.Kind == BRACKETS_OPEN)
		{
			t = BackToken(tokenList);
			Parse_Receiver_T();
			t = NextToken(tokenList);
			printf("\nReceiver->id->Receiver_Tag");
		}
		match(t.Lexeme, "=");
		printf("Receiver->id->Receiver_Tag->=");
		printf("\n|Receiver->id->=");
		break; //End of case ID
	default:
	if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Receiver(tokenList);
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
}

void Parse_Receiver_T(Attribute R_T_type)
{
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case BRACKETS_OPEN:
		Parse_Expression(tokenList);
		match(t.Lexeme, "]");
		printf("\nReceiver_Tag->[->Expression->]");
		break; //End of case BRACKETS_OPEN
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Receiver_T();
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
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case INT_NUM:
	case REAL_NUM:
		t = NextToken(tokenList);
		printf("\nExpression->number");
		break; //End of case INT_NUM, REAL_NUM
	case ID:				
		t = NextToken(tokenList);
		if (t.Kind == BRACKETS_OPEN ||
			t.Kind == ADD_OP ||
			t.Kind == MUL_OP)
		{
			t = BackToken(tokenList);
			Parse_Expression_T();
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

	if (!(MultiMatch(t.Lexeme, "]") ||
		MultiMatch(t.Lexeme, ";") ||
		MultiMatch(t.Lexeme, "else") ||
		MultiMatch(t.Lexeme, "end_if") ||
		MultiMatch(t.Lexeme, "end") ||
		MultiMatch(t.Lexeme, "until") ||
		MultiMatch(t.Lexeme, "end_loop") ||
		MultiMatch(t.Lexeme, ">") ||
		MultiMatch(t.Lexeme, "<") ||
		MultiMatch(t.Lexeme, ">=") ||
		MultiMatch(t.Lexeme, "<=") ||
		MultiMatch(t.Lexeme, "==") ||
		MultiMatch(t.Lexeme, "!=") ||
		MultiMatch(t.Lexeme, "then"))) //if all are false
	{
		wasError = true;
	}
}

void Parse_Expression_T(Attribute E_T_type)
{
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case BRACKETS_OPEN:
		Parse_Expression(tokenList);
		match(t.Lexeme, "]");
		printf("\nExpression_Tag->[->Expression->]");
		break; //End of case BRACKETS_OPEN
	case ADD_OP:
	case MUL_OP:
		Parse_Expression(tokenList);
		printf("\nExpression_Tag->+|*->Expression");
		if (!(MultiMatch(t.Lexeme, "]") || 
			MultiMatch(t.Lexeme, ";") ||
			MultiMatch(t.Lexeme, "else") ||
			MultiMatch(t.Lexeme, "end_if") ||
			MultiMatch(t.Lexeme, "end") ||
			MultiMatch(t.Lexeme, "until") ||
			MultiMatch(t.Lexeme, "end_loop") ||
			MultiMatch(t.Lexeme, ">") ||
			MultiMatch(t.Lexeme, "<") ||
			MultiMatch(t.Lexeme, ">=") ||
			MultiMatch(t.Lexeme, "<=") ||
			MultiMatch(t.Lexeme, "==") ||
			MultiMatch(t.Lexeme, "!="))) //if all are false
		{
			wasError = true;
		}
		break; //End of case ADD_OP, MUL_OP
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Expression_T();
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
}

void Parse_Condition()
{
	t = NextToken(tokenList);
	switch (t.Kind)
	{
	case INT_NUM:
	case REAL_NUM:
	case ID:
		t = BackToken(tokenList);
		Parse_Expression(tokenList);
		if (MultiMatch(t.Lexeme, ">") ||
			MultiMatch(t.Lexeme, "<") ||
			MultiMatch(t.Lexeme, ">=") ||
			MultiMatch(t.Lexeme, "<=") ||
			MultiMatch(t.Lexeme, "==") ||
			MultiMatch(t.Lexeme, "!="))
		{
			Parse_Expression(tokenList);
			if (!(MultiMatch(t.Lexeme, "end_loop") ||
				MultiMatch(t.Lexeme, "then")))
			{
				printf("\n-----------------\nParser Error at %s, expected end_loop or then, line %d", t.Lexeme, t.LineNumber);
				wasError = true;
			}
			
			printf("\nCondition->id|number->Expression->end_loop|then");
		}
		else
		{
			wasError = true;
			printf("\n-----------------\nParser Error at %s, expected a relation operation, line %d", t.Lexeme, t.LineNumber);
		}			
		break; // End of case INT_NUM, REAL_NUM, ID
	default:
		if(t.Kind == COMMENT_START) //If there is a comment
		{
			while(t.Kind != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Condition(tokenList);
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

bool match(char* tokenString, char* expectedString)
{
	if (wasError == false)
	{
		if (strcmp(tokenString, expectedString) != 0)
		{
			printf("\n-----------------\nParser Error at %s, expected %s", tokenString, expectedString);
			wasError = true;
			return false;
		}
	}

	return true;
}

//Same as match but not changing wasError to true
bool MultiMatch(char* tokenString, char* expectedString) 
{
	if (strcmp(tokenString, expectedString) != 0)
	{
		return false;
	}

	return true;
}