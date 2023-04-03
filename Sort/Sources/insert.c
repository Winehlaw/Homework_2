#include"Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InsertSort(int arr[], int n)
{
	int i,j,temp;

	for (i = 1; i < n; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			temp = arr[i];

			for (j = i - 1; j>=0&&arr[j] > temp; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}
}

void insert()
{
	int random_nums[NUM];
	savefile();
	loadfile(random_nums);

	clock_t start = clock();

	InsertSort(random_nums, NUM);

	for (int i = 0; i < NUM; i++)
	{
		printf("%d ", random_nums[i]);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	printf("\n");

	clock_t diff = clock() - start;
	printf("¹²ÓÃÊ±%d ms\n", diff);
	return 0;
}