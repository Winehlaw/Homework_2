#include"head.h"

LPTree createNode(ElemType data)  // 创建节点函数，返回一个指向新节点的指针
{
	LPTree newNode = (LPTree)malloc(sizeof(Tree));  // 为节点分配内存空间
	newNode->data = data;                           // 赋值数据
	newNode->LChild = NULL;                         // 初始化左右子树
	newNode->RChild = NULL;
	return newNode;
}

void insertNode(LPTree parentNode, LPTree LChild, LPTree RChild)	//无序
{
	parentNode->LChild = LChild;  // 插入节点
	parentNode->RChild = RChild;
}

void InsertNode(LPTree curData, LPTree* root)	//插入节点
{//因为根节点可能被修改，所以传二级指针
//将插入节点的data和根节点的data作比较，小的插入根节点的左子树，反之则插入右子树

	if (*root == NULL || curData == NULL)
	{
		*root = curData;
		return;
	}

	if ((curData->data) > ((*root)->data))
	{
		if ((*root)->RChild == NULL)
		{
			(*root)->RChild = curData;
			return;
		}
		if ((*root)->RChild)
			InsertNode(curData, &(*root)->RChild);
	}

	if (curData->data <= (*root)->data)
	{
		if ((*root)->LChild == NULL)
		{
			(*root)->LChild = curData;
			return;
		}
		if ((*root)->LChild)
			InsertNode(curData, &(*root)->LChild);
	}
}

void* parentNode(LPTree curData, LPTree root)	//找到指定节点的父节点
{
	if (curData == NULL || root == NULL || root == curData)	//判断是否为空指针，以及root有无父节点
	{
		return NULL;
	}

	LPTree pMove = root;
	LPTree parentNode = pMove;

	while (pMove != NULL && pMove->data != curData->data)
	{
		parentNode = pMove;
		if (curData->data > pMove->data)
			pMove = pMove->RChild;
		else
			pMove = pMove->LChild;
	}

	if(pMove == NULL)
	{
		printf("Node does not exist.\n");
		return NULL;
	}

	return parentNode;
}

LPTree maxNode(LPTree root)
{
	if (root == NULL)
		return NULL;
	LPTree pMove = root;
	while (pMove->RChild)
		pMove = pMove->RChild;
	return pMove;
}

LPTree minNode(LPTree root)
{
	if (root == NULL)
		return NULL;
	LPTree pMove = root;
	while (pMove->LChild)
		pMove = pMove->LChild;
	return pMove;
}

void deleteNode(LPTree delData, LPTree* root)
{
	LPTree pNode = parentNode(delData, *root);	//删除节点的父节点

	if (delData == NULL || root == NULL)
		return;
	
	if (delData != *root && pNode == NULL)	//删除节点不是root，说明没有找到要删除的节点
		return;

	if (delData->LChild == NULL && delData->RChild == NULL)	//删除节点为叶子节点
	{
		if(*root == delData)	//要删除的节点是root节点
		{
			*root = NULL;
			return;
		}

		if (pNode->LChild == delData)
			pNode->LChild = NULL;
		if (pNode->RChild == delData)
			pNode->RChild = NULL;
	}

	else if (delData->LChild == NULL || delData->RChild == NULL)	//要删除的节点只有左子树或右子树
	{
		if (*root == delData)	//要删除的节点是根节点
		{
			if ((*root)->LChild != NULL)	//删除节点只有左子树
				(*root) = (*root)->LChild;
			else if ((*root)->RChild != NULL)	//删除节点只有右子树
				(*root) = (*root)->RChild;
		}
		else if (delData->LChild != NULL)	//删除节点只有左子树
		{
			if (pNode->LChild == delData)	//删除节点是父节点的左子节点
				pNode->LChild = delData->LChild;
			if (pNode->RChild == delData)
				pNode->RChild = delData->LChild;
		}
		else if (delData->RChild != NULL)
		{
			if (pNode->LChild == delData)
				pNode->LChild = delData->RChild;
			if (pNode->RChild == delData)
				pNode->RChild = delData->RChild;
		}
	}
	else if (delData->LChild != NULL && delData->RChild != NULL)	//删除节点有左子树和右子树
	{
		LPTree repNode = maxNode(delData->LChild);	
		//找到删除节点的左子树的最右节点作为替代节点，替代节点与删除节点相邻
		LPTree pNode = parentNode(repNode, *root);	//找到替代节点的父节点

		if (*root == delData)
		{
			pNode->RChild = repNode->LChild;	
			repNode->LChild = (*root)->LChild;	//将替代节点的左子树作为删除节点的左子树
			repNode->RChild = (*root)->RChild;	//将替代节点的右子树作为删除节点的右子树
			(*root) = repNode;					//将替代节点代替原来的删除节点成为新的根节点或者更新替代节点的父节点的子节点为替代节点
		}
		else if (pNode->LChild == delData)	//删除节点是其父节点的左子节点
		{
			pNode->LChild = repNode;
			repNode->LChild = delData->LChild;
			if (pNode != delData)
			{
				repNode->RChild = delData->RChild;
				pNode->RChild = repNode->LChild;
			}
			else if (pNode == delData)
				repNode->RChild = delData->RChild->LChild;
		}
		else if (pNode->RChild == delData)
		{
			pNode->RChild = repNode;
			repNode->RChild = delData->RChild;
			if (pNode != delData)
			{
				repNode->LChild = repNode->LChild;
				pNode->RChild = repNode->LChild;
			}
			else if (pNode == delData)
			{
				repNode->LChild = repNode->LChild->LChild;
			}
		}
	}
	free(delData);
}

LPTree searchNode(LPTree root, ElemType data)	//搜索指定数据的节点
{
	if (root == NULL)
		return NULL;
	if (root->data > data)
		return searchNode(root->LChild, data);
	if (root->data < data)
		return searchNode(root->RChild, data);
	else
		return root;
}

void printfData(LPTree curData)  // 打印节点数据
{
	printf("%c\t", curData->data);
}

void preOrder(LPTree root)  // 先序遍历
{
	if (root != NULL)            // 当前节点不为空
	{
		printfData(root);          // 访问当前节点
		preOrder(root->LChild);    // 遍历左子树
		preOrder(root->RChild);    // 遍历右子树
	}
}

void preOrderByStack(LPTree root)  // 先序遍历（非递归）
{
	if (root == NULL)  // 根节点为空，直接返回
	{
		return;
	}
	LPTree stack[NUM]; // 建立一个栈来存储节点
	int stackTop = -1; // 初始化栈顶为-1
	LPTree pMove = root; // 当前节点赋值为根节点
	while (stackTop != -1 || pMove) // 当栈不为空或当前节点不为空时
	{
		while (pMove) // 当前节点不为空
		{
			printf("%c\t", pMove->data);  // 访问当前节点
			stack[++stackTop] = pMove;    // 将当前节点入栈
			pMove = pMove->LChild;        // 遍历左子树
		}
		if (stackTop != -1)    // 栈不为空
		{
			pMove = stack[stackTop];  // 取出栈顶节点
			stackTop--;               // 减少栈的大小
			pMove = pMove->RChild;    // 遍历右子树
		}
	}
}

void midOrder(LPTree root)  // 中序遍历
{
	if (root != NULL)            // 当前节点不为空
	{
		midOrder(root->LChild);    // 遍历左子树
		printfData(root);          // 访问当前节点
		midOrder(root->RChild);    // 遍历右子树
	}
}

void midOrderByStack(LPTree root)  // 中序遍历（非递归）
{
	if (root == NULL)  // 根节点为空，直接返回
	{
		return;
	}
	LPTree pMove = root; // 当前节点赋值为根节点
	LPTree stack[NUM] = { 0 }; // 定义一个存储节点的栈
	int stacktop = -1;         // 初始化栈顶为-1
	while (stacktop != -1 || pMove)  // 当栈不为空或当前节点不为空时
	{
		while (pMove)  // 当前节点不为空
		{
			stack[++stacktop] = pMove;   // 将当前节点入栈
			pMove = pMove->LChild;       // 遍历左子树
		}
		if (stacktop != -1)   // 栈不为空
		{
			pMove = stack[stacktop--];   // 取出栈顶节点
			printf("%c\t", pMove->data); // 访问当前节点
			pMove = pMove->RChild;       // 遍历右子树
		}
	}

}

void lastOrder(LPTree root)  // 后序遍历
{
	if (root != NULL)            // 当前节点不为空
	{
		lastOrder(root->LChild);    // 遍历左子树
		lastOrder(root->RChild);    // 遍历右子树
		printfData(root);           // 访问当前节点
	}
}

void lastOrderByStack(LPTree root)  // 后序遍历（非递归）
{
	if (root == NULL)   // 根节点为空，直接返回
		return;
	LPTree pMove = root;    // 当前节点赋值为根节点
	LPTree pLast = NULL;    // 定义一个指向最近访问过的节点的指针，初始为空
	LPTree stack[NUM] = { 0 };  // 定义一个存储节点的栈
	int stacktop = -1;      // 初始化栈顶为-1

	while (pMove)           // 遍历左子树
	{
		stack[++stacktop] = pMove;
		pMove = pMove->LChild;
	}
	while (stacktop != -1)  // 当栈不为空时
	{
	pMove = stack[stacktop--];
	if (pMove->RChild == NULL || pMove->RChild == pLast)  // 若右子树为空或者右子树已经被访问过
	{
		printf("%c\t", pMove->data);  // 访问当前节点
		pLast = pMove;                // 将当前节点更新为最近访问过的节点
	}
	else
	{
		stack[++stacktop] = pMove;   // 将当前节点和右子树入栈
		pMove = pMove->RChild;
		while (pMove)           // 遍历右子树的左子树
		{
			stack[++stacktop] = pMove;
			pMove = pMove->LChild;
		}
	}
	}
}

void initQueue(LPQueue* q)	//初始化队列
{
	if (!((*q) = (LPQueue)malloc(sizeof(LPQueue))))
	{
		printf("Memory allocation failed!");
		return;
	}
	(*q)->front = (*q)->rear = -1;
}

bool emptyQueue(LPQueue q, LPTree curData)
{
	if (q->front == q->rear)
	{
		return false;
	}

	q->rear++;
	q->data[q->rear] = curData;
	return true;
}

bool enQueue(LPQueue q, LPTree curData)
{
	if (q->rear == MAX_SIZE - 1)
		return false;

	q->rear++;
	q->data[q->rear] = curData;
	return true;
}

bool deQueue(LPQueue q, LPTree* curData)
{
	if (q->front == q->rear) {
		return false;
	}

	q->front++;
	*curData = q->data[q->front];
	return true;
}

void levelOrder(LPTree root)
{
	LPQueue q;
	initQueue(&q);
	if (root != NULL)
	{
		enQueue(q, root);
	}

	while (!emptyQueue(q, root))
	{
		deQueue(q, &root);
		printf("%d", root->data);
		if (root->LChild != NULL)
		{
			enQueue(q, root->LChild);
		}
		if (root->RChild != NULL)
		{
			enQueue(q, root->LChild);
		}
	}
}


