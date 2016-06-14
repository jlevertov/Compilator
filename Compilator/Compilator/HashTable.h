#include<stdbool.h>
#include"header.h"

typedef struct TableNode
{
	enum KeyWords Type;
	int sizeOfArray;
	int key;
	char LexemeOfID[50];

}TableNode;

typedef struct Table
{
	TableNode** ParentTable;
	TableNode* hashTable[1000];
}Table;

int hashCode(int key);
TableNode* Search(Table* hashTable, int key);
void Insert(Table* hashTable, int key, enum KeyWords data, char lexeme[]);
TableNode* Delete(Table* hashTable, TableNode* item);
