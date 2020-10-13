// ТУТ КОРОЧЕ ПОДСВЕТКА ПОБОЧНОЙ ДИАГОНАЛИ БУДЕТ!!!! ВООБЩЕ ДИСКОТЕКА А НЕ ПРОГРАММА!!!
#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

int** allocate_matrix(int height, int width);
void print_matrix(int** matrix, int height, int width);
void input_matrix(int** matrix, int height, int width);
void free_RAM(int** M, int height, int width);
void find_line_and_column_of_maximum(int** M, int height, int width, int* lm, int* cm); //Посик координат максимального элемента
int find_summary_under_antidiagonal(int** M, int height, int width); //Ищет сумму элементов под побочной диагональю
void change_matrix(int** M, int height, int width);

int main()
{
	printf("Set the height of the matrix:");
	int height, width;
	scanf_s("%d", &height);
	printf("Set the width of the matrix:");
	scanf_s("%d", &width);
	int** Mamix = allocate_matrix(height, width);
	input_matrix(Mamix, height, width);
	change_matrix(Mamix, height, width);
	print_matrix(Mamix, height, width);
	free_RAM(Mamix, height, width);
	return 0;
}

int** allocate_matrix(int height, int width)
{
	int** matrix = (int**)malloc(height * sizeof(int));
	for (int i = 0; i < height; ++i)
	{
		matrix[i] = (int*)malloc(width * sizeof(int));
	}
	if (NULL == matrix) printf("NO MATRIX!!!\n");
	return matrix;
}

void input_matrix(int** matrix, int height, int width)
{
	printf("Set the matrix size of %d * %d:\n", height, width);
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			scanf_s("%d", &matrix[i][j]);
		}
	}
}

void print_matrix(int** matrix, int height, int width)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("Changed matrix is:\n");
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (i + j == width - 1) SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10)); // А ВОТ ТА САМАЯ ТУСА-ДЖУСА
			printf("%d ", matrix[i][j]);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		}
		printf("\n");
	}
}

void free_RAM(int** M, int height, int width)
{
	for (int i = 0; i < height; ++i)
	{
		free(M[i]);
	}
	free(M);
}

void find_line_and_column_of_maximum(int** M, int height, int width, int* lm, int* cm)
{
	int maximum = M[0][0];
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (maximum < M[i][j])
			{
				maximum = M[i][j];
				*lm = i;
				*cm = j;
			}
		}
	}
}

int find_summary_under_antidiagonal(int** M, int height, int width)
{
	int summary = 0;
	for (int i = 1; i < height; ++i)
	{
		for (int j = max(width - i, 0); j < width; ++j)
		{
			summary += M[i][j];
		}
	}
	return summary;
}

void change_matrix(int** M, int height, int width)
{
	int line_of_maximum = 0;
	int column_maximum = 0;
	find_line_and_column_of_maximum(M, height, width, &line_of_maximum, &column_maximum);
	M[line_of_maximum][column_maximum] = find_summary_under_antidiagonal(M, height, width);
}
