#include <stdio.h>
#include <malloc.h>

int** allocate_matrix(int height, int width);
void print_matrix(int** matrix, int height, int width);
void input_matrix(int** matrix, int height, int width);
void free_RAM(int** M, int height, int width);
void exchange_valules(int* x, int* y);
void sort(int** M, int height, int width);

int main()
{
	printf("Set the height of the matrix:");
	int height, width;
	scanf_s("%d", &height);
	printf("Set the width of the matrix:");
	scanf_s("%d", &width);
	int** Mamix = allocate_matrix(height, width);
	input_matrix(Mamix, height, width);
	sort(Mamix, height, width);
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
	printf("Changed matrix is:\n");
	for (int i = 0; i < height; ++i)
	{
		if (0 == i % 2)
		{
			for (int j = 0; j < width; ++j)
			{
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
		else
		{
			for (int j = width - 1; j > -1; j -= 1)
			{
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
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

void exchange_valules(int* x, int* y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

void sort(int** M, int height, int width)
{

	for (int i = 0; i < height * width - 1; i++)
	{
		for (int j = 0; j < height * width - 1 - i; ++j)
			if (M[j / width][j % width] > M[(j + 1) / width][(j + 1) % width])
				exchange_valules(&M[j / width][j % width], &M[(j + 1) / width][(j + 1) % width]);
	}
}

