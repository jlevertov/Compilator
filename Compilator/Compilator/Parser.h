#include "HashTable.h"


typedef struct Attribute
{
	  enum KeyWords type;
}Attribute;

void Parse_Program(List* tokenList);
void Parse_Declerations();
void Parse_Decleration();
void Parse_Decleration_T();
Attribute Parse_Type();
void Parse_Variables_List();
void Parse_Variables_List_T();
void Parse_Variable();
void Parse_Variable_T();
void Parse_Statements();
void Parse_Statements_T();
void Parse_Statement();
Attribute Parse_Receiver();
void Parse_Receiver_T(Attribute R_T_type);
Attribute Parse_Expression();
Attribute Parse_Expression_T(Attribute E_T_type);
void Parse_Condition();
