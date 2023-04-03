#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int choice = 0;
	do {
		printf("当前数据量为10000，请选择排序方式：\n");
		printf("0.退出\n");
		printf("1.插入排序\n");
		printf("2.归并排序\n");
		printf("3.快速排序\n");
		printf("4.计数排序\n");
		printf("5.基数排序\n");
		
		scanf("%d", &choice);
		system("cls"); //清屏
		switch (choice)
		{
		case 1:
		{
			insert();
			break;
		}
		case 2:
		{
			merge();
			break;
		}
		case 3:
		{
			quick();
			break;
		}
		case 4:
		{
			count();
			break;
		}
		case 5:
		{
			radix();
			break;
		}
		default:
		{
			printf("请重新输入\n");
			break;
		}
		}
	} while (choice != 0);
	return 0;
}

