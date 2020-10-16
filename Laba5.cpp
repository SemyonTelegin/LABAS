#include <stdio.h>
#include <iso646.h>
#include <malloc.h>

void sort_negative(int* A, int lenght, int count_positive, int count_negative);
int find_index_of_positive_min(int A[], int start, int finish);
int find_index_of_negative_max(int A[], int start, int finish);
void input_array(int* A, int lenght);
void print_array(int* A, int lenght);
void switch_values(int* x, int* y);
void count_negative_and_positive(int* A, int lenght, int* count_neganive, int* count_positive);
void sort_positive(int* A, int lenght, int count_positive);
void algorithm_of_Semyon(int* A, int lenght);

int main()
{
	printf("Set the size of the array:");
	int size;
	scanf_s("%d", &size);
	int* Array = (int*)malloc(size * sizeof(int));
	printf("\nSet %d numbers:", size);
	input_array(Array, size);
	algorithm_of_Semyon(Array, size);
	print_array(Array, size);
	free(Array);
	return 0;
}

void input_array(int* A, int lenght)
{
	for (int i = 0; i < lenght; ++i)
	{
		scanf_s("%d", &A[i]);
	}
}

void print_array(int* A, int lenght)
{
	for (int i = 0; i < lenght; ++i)
	{
		printf("%d  ", A[i]);
	}
	printf("\n");
}

void switch_values(int* x, int* y)
{
	int temporary = *y;
	*y = *x;
	*x = temporary;
}

void count_negative_and_positive(int* A, int lenght, int* count_positive, int* count_negative)
{
	for (int i = 0; i < lenght; ++i)
	{
		if (A[i] > 0) (*count_positive)++;
		if (A[i] < 0) (*count_negative)++;
	}
}

void algorithm_of_Semyon(int* A, int lenght)
{
	int pos = 0;
	int neg = 0;
	count_negative_and_positive(A, lenght, &pos, &neg);
	sort_positive(A, lenght, pos);
	sort_negative(A, lenght, pos, neg);
}

void sort_positive(int* A, int lenght, int count_positive)
{
	for (int i = 0; i < count_positive; ++i)
	{
		int j = find_index_of_positive_min(A, i, lenght);
		switch_values(&A[j], &A[i]);
	}
}

int find_index_of_positive_min(int A[], int start, int finish)
{
	int min = 1000;
	int index = 0;
	for (int i = start; i < finish; ++i)
	{
		if (min > A[i] and A[i] > 0)
		{
			min = A[i];
			index = i;
		}
	}
	return index;;
}

int find_index_of_negative_max(int A[], int start, int finish)
{
	int max = -1000;
	int index = 0;
	for (int i = start; i < finish; ++i)
	{
		if (max < A[i] and A[i] < 0)
		{
			max = A[i];
			index = i;
		}
	}
	return index;;
}

void sort_negative(int* A, int lenght, int count_positive, int count_negative)
{
	for (int i = count_positive; i < count_negative + count_positive; ++i)
	{
		int j = find_index_of_negative_max(A, i, lenght);
		switch_values(&A[j], &A[i]);
	}
}