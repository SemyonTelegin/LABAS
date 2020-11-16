#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_LENGHT_OF_WORDS 25
#define MAX_LENGHT_OF_TEXT 10000
#define LENGHT_OF_LINE 100
#define MAX_NUMBER_OF_STRINGS 500

int countNumberWordsInString(char* string);
char** parseString(char* string);
void copyNSymbolsToStringFromString(char* stringDestination, char* stringSource, int n);
void freeMemoryOfMassiveOfStrings(char** massiveOfStrings, int numberOfElements);
void makeWordLonger(char* word);
void alignLine(int start, int finish, int* currentLenght, int** words);
int* distributeWordsIntoStrings(char** words, int numberOfWords);
int checkForExistaceOfNumberInArray(int number, int* array);

int main()
{
	char* text = (char*)malloc(MAX_LENGHT_OF_TEXT * sizeof(char));
	fgets(text, MAX_LENGHT_OF_TEXT, stdin);
	int numberOfWords = countNumberWordsInString(text);
	char** words = parseString(text);
	int* lines = distributeWordsIntoStrings(words, numberOfWords);
	for (int i = 0; i < LENGHT_OF_LINE; i++)
	{
		printf("_");
	}
	printf("\n");
	//puts(words[28]);
	for (int i = 0; i < numberOfWords; i++)
	{
		printf("%s", words[i]);
		if (checkForExistaceOfNumberInArray(i, lines) && i)
		{
			printf("\n");
		}
	}
	free(text);
	free(lines);
	freeMemoryOfMassiveOfStrings(words, numberOfWords);
	return 0;
}

int countNumberWordsInString(char* string)
{
	int count = 0;
	char* pointer = string;
	for (char* pointerOnSpace; pointerOnSpace = strpbrk(pointer, " "); pointer++)
	{
		if (pointer != pointerOnSpace)
		{
			count++;
			pointer = pointerOnSpace;
		}
	}
	if (strlen(pointer))
	{
		count++;
	}
	return count;
}

char** parseString(char* string)
{
	int numberOfWords = countNumberWordsInString(string);
	char* pointer = string;
	char** words = (char**)malloc(numberOfWords * sizeof(char*));
	int i = 0;
	for (char* pointerOnSpace; pointerOnSpace = strpbrk(pointer, " "); pointer++)
	{
		if (pointer != pointerOnSpace)
		{
			int lenght = pointerOnSpace - pointer;
			words[i] = (char*)malloc(MAX_LENGHT_OF_WORDS * sizeof(char));
			copyNSymbolsToStringFromString(words[i], pointer, lenght + 1);
			pointer = pointerOnSpace;
			i++;
		}
	}
	if (strlen(pointer))
	{
		words[i] = (char*)malloc(MAX_LENGHT_OF_WORDS * sizeof(char));
		copyNSymbolsToStringFromString(words[i], pointer, strlen(pointer));
		i++;
	}
	return words;
}

void copyNSymbolsToStringFromString(char* stringDestination, char* stringSource, int n)
{
	for (int i = 0; i < n; i++)
	{
		stringDestination[i] = stringSource[i];
	}
	stringDestination[n] = '\0';
}

void freeMemoryOfMassiveOfStrings(char** massiveOfStrings, int numberOfElements)
{
	for (int i = 0; i < numberOfElements - 1; i++)
	{
		free(massiveOfStrings[i]);
	}
	free(massiveOfStrings);
}

void makeWordLonger(char* word)
{
	int lenght = strlen(word);
	word[lenght] = '_';
	word[lenght + 1] = '\0';
}

void alignLine(int start, int finish, int* currentLenght, char** words)
{
	int count = 0;
	while (*currentLenght < LENGHT_OF_LINE)
	{
		makeWordLonger(words[start + 1 + count]);
		(*currentLenght)++;
		count++;
	}
	*currentLenght = 0;
}

int* distributeWordsIntoStrings(char** words, int numberOfWords)
{
	int currentLenghtOfLine = 0;
	int currenNumberOfLine = 0;
	int* endingsOfStrings = (int*)malloc(MAX_NUMBER_OF_STRINGS * sizeof(int));
	for (int i = 0; i < MAX_NUMBER_OF_STRINGS; i++)
	{
		endingsOfStrings[i] = -1;
	}
	endingsOfStrings[0] = 0;
	for (int j = 0; j < numberOfWords; j++)
	{	
		int lenghtOfCurrentWord = strlen(words[j]);
		if (currentLenghtOfLine + lenghtOfCurrentWord < LENGHT_OF_LINE)
		{
			currentLenghtOfLine += lenghtOfCurrentWord;
		}
		else
		{
			endingsOfStrings[currenNumberOfLine + 1] = j - 1;
			alignLine(endingsOfStrings[currenNumberOfLine], endingsOfStrings[currenNumberOfLine + 1], &currentLenghtOfLine, words);
			currenNumberOfLine++;
			j--;
		}
	}
	return endingsOfStrings;
}

int checkForExistaceOfNumberInArray(int number, int* array)
{
	for (int i = 0; i < MAX_NUMBER_OF_STRINGS; i++)
	{
		if (number == array[i])
		{
			return 1;
		}
	}
	return 0;
}