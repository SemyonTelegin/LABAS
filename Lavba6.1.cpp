//Эта штука переворачиват матрицу относительно побочной диагонали (на самом деле псевдо-побочной как выяснилось)
#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

int** allocate_matrix(int height, int width); //выделение RAM
void print_matrix(int** matrix, int height, int width);
void input_matrix(int** matrix, int height, int width);
void exchange_valules(int* x, int* y); //обмен переменных значением БЕЗ ИСПОЛЬЗОВАНИЯ ТРЕТЬЕЙ!!!!! 
void antidiagonal_transposion(int** matrix, int height, int width); //Собсна сама транспозиция
void free_RAM(int** M, int height, int width); //Освобождение RAM

int main()
{
	printf("Set the height of the matrix:");
	int height, width;
	scanf_s("%d", &height);
	printf("Set the width of the matrix:");
	scanf_s("%d", &width);
	int** Mamix = allocate_matrix(height, width);
	input_matrix(Mamix, height, width);
	antidiagonal_transposion(Mamix, height, width);
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
	printf("Chanched matrix is:\n");
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (i + j == width - 1) SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			printf("%d ", matrix[i][j]);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		}
		printf("\n");
	}
}

void exchange_valules(int* x, int* y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

void antidiagonal_transposion(int** matrix, int height, int width)
{
	if (height >= width)
	{
		for (int i = 0; i < width - 1; ++i)
		{
			for (int j = 0; j < width - i - 1; ++j)
			{
				exchange_valules(&matrix[i][j], &matrix[width - j - 1][width - i - 1]);
			}
		}
	}
	else
	{
		int delta = width - height;
		for (int i = 0; i < height - 1; ++i)
		{
			for (int j = delta; j < width - 1 - i; ++j)
			{
				exchange_valules(&matrix[i][j], &matrix[height - j - 1 + delta][height - i - 1 + delta]);
			}
		}
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
