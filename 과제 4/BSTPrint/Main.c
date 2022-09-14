#include "BinaryTree3.h"
#include "BinarySearchTree3.h"
#include "BSTPrint.h"
#include <stdio.h>
#define FILE_NAME "tree.txt"

int main(void)
{
	BTreeNode * avlRoot;
	int i;

	BSTMakeAndInit(&avlRoot);

	for (i=1; i<=10; i++)
		BSTInsert(&avlRoot, i);

	printf("루트 노드: %d \n", GetData(avlRoot));
	
	//FileBSTShowAllTree(avlRoot, FILE_NAME);
	BSTShowAllTree(avlRoot);

	return 0;
}