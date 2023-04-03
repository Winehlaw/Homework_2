#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#define NUM 10000

void savefile();
void loadfile(int arr[]);


void InsertSort(int k[], int n);
void swap(int k[], int low, int high);
int partition(int k[], int low, int high);
void QuickSort(int k[], int low, int high);
void merging(int arr[], int left, int mid, int right);
void MergeSort(int arr[], int left, int right);
void CountSort(int arr[], int len);
void RadixSort(int arr[], int len);


void insert();
void quick();
void merge();
void count();
void radix();
#endif //
