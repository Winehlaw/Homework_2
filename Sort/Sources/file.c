#include"Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void savefile()
{
	int i;
	FILE* fp = fopen("random_numbers.txt", "w");

	//设置rand函数种子为当前时间
	srand((unsigned)time(NULL));

	//使用循环生成NUM个随机数
	for (i = 0; i < NUM; i++)
	{
		fprintf(fp, "%d ", rand());
	}

	//关闭文件

	fclose(fp);

}

void loadfile(int arr[])
{
	int i;

	FILE* fp = fopen("random_numbers.txt", "r");
	if (fp == NULL)
	{
		printf("Failed to open file !\n");
		return;
	}

	//循环读取文件中的数据数，并存入数组
	for (i = 0; i < NUM; i++)
	{
		fscanf(fp, "%d", &arr[i]);
		
	}
	fclose(fp);
}