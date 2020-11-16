#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_LENGHT_OF_WORDS 20
#define MAX_LENGHT_OF_TEXT 10000

typedef struct FrequencyDictionary
{
	char** words;
	int* frequencyOfwords;
} FrequencyDictionary;

int countNumberWordsInString(char* string);
char** parseString(char* string);
void printMassiveOfStrings(char** massiveOfStrings, int numberOfElements);
void freeMemoryOfMassiveOfStrings(char** massiveOfStrings, int numberOfElements);
void copyNSymbolsToStringFromString(char* stringDestination, char* stringSource, int n);
int checkForExistanceOfAtringInMassiveOfStrings(char** massiveOfStrings, char* string, int numberOfElements);
FrequencyDictionary makeFrequencyDictionaryOfText(char* text);
void printFrequencyFictionary(FrequencyDictionary FreDick, int numberOfWords);
void freeMemoryOfFrequencyDictionary(FrequencyDictionary FreDick, int numberOfWords);
void sortFrequencyDictionaryByFrequencyOfWords(FrequencyDictionary FreDick, int numberOfWords);

int main()
{
	char* text = (char*)malloc(MAX_LENGHT_OF_TEXT * sizeof(char));
	fgets(text, MAX_LENGHT_OF_TEXT, stdin);
	text[strlen(text) - 1] = '\0';
	int numberOfWords = countNumberWordsInString(text);
	FrequencyDictionary FreqDick = makeFrequencyDictionaryOfText(text);
	sortFrequencyDictionaryByFrequencyOfWords(FreqDick, numberOfWords);
	printFrequencyFictionary(FreqDick, numberOfWords);
	freeMemoryOfFrequencyDictionary(FreqDick, numberOfWords);
	free(text);
	return 0;
}

int countNumberWordsInString(char* string)
{
	int count = 0;
	char* pointer = string;
	for (char* pointerOnSpace; pointerOnSpace = strpbrk(pointer, " ,.''-_!?><;:()|}]{{+=*&^%$#@!"); pointer++)
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
	for (char* pointerOnSpace; pointerOnSpace = strpbrk(pointer, " ,.''-_!?><;:()|}]{[+=*&^%$#@!");pointer++)
	{
		if (pointer != pointerOnSpace)
		{
			int lenght = pointerOnSpace - pointer;
			words[i] = (char*)malloc((lenght+1) * sizeof(char));
			copyNSymbolsToStringFromString(words[i], pointer, lenght);
			pointer = pointerOnSpace;
			i++;
		}
	}
	if (strlen(pointer))
	{
		words[i] = (char*)malloc(strlen((pointer)+1) * sizeof(char));
		copyNSymbolsToStringFromString(words[i], pointer, strlen(pointer));
		i++;
	}
	return words;
}

void printMassiveOfStrings(char** massiveOfStrings, int numberOfElements)
{
	for (int i = 0; i < numberOfElements; i++)
	{
		puts(massiveOfStrings[i]);
	}
}

void freeMemoryOfMassiveOfStrings(char** massiveOfStrings, int numberOfElements)
{
	for (int i = 0; i < numberOfElements - 1; i++)
	{
		free(massiveOfStrings[i]);
	}
	free(massiveOfStrings);
}

void copyNSymbolsToStringFromString(char* stringDestination, char* stringSource, int n)
{
	for (int i = 0; i < n; i++)
	{
		stringDestination[i] = stringSource[i];
	}
	stringDestination[n] = '\0';
}

int checkForExistanceOfAtringInMassiveOfStrings(char** massiveOfStrings, char* string, int numberOfElements)
{
	for (int i = 0; i < numberOfElements; i++)
	{
		if (massiveOfStrings[i] && string)
		{
			if (!strcmp(massiveOfStrings[i], string))
			{
				return i;
			}
		}
	}
	return -1;
}

FrequencyDictionary makeFrequencyDictionaryOfText(char* text)
{
	int numberOfWords = countNumberWordsInString(text);
	char** words = parseString(text);
	int* frequency = (int*)malloc(numberOfWords * sizeof(int));
	for (int i = 0; i < numberOfWords; i++)
	{
		frequency[i] = 1;
	}
	for (int i = 0; i < numberOfWords; i++)
	{
		int index = checkForExistanceOfAtringInMassiveOfStrings(words, words[i], i - 1);
		if (words[i] && (index + 1))
		{
			words[i] = { };
			frequency[index]++;
		}
	}
	FrequencyDictionary FreqDick = {words, frequency};
	return FreqDick;
}

void printFrequencyFictionary(FrequencyDictionary FreDick, int numberOfWords)
{
	for (int i = 0; i < numberOfWords; i++)
	{
		if (FreDick.words[i])
		{
			printf("%10.10s:  %d\n", FreDick.words[i], FreDick.frequencyOfwords[i]);
		}
	}
}

void freeMemoryOfFrequencyDictionary(FrequencyDictionary FreDick, int numberOfWords)
{
	freeMemoryOfMassiveOfStrings(FreDick.words, numberOfWords);
	free(FreDick.frequencyOfwords);
}

void sortFrequencyDictionaryByFrequencyOfWords(FrequencyDictionary FreDick, int numberOfWords)
{
	for (int i = 0; i < numberOfWords - 1; i++)
	{
		for (int j = 0; j < numberOfWords - 1 - i; j++)
		{
			if (FreDick.frequencyOfwords[j] < FreDick.frequencyOfwords[j + 1])
			{
				int temporary = FreDick.frequencyOfwords[j];
				FreDick.frequencyOfwords[j] = FreDick.frequencyOfwords[j + 1];
				FreDick.frequencyOfwords[j + 1] = temporary;
				char* temp = FreDick.words[i];
				FreDick.words[i] = FreDick.words[i + 1];
				FreDick.words[i + 1] = temp;
			}
		}
	}
}