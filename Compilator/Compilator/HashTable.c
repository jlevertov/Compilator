<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS
=======
>>>>>>> origin/master
#include "HashTable.h"
#define SIZE 1000;


/*struct TableNode* hashArray[SIZE];
struct TableNode* dummyItem;
struct TableNode* item;*/

<<<<<<< HEAD
int hashCode(int key) {
	return key % SIZE;
}

TableNode* Search(Table* hashTable, int key) {
=======
int HashCode(int key) {
	return key % SIZE;
}

TableNode *Search(Table* hashTable, int key) {
>>>>>>> origin/master
	//get the hash 
	int hashIndex = hashCode(key);

	//move in array until an empty 
	while (hashTable->hashTable[hashIndex] != NULL) {

		if (hashTable->hashTable[hashIndex]->key == key)
			return hashTable->hashTable[hashIndex];

		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= SIZE;
	}

<<<<<<< HEAD
	if (hashTable->hashTable[hashIndex] == NULL && hashTable->ParentTable != NULL)
	{
		return Search(hashTable->ParentTable, key);
	}

	return NULL;
}

bool Insert(Table* hashTable, int key, enum KeyWords data, char lexeme[]) {
=======
	return NULL;
}

void Insert(Table* hashTable, int key, enum KeyWords data, char lexeme[]) {
>>>>>>> origin/master

	struct TableNode *item = (struct TableNode*) malloc(sizeof(struct TableNode));
	item->Type = data;
	item->key = key;
	strcpy(item->LexemeOfID, lexeme);

	//get the hash 
	int hashIndex = hashCode(key);
	if (strcmp(hashTable->hashTable[hashIndex]->LexemeOfID, item->LexemeOfID) == 0)
	{
<<<<<<< HEAD
		return false;
=======
		printf("Veriable %s already exists", lexeme);
		return;
>>>>>>> origin/master
	}
	//move in array until an empty or deleted cell
	while (hashTable->hashTable[hashIndex] != NULL && hashTable->hashTable[hashIndex]->key != -1) {
		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= SIZE;
	}

	hashTable->hashTable[hashIndex] = item;
<<<<<<< HEAD
	return true;
=======
>>>>>>> origin/master
}

TableNode* Delete(Table* hashTable, TableNode* item) {
	int key = item->key;
	TableNode* dummyItem = (TableNode*)malloc(sizeof(TableNode));
	dummyItem->key = -1;
	dummyItem->Type = ERROR;
	//get the hash 
	int hashIndex = hashCode(key);

	//move in array until an empty 
	while (hashTable->hashTable[hashIndex] != NULL) {

		if (hashTable->hashTable[hashIndex]->key == key) {
			TableNode* temp = hashTable->hashTable[hashIndex];

			//assign a dummy item at deleted position
			hashTable->hashTable[hashIndex] = dummyItem;
			return temp;
		}

		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= SIZE;
	}

	return NULL;
}
