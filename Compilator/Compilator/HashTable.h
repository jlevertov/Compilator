#include<stdbool.h>
#include"header.h"

typedef struct TableNode
{
	enum KeyWords Type;
	int key;

}TableNode;

typedef struct Table
{
	TableNode** ParentTable;
	TableNode* hashTable[1000];
}Table;

int hashCode(int key);
TableNode* Search(Table* hashTable, int key);
void Insert(Table* hashTable, int key, enum KeyWords data);
TableNode* Delete(Table* hashTable, TableNode* item);
