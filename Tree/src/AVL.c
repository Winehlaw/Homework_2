#include"head.h"

static AVLTree CreateNode(ElemType key, AVLTree LChild, AVLTree RChild)	//创建节点
{
	AVLTree p;

	if ((p = (AVLTree)malloc(sizeof(TREE))) == NULL)
		return NULL;

	p->key = key;
	p->height = 0;
	p->LChild = LChild;
	p->RChild = RChild;

	return p;
}

int getHeight(AVLTree curData)
{
	return (curData == NULL ? 0 : curData->height);
}

void preOrderAVLtree(AVLTree root)
{
	if (root != NULL)
	{
		printf("%d ", root->key);
		preOrderAVLtree(root->LChild);
		preOrderAVLtree(root->RChild);
	}
}

void midOrderAVLtree(AVLTree root)
{
	if (root != NULL)
	{
		midOrderAVLtree(root->LChild);
		printf("%d ", root->key);
		midOrderAVLtree(root->RChild);
	}
}

AVLTree SearchAVLnode(AVLTree Node, ElemType key)
{
	if (Node == NULL || Node->key == key)
	{
		return Node;
	}

	if (key < Node->key)
	{
		return SearchAVLnode(Node->LChild, key);
	}
	else
	{
		return SearchAVLnode(Node->RChild, key);
	}
}

void lastOrderAVLtree(AVLTree root)
{
	if (root != NULL)
	{
		lastOrderAVLtree(root->LChild);
		lastOrderAVLtree(root->RChild);
		printf("%d ", root->key);
	}
}

static AVLTree LLrotation(AVLTree root)
{
	AVLTree pNode;
	pNode = root->LChild;
	root->LChild = pNode->RChild;
	pNode->RChild = root;

	root->height = MAX(getHeight(root->LChild), getHeight(root->RChild)) + 1;
	pNode->height = MAX(getHeight(pNode->LChild), root->height) + 1;

	return pNode;

}

static AVLTree RRrotation(AVLTree root)
{
	AVLTree pNode;

	pNode = root->RChild;
	root->RChild = pNode->LChild;
	pNode->LChild = root;

	root->height = MAX(getHeight(root->LChild), getHeight(root->RChild)) + 1;
	pNode->height = MAX(getHeight(pNode->RChild), root->height) + 1;

	return pNode;
}

static AVLTree LRrotation(AVLTree root)
{
	root->LChild = RRrotation(root->LChild);

	return LLrotation(root);
}

static AVLTree RLrotation(AVLTree root)
{
	root->RChild = LLrotation(root->RChild);

	return RRrotation(root);
}

AVLTree AVL_min(AVLTree root)
{
	if (root == NULL)
		return NULL;
	while (root->LChild != NULL)
		root = root->LChild;
	return root;
}

AVLTree AVL_max(AVLTree root)
{
	if (root == NULL)
		return NULL;
	while (root->RChild != NULL)
		root = root->RChild;
	return root;
}

AVLTree insertTree(AVLTree root, ElemType key)
{
	if (root == NULL)
	{
		root = CreateNode(key, NULL, NULL);
		if (root == NULL)
		{
			printf("ERROR:create AVLtree Node failed!\n");
			return NULL;
		}
	}
	else if (key < root->key)	//将key插入到root的左子树
	{
		root->LChild = insertTree(root->LChild, key);	//调节

		if (getHeight(root->LChild) - getHeight(root->RChild) == 2)
		{
			if (key < root->LChild->key)
				root = LLrotation(root);
			else
				root = LRrotation(root);
		}
	}
	else if (key > root->key)
	{
		root->RChild = insertTree(root->RChild, key);

		if (getHeight(root->RChild) - getHeight(root->LChild) == 2)
		{
			if (key > root->RChild->key)
				root = RRrotation(root);
			else
				root = RLrotation(root);
		}
	}
	else
	{
		printf("ERROR:Adding the same node is not allowed!\n");
	}

	root->height = MAX(getHeight(root->LChild), getHeight(root->RChild)) + 1;

	return root;
}

static AVLTree DelNode(AVLTree root, AVLTree pNode)
{
	if (root == NULL || pNode == NULL)
		return NULL;

	if (pNode->key < root->key)
	{
		root->LChild = DelNode(root->LChild, pNode);
		if (getHeight(root->RChild) - getHeight(root->LChild) == 2)
		{
			AVLTree pMove = root->RChild;
			if (getHeight(pMove->LChild) > getHeight(pMove->RChild))
				root = RLrotation(root);
			else
				root = RRrotation(root);
		}
	}
	else if (pNode->key > root->key)
	{
		root->RChild = DelNode(root->RChild, pNode);
		if (getHeight(root->LChild) - getHeight(root->RChild) == 2)
		{
			AVLTree pMove = root->LChild;
			if (getHeight(pMove->RChild) > getHeight(pMove->LChild))
				root = LRrotation(root);
			else
				root = LLrotation(root);
		}
	}
	else
	{
		if ((root->LChild) && (root->RChild))
		{
			if (getHeight(root->LChild) > getHeight(root->RChild))
			{
				AVLTree max = AVL_max(root->LChild);
				root->key = max->key;
				root->LChild = DelNode(root->LChild, max);
			}
			else
			{
				AVLTree min = AVL_max(root->RChild);
				root->key = min->key;
				root->RChild = DelNode(root->RChild, min);
			}
		}
		else
		{
			AVLTree temp = root;
			root = root->LChild ? root->LChild : root->RChild;
			free(temp);
		}
	}

	return root;
}

AVLTree AVL_del(AVLTree root, ElemType key)
{
	AVLTree pNode;
	if ((pNode = SearchAVLnode(root, key)) != NULL)
		root = DelNode(root, pNode);
	return root;
}

void desAVLtree(AVLTree root)
{
	if (root == NULL)
	{
		printf("Empty.\n");
		return;
	}
	if (root->LChild != NULL)
		desAVLtree(root->LChild);
	if (root->RChild != NULL)
		desAVLtree(root->RChild);

	free(root);
}

void printfAVLtree(AVLTree Node, ElemType key, int direction)
{
	if (Node != NULL)
	{
		if (direction == 0)
			printf("%2d is root.\n", Node->key);
		else
			printf("%2d is %2d's %6s child.\n", Node->key, key, direction == 1 ? "RChild" : "LChild");

		printfAVLtree(Node->LChild, Node->key, -1);
		printfAVLtree(Node->RChild, Node->key, 1);
	}
}

