#include"Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 归并排序两个有序数组
void merging(int arr[],int left,int mid,int right)
{
	int len1 = mid - left + 1;// 左数组长度
	int len2 = right - mid;// 右数组长度
	int* L = (int*)malloc(len1 * sizeof(int));  // 动态分配左数组空间
	int* R = (int*)malloc(len2 * sizeof(int));  // 动态分配右数组空间

	for (int i = 0; i < len1; i++)
	{
		L[i] = arr[left + i];  // 填充左数组
	}

	for (int j = 0; j < len2; j++)
	{
		R[j] = arr[mid + 1 + j]; // 填充右数组
	}

	int i = 0, j = 0, k = left;  // 初始化指针i,j,k
	while (i < len1 && j < len2) { // 当左右数组都不为空时
		if (L[i] <= R[j]) {  // 左数组当前元素小于等于右数组当前元素
			arr[k++] = L[i++];   // 将左数组当前元素复制到arr中，同时递增i,k
		}
		else {             // 左数组当前元素大于右数组当前元素
			arr[k++] = R[j++];   // 将右数组当前元素复制到arr中，同时递增j,k
		}
	}
	while (i < len1) {  // 如果左数组还有剩余元素，则全部复制到arr中
		arr[k++] = L[i++];
	}
	while (j < len2) {  // 如果右数组还有剩余元素，则全部复制到arr中
		arr[k++] = R[j++];
	}
	free(L);  // 释放内存
	free(R);
}

// 归并排序
void MergeSort(int arr[], int left,int right)
{
	if (left >= right) return;

	int mid = (left + right) / 2;// 计算中间位置

	MergeSort(arr,left,mid);// 对左半边进行排序
	MergeSort(arr,mid+1,right);// 对右半边进行排序

	merging(arr, left,mid,right); // 归并两个有序数组
	

}

void merge()
{
	int random_nums[NUM];
	savefile();
	loadfile(random_nums);
	clock_t start = clock();
	MergeSort(random_nums,0,NUM-1);
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