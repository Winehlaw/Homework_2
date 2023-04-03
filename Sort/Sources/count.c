#include"Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CountSort(int arr[], int len)
{
	if (len < 1)return;

	//寻找最大的元素
	int max = arr[0];
	for (int i = 1; i < len; i++)
		if (arr[i] > max)
			max = arr[i];

	//分配一个长度为max+1的数组存储计数，并初始化为0
	int* count = (int*)malloc(sizeof(int) * (max + 1));
	memset(count, 0, sizeof(int) * (max + 1));// 初始化为 0

	//计数
	for (int i = 0; i < len; i++)
		count[arr[i]]++;// 统计 arr[i] 元素出现的次数

	//统计计数的累计值
	for (int i = 1; i < max + 1; i++)
		count[i] += count[i - 1];// 将 count 数组处理成累计次数的形式

	//创建一个临时数组保存结果
	int* output = (int*)malloc(sizeof(int) * len);

	//将元素放到正确的位置上
	for (int i = len - 1; i >= 0; i--)
	{
		output[--count[arr[i]]] = arr[i]; // 在 count 数组中查找 arr[i] 对应的下标，并将其放在 output 数组中
	}

	//将结果复制回原数组
	for (int i = 0; i < len; i++)
		arr[i]=output[i];
	free(count); // 释放动态分配的内存
	free(output);
}

void count()
{
	int random_nums[NUM];
	savefile();
	loadfile(random_nums);

	clock_t start = clock();

	CountSort(random_nums, NUM);

	for (int i = 0; i < NUM; i++)
	{
		printf("%d ", random_nums[i]);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	printf("\n");

	clock_t diff = clock() - start;
	printf("共用时%d ms\n", diff);
	return 0;

}
