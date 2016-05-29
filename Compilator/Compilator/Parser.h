#include<stdio.h>
#include"header.h"
typedef struct Attribute
{
	enum KeyWords type;
}Attribute;
void Parse_Program(List* tokenList);
void Parse_Declerations();
void Parse_Decleration();
void Parse_Decleration_T();
Attribute Parse_Type();
void Parse_Variables_List(Attribute VS_type);
void Parse_Variables_List_T(Attribute VS_T_type);
void Parse_Variable(Attribute V_type);
void Parse_Variable_T(Attribute V_T_type);
void Parse_Statements();
void Parse_Statements_T();
void Parse_Statement();
Attribute Parse_Receiver();
void Parse_Receiver_T(Attribute R_T_type);
Attribute Parse_Expression();
void Parse_Expression_T(Attribute E_T_type);
void Parse_Condition();