#include"head.h"

LPTree createNode(ElemType data)  // �����ڵ㺯��������һ��ָ���½ڵ��ָ��
{
	LPTree newNode = (LPTree)malloc(sizeof(Tree));  // Ϊ�ڵ�����ڴ�ռ�
	newNode->data = data;                           // ��ֵ����
	newNode->LChild = NULL;                         // ��ʼ����������
	newNode->RChild = NULL;
	return newNode;
}

void insertNode(LPTree parentNode, LPTree LChild, LPTree RChild)	//����
{
	parentNode->LChild = LChild;  // ����ڵ�
	parentNode->RChild = RChild;
}

void InsertNode(LPTree curData, LPTree* root)	//����ڵ�
{//��Ϊ���ڵ���ܱ��޸ģ����Դ�����ָ��
//������ڵ��data�͸��ڵ��data���Ƚϣ�С�Ĳ�����ڵ������������֮�����������

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

void* parentNode(LPTree curData, LPTree root)	//�ҵ�ָ���ڵ�ĸ��ڵ�
{
	if (curData == NULL || root == NULL || root == curData)	//�ж��Ƿ�Ϊ��ָ�룬�Լ�root���޸��ڵ�
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
	LPTree pNode = parentNode(delData, *root);	//ɾ���ڵ�ĸ��ڵ�

	if (delData == NULL || root == NULL)
		return;
	
	if (delData != *root && pNode == NULL)	//ɾ���ڵ㲻��root��˵��û���ҵ�Ҫɾ���Ľڵ�
		return;

	if (delData->LChild == NULL && delData->RChild == NULL)	//ɾ���ڵ�ΪҶ�ӽڵ�
	{
		if(*root == delData)	//Ҫɾ���Ľڵ���root�ڵ�
		{
			*root = NULL;
			return;
		}

		if (pNode->LChild == delData)
			pNode->LChild = NULL;
		if (pNode->RChild == delData)
			pNode->RChild = NULL;
	}

	else if (delData->LChild == NULL || delData->RChild == NULL)	//Ҫɾ���Ľڵ�ֻ����������������
	{
		if (*root == delData)	//Ҫɾ���Ľڵ��Ǹ��ڵ�
		{
			if ((*root)->LChild != NULL)	//ɾ���ڵ�ֻ��������
				(*root) = (*root)->LChild;
			else if ((*root)->RChild != NULL)	//ɾ���ڵ�ֻ��������
				(*root) = (*root)->RChild;
		}
		else if (delData->LChild != NULL)	//ɾ���ڵ�ֻ��������
		{
			if (pNode->LChild == delData)	//ɾ���ڵ��Ǹ��ڵ�����ӽڵ�
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
	else if (delData->LChild != NULL && delData->RChild != NULL)	//ɾ���ڵ�����������������
	{
		LPTree repNode = maxNode(delData->LChild);	
		//�ҵ�ɾ���ڵ�������������ҽڵ���Ϊ����ڵ㣬����ڵ���ɾ���ڵ�����
		LPTree pNode = parentNode(repNode, *root);	//�ҵ�����ڵ�ĸ��ڵ�

		if (*root == delData)
		{
			pNode->RChild = repNode->LChild;	
			repNode->LChild = (*root)->LChild;	//������ڵ����������Ϊɾ���ڵ��������
			repNode->RChild = (*root)->RChild;	//������ڵ����������Ϊɾ���ڵ��������
			(*root) = repNode;					//������ڵ����ԭ����ɾ���ڵ��Ϊ�µĸ��ڵ���߸�������ڵ�ĸ��ڵ���ӽڵ�Ϊ����ڵ�
		}
		else if (pNode->LChild == delData)	//ɾ���ڵ����丸�ڵ�����ӽڵ�
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

LPTree searchNode(LPTree root, ElemType data)	//����ָ�����ݵĽڵ�
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

void printfData(LPTree curData)  // ��ӡ�ڵ�����
{
	printf("%c\t", curData->data);
}

void preOrder(LPTree root)  // �������
{
	if (root != NULL)            // ��ǰ�ڵ㲻Ϊ��
	{
		printfData(root);          // ���ʵ�ǰ�ڵ�
		preOrder(root->LChild);    // ����������
		preOrder(root->RChild);    // ����������
	}
}

void preOrderByStack(LPTree root)  // ����������ǵݹ飩
{
	if (root == NULL)  // ���ڵ�Ϊ�գ�ֱ�ӷ���
	{
		return;
	}
	LPTree stack[NUM]; // ����һ��ջ���洢�ڵ�
	int stackTop = -1; // ��ʼ��ջ��Ϊ-1
	LPTree pMove = root; // ��ǰ�ڵ㸳ֵΪ���ڵ�
	while (stackTop != -1 || pMove) // ��ջ��Ϊ�ջ�ǰ�ڵ㲻Ϊ��ʱ
	{
		while (pMove) // ��ǰ�ڵ㲻Ϊ��
		{
			printf("%c\t", pMove->data);  // ���ʵ�ǰ�ڵ�
			stack[++stackTop] = pMove;    // ����ǰ�ڵ���ջ
			pMove = pMove->LChild;        // ����������
		}
		if (stackTop != -1)    // ջ��Ϊ��
		{
			pMove = stack[stackTop];  // ȡ��ջ���ڵ�
			stackTop--;               // ����ջ�Ĵ�С
			pMove = pMove->RChild;    // ����������
		}
	}
}

void midOrder(LPTree root)  // �������
{
	if (root != NULL)            // ��ǰ�ڵ㲻Ϊ��
	{
		midOrder(root->LChild);    // ����������
		printfData(root);          // ���ʵ�ǰ�ڵ�
		midOrder(root->RChild);    // ����������
	}
}

void midOrderByStack(LPTree root)  // ����������ǵݹ飩
{
	if (root == NULL)  // ���ڵ�Ϊ�գ�ֱ�ӷ���
	{
		return;
	}
	LPTree pMove = root; // ��ǰ�ڵ㸳ֵΪ���ڵ�
	LPTree stack[NUM] = { 0 }; // ����һ���洢�ڵ��ջ
	int stacktop = -1;         // ��ʼ��ջ��Ϊ-1
	while (stacktop != -1 || pMove)  // ��ջ��Ϊ�ջ�ǰ�ڵ㲻Ϊ��ʱ
	{
		while (pMove)  // ��ǰ�ڵ㲻Ϊ��
		{
			stack[++stacktop] = pMove;   // ����ǰ�ڵ���ջ
			pMove = pMove->LChild;       // ����������
		}
		if (stacktop != -1)   // ջ��Ϊ��
		{
			pMove = stack[stacktop--];   // ȡ��ջ���ڵ�
			printf("%c\t", pMove->data); // ���ʵ�ǰ�ڵ�
			pMove = pMove->RChild;       // ����������
		}
	}

}

void lastOrder(LPTree root)  // �������
{
	if (root != NULL)            // ��ǰ�ڵ㲻Ϊ��
	{
		lastOrder(root->LChild);    // ����������
		lastOrder(root->RChild);    // ����������
		printfData(root);           // ���ʵ�ǰ�ڵ�
	}
}

void lastOrderByStack(LPTree root)  // ����������ǵݹ飩
{
	if (root == NULL)   // ���ڵ�Ϊ�գ�ֱ�ӷ���
		return;
	LPTree pMove = root;    // ��ǰ�ڵ㸳ֵΪ���ڵ�
	LPTree pLast = NULL;    // ����һ��ָ��������ʹ��Ľڵ��ָ�룬��ʼΪ��
	LPTree stack[NUM] = { 0 };  // ����һ���洢�ڵ��ջ
	int stacktop = -1;      // ��ʼ��ջ��Ϊ-1

	while (pMove)           // ����������
	{
		stack[++stacktop] = pMove;
		pMove = pMove->LChild;
	}
	while (stacktop != -1)  // ��ջ��Ϊ��ʱ
	{
	pMove = stack[stacktop--];
	if (pMove->RChild == NULL || pMove->RChild == pLast)  // ��������Ϊ�ջ����������Ѿ������ʹ�
	{
		printf("%c\t", pMove->data);  // ���ʵ�ǰ�ڵ�
		pLast = pMove;                // ����ǰ�ڵ����Ϊ������ʹ��Ľڵ�
	}
	else
	{
		stack[++stacktop] = pMove;   // ����ǰ�ڵ����������ջ
		pMove = pMove->RChild;
		while (pMove)           // ������������������
		{
			stack[++stacktop] = pMove;
			pMove = pMove->LChild;
		}
	}
	}
}

void initQueue(LPQueue* q)	//��ʼ������
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


