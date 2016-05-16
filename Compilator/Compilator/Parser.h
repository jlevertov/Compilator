#include<stdio.h>
void Parse_Program(List* tokenList);
void Parse_Declerations(List* tokenList);
void Parse_Decleration(List* tokenList);
void Parse_Decleration_T(List* tokenList);
void Parse_Type(List* tokenList);
void Parse_Variables_List(List* tokenList);
void Parse_Variables_List_T(List* tokenList);
void Parse_Variable(List* tokenList);
void Parse_Variable_T(List* tokenList);
void Parse_Statements(List* tokenList);
void Parse_Statements_T(List* tokenList);
void Parse_Statement(List* tokenList);
void Parse_Receiver(List* tokenList);
void Parse_Receiver_T(List* tokenList);
void Parse_Expression(List* tokenList);
void Parse_Expression_T(List* tokenList);
void Parse_Condition(List* tokenList);