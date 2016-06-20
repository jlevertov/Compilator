#define _CRT_SECURE_NO_WARNINGS

#include"Parser.h"

void main()
{
	int selectedItem;
	printf("Select input file:\n");
	printf("Correct input 1 -> 1.\n");
	printf("Correct input 2 -> 2.\n");
	printf("Incorrect input 1 -> 3.\n");
	printf("Incorrect input 2 -> 4.\n");
	scanf("%d", &selectedItem);
	switch (selectedItem)
	{
	case 1:
		system("cd C:\\Users\\elad-pc\\Desktop\\App3\\lex.yy.exe CorrectInput1.txt > t111.txt");
	default:
		break;
	}
}