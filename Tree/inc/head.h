#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<stdbool.h>
#include<string.h>

#define NUM 10 // ջ�Ĵ�С
#define MAX_SIZE 128
#define STR_SIZE 1024
//define HEIGHT(p) ( (p==NULL) ? 0 : ((LPTree p)->height) )
#define MAX(a,b) a>b?a:b

typedef int ElemType;

typedef struct treeNode  // ����������ڵ�Ľṹ��
{
	ElemType data;               // ����
	struct treeNode* LChild; // ������
	struct treeNode* RChild; // ������
}Tree, * LPTree;

typedef struct AVLTreeNode
{
	ElemType key;	//�ؼ��֣����ڶ�AVL���ڵ��������
	int height;
	struct AVLTreeNode* LChild;
	struct AVLTreeNode* RChild;
}TREE, * AVLTree;

typedef struct Queue
{
	int front;
	int rear;
	LPTree data[MAX_SIZE];
}Queue, * LPQueue;

typedef enum Status
{
	error,
	success
}Status;

LPTree createNode(ElemType data);
void insertNode(LPTree parentNode, LPTree LChild, LPTree RChild);
void InsertNode(LPTree curData, LPTree* root);
void* parentNode(LPTree curData, LPTree root);
LPTree maxNode(LPTree root);
LPTree minNode(LPTree root);
void deleteNode(LPTree delData, LPTree* root);
LPTree searchNode(LPTree root, ElemType data);
void printfData(LPTree curData);
void preOrder(LPTree root);
void preOrderByStack(LPTree root);
void midOrder(LPTree root);
void midOrderByStack(LPTree root);
void lastOrder(LPTree root);
void lastOrderByStack(LPTree root);
void initQueue(LPQueue* q);
bool emptyQueue(LPQueue q, LPTree curData);
bool enQueue(LPQueue q, LPTree curData);
bool deQueue(LPQueue q, LPTree* curData);
void levelOrder(LPTree root);

void swap(int* a, int* b);
void heapify(int a[], size_t n, int i);
void heap_sort(int a[], size_t n);

static AVLTree CreateNode(ElemType key, AVLTree LChild, AVLTree RChild);
int getHeight(AVLTree curData);
void preOrderAVLtree(AVLTree root);
void midOrderAVLtree(AVLTree root);
AVLTree SearchAVLnode(AVLTree Node, ElemType key);
void lastOrderAVLtree(AVLTree root);
static AVLTree LLrotation(AVLTree root);
static AVLTree RRrotation(AVLTree root);
static AVLTree LRrotation(AVLTree root);
static AVLTree RLrotation(AVLTree root);
AVLTree AVL_min(AVLTree root);
AVLTree AVL_max(AVLTree root);
AVLTree insertTree(AVLTree root, ElemType key);
static AVLTree DelNode(AVLTree root, AVLTree pNode);
AVLTree AVL_del(AVLTree root, ElemType key);
void desAVLtree(AVLTree root);
void printfAVLtree(AVLTree Node, ElemType key, int direction);