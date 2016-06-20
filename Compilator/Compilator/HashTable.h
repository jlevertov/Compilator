<<<<<<< HEAD
//#include<stdbool.h>


#include "header.h"
=======
#include<stdbool.h>
#include"header.h"
>>>>>>> origin/master

typedef struct TableNode
{
	enum KeyWords Type;
	int sizeOfArray;
	int key;
	char LexemeOfID[50];

}TableNode;

typedef struct Table
{
<<<<<<< HEAD
	struct Table* ParentTable;
=======
	TableNode** ParentTable;
>>>>>>> origin/master
	TableNode* hashTable[1000];
}Table;

int hashCode(int key);
TableNode* Search(Table* hashTable, int key);
<<<<<<< HEAD
bool Insert(Table* hashTable, int key, enum KeyWords data, char lexeme[]);
=======
void Insert(Table* hashTable, int key, enum KeyWords data, char lexeme[]);
>>>>>>> origin/master
TableNode* Delete(Table* hashTable, TableNode* item);
