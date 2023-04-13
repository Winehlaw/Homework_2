#include"head.h"

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], size_t n, int i)	//n:数组长度	i:待维护节点的下标
{
    int largest = i;
    int LChild = 2 * i + 1;
    int RChild = 2 * i + 2;

    if (LChild < n && a[largest] < a[LChild])
        largest = LChild;
    if (RChild < n && a[largest] < a[RChild])
        largest = RChild;
    if (largest != i)
    {
        swap(&a[largest], &a[i]);
        heapify(a, n, largest);
    }

}

void heap_sort(int a[], size_t n)
{
    int i;

    for (i = n / 2 - 1; i >= 0; i--)	//建堆
    {
        heapify(a, n, i);
    }

    for (i = n - 1; i > 0; i--)	//排序
    {
        swap(&a[i], &a[0]);
        heapify(a, i, 0);
    }
}


