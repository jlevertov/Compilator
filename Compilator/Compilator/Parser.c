#include "Parser.h"
#include <string.h>

static Token t;
static bool wasError = false;

void Parse_Program(List* tokenList)
{
	
	t = tokenList->First->data[0];
	if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			t = NextToken(tokenList);
		}
		printf("\n%s\n", t.Lexeme);
	switch (t.Type)
	{
	case PROGRAM:
		Parse_Declerations(tokenList);
		printf("\nProgram->Declerations");
		match(t.Lexeme, ";");
		printf("\nProgram->Declerations->;");
		Parse_Statements(tokenList);
		printf("\nProgram->Declerations->;->Statemants");
		/*if(t.Type != EOF_)*/
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
			while (t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file\n");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token\n");
			}

		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Declerations(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case INT_NUM:
	case ID:
		t = BackToken(tokenList);
		Parse_Decleration(tokenList);
		printf("\nDeclerations->Decleration");
		match(t.Lexeme, ";");
		printf("\nDeclerations->Decleration->;");
		t = NextToken(tokenList);
		if (t.Type == IF || t.Type == LOOP || t.Type == START) //Finished Decleration starting Statemants
		{
			t = BackToken(tokenList);
		}
		else if (t.Type == INT_NUM)
		{
			t = BackToken(tokenList);
			t = BackToken(tokenList);
			Parse_Decleration_T(tokenList);
			printf("\nDeclerations->Decleration->;->Decleration_Tag");
		}
		else if (t.Type == ID)
		{
			t = NextToken(tokenList);
			
			if (t.Type == COMMA || t.Type == COLON)
			{
				t = BackToken(tokenList);
				t = BackToken(tokenList);
				t = BackToken(tokenList);
				Parse_Decleration_T(tokenList);
				printf("\nDeclerations->Decleration->;->Decleration_Tag");
			}
			else if (t.Type == BRACKETS_OPEN)
			{
				int i = 1;
				while (t.Type != INSERTION && t.Type != COLON)
				{
					t = NextToken(tokenList);
					i++;
				}

				if (t.Type == INSERTION)
				{
					while (i > 0)
					{
						t = BackToken(tokenList);
						i--;
					}
					
					t = BackToken(tokenList);
				}
				else if (t.Type == COLON)
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
			else if (t.Type == INSERTION)
			{
				t = BackToken(tokenList);
				t = BackToken(tokenList);
			} 

		}

		match(t.Lexeme, ";");
		printf("\nDeclerations->;");
		break; //End of cases INT_NUM, ID

	default:
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			Parse_Declerations(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected id or an int number, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != CMD_SEPERATOR && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Decleration(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case INT_NUM:
	case ID:
		t = BackToken(tokenList);
		Parse_Variables_List(tokenList);
		printf("\nDecleration->Variables_List");
		match(t.Lexeme, ":");
		printf("\nDecleration->Variables_List->:");
		Parse_Type(tokenList);
		t = NextToken(tokenList);
		printf("\nDecleration->Variables_List->:->Type");
		match(t.Lexeme, ";");
		printf("\nDecleration->Variables_List->:->Type->;");
		break; //End of cases INT_NUM, ID
	default:
	if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Decleration(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected an id or an int number, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != CMD_SEPERATOR && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Decleration_T(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case CMD_SEPERATOR:
		Parse_Declerations(tokenList);
		printf("\nDecleration_Tag->Decleration");
		break; //End of case CMD_SEPERATOR
	default:
	if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Decleration_T(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected ;, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != CMD_SEPERATOR && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; // End of default case
	} //End of switch (t.Type)
}

void Parse_Type(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case INT:
	case REAL:
		printf("\nType->Integer|Real");
		break; //End of cases INT, REAL
	default:
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Type(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected 'integer' or 'real', line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != CMD_SEPERATOR && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}
		
		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Variables_List(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case ID:
	case INT_NUM:
		t = BackToken(tokenList);
		Parse_Variable(tokenList);
		printf("\nVariables_List->Variable");
		t = NextToken(tokenList);
		 if (t.Type == COMMA)
		{
			t = BackToken(tokenList);
			Parse_Variables_List_T(tokenList);
			printf("Varialbles_List->Variable->,->Variables_List_Tag");
		}
		printf("\nVariables_List->Variable->,->Variables_List_Tag->:");
		printf("\n|Variables_List->Variable->:");
		printf("Now at %s", t.Lexeme);
		match(t.Lexeme, ":");
		break; //End of cases ID, INT_NUM
	default:
	if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Variables_List(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected id or an int number , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != COLON && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Variables_List_T(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case COMMA:
		Parse_Variable(tokenList);
		printf("\nVariables_List_Tag->Variable");
		t = NextToken(tokenList);
		if (t.Type == COMMA)
		{
			t = BackToken(tokenList);
			Parse_Variables_List_T(tokenList);
			printf("\nVariables_List_Tag->Variable->,->Variables_List_Tag");
		}
		else if(t.Type != COLON)
		{
			wasError = true;
		}
		break; //End of case COMMA
	default:
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Variables_List_T(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected ',', line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != COLON && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Variable(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case INT_NUM:
		printf("\nVariable->Number");
		break; //End of case INT_NUM
	case ID:
		t = NextToken(tokenList);
		printf("\nVariable->id");
		if (t.Type == COMMA || t.Type == COLON)
		{
			t = BackToken(tokenList);
		}
		else if (t.Type == BRACKETS_OPEN)
		{
			t = BackToken(tokenList);
			Parse_Variable_T(tokenList);
			printf("\nVariable->id->Variable_Tag");
		}
		else
		{
			wasError = true;
		}

		break; //End of case ID
	default:
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Variable(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected an int num or an id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != COMMA && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}
			
			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Variable_T(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case BRACKETS_OPEN:
		t = NextToken(tokenList);
		printf("Variable_Tag->[");
		if (t.Type == INT_NUM)
		{
			t = NextToken(tokenList);
			match(t.Lexeme, "]");
			printf("Variable_Tag->[Number]");
		}

		break; //End of case BRACKETS_OPEN
	default:
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Variable_T(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected [ , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != COMMA && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Statements(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case IF:
	case LOOP:
	case START:
	case ID:
		t = BackToken(tokenList);
		Parse_Statement(tokenList);
		printf("\nStatements->Statemant");
		//t = NextToken(tokenList);
		if (t.Type == CMD_SEPERATOR)
		{
			t = BackToken(tokenList);
			Parse_Statements_T(tokenList);
			printf("\nStatements->Statemant->;->Statemants_Tag");
		}

		match(t.Lexeme, "end");
		printf("\nStatements->Statemant->end");
		break; //End of cases IF, LOOP, START, ID

	default:
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Statements(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected if or loop or start or id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != END && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Statements_T(List* tokenList)
{
	t = NextToken(tokenList);
	//match(t.Lexeme, ";");
	t = NextToken(tokenList);
	switch (t.Type)
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
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Statements_T(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected if or loop or start or id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;	  
			while (t.Type != END && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Statement(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
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
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Statement(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected if or loop or start or id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != END_IF && t.Type != UNTIL && t.Type != END && t.Type != CMD_SEPERATOR  && t.Type != ELSE && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}
		
		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Receiver(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case ID:
		t = NextToken(tokenList);
		printf("\nReceiver->id");
		if (t.Type == BRACKETS_OPEN)
		{
			t = BackToken(tokenList);
			Parse_Receiver_T(tokenList);
			t = NextToken(tokenList);
			printf("\nReceiver->id->Receiver_Tag");
		}
		match(t.Lexeme, "=");
		printf("Receiver->id->Receiver_Tag->=");
		printf("\n|Receiver->id->=");
		break; //End of case ID
	default:
	if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Receiver(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected an id, line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != EQUALS && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}
			
			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Receiver_T(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case BRACKETS_OPEN:
		Parse_Expression(tokenList);
		match(t.Lexeme, "]");
		printf("\nReceiver_Tag->[->Expression->]");
		break; //End of case BRACKETS_OPEN
	default:
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Receiver_T(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected [ , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != INSERTION && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Expression(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
	{
	case INT_NUM:
	case REAL_NUM:
		t = NextToken(tokenList);
		printf("\nExpression->number");
		break; //End of case INT_NUM, REAL_NUM
	case ID:				
		t = NextToken(tokenList);
		if (t.Type == BRACKETS_OPEN ||
			t.Type == ADD_OP ||
			t.Type == MUL_OP)
		{
			t = BackToken(tokenList);
			Parse_Expression_T(tokenList);
			printf("\nExpression->id->[|+|*->Expression_Tag");
		}
		break; //End of case ID

		
	default:
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Expression(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected a number or an id , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != BRACKETS_CLOSE && t.Type != REAL_NUM && t.Type != CMD_SEPERATOR && t.Type != END_IF && t.Type != ELSE && t.Type != END && t.Type != UNTIL && t.Type != EOF_
				&& t.Type != BIGGER_THAN && t.Type != SMALLER_THAN && t.Type != BIGGER_THAN_EQUALS && t.Type != SMALLER_THAN_EQUALS && t.Type != EQUALS && t.Type != NOT_EQUALS && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End if default case
	} //End of switch (t.Type)

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

void Parse_Expression_T(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
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
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Expression_T(tokenList);
		}
		else
		{	
			printf("\n-----------------\nParser Error at %s, expected + or * or [ , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != BRACKETS_CLOSE && t.Type != CMD_SEPERATOR && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if (t.Type == ERROR)
			{
				printf("\nNo Token");
			}
		}
		break; //End of default case
	} //End of switch (t.Type)
}

void Parse_Condition(List* tokenList)
{
	t = NextToken(tokenList);
	switch (t.Type)
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
		if(t.Type == COMMENT_START) //If there is a comment
		{
			while(t.Type != COMMENT_END)
			{
				t = NextToken(tokenList);
			}
			
			Parse_Condition(tokenList);
		}
		else
		{
			printf("\n-----------------\nParser Error at %s, expected a number or an id , line %d", t.Lexeme, t.LineNumber);
			wasError = true;
			while (t.Type != THEN && t.Type != END_LOOP && t.Type != EOF_ && t.Type != ERROR)
			{
				t = NextToken(tokenList);
			}

			if (t.Type == EOF_)
			{
				printf("\nUnexpected end of file");
				exit(1);
			}
			else if(t.Type != ERROR)
			{
				printf("\nNo Token");
			}
		}

		break; //End of default case
	} //End of switch(t.Type)

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