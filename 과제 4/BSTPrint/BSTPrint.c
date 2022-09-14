#include "BSTPrint.h"
#include "BinarySearchTree3.h"
#include "BinaryTree3.h"
#include <stdio.h>
#define MAXLOGNUM 100

// BSTShowAll()�� ���� �����Լ� //
void ShowIntData(BSTData data)
{
	printf("%d ", data);
}

// BSTShowAllNode()�� ���� �����Լ�
void PrintData(BTreeNode *bst)
{
	if (bst != NULL)
		printf("%d\n", BSTGetNodeData(bst));
	else
		printf("NULL\n");
}

void BSTShowAllNode(BTreeNode * bst)
{
	if (bst == NULL)
		return;

	printf("NodeData : "); PrintData(bst);
	printf("-> LNode : "); PrintData(GetLeftSubTree(bst));
	printf("-> RNode : "); PrintData(GetRightSubTree(bst));
	putchar('\n');

	BSTShowAllNode(GetLeftSubTree(bst));
	BSTShowAllNode(GetRightSubTree(bst));
}

// BSTShowAllTree()�� ���� �����Լ� //
void PrintBSTData(BTreeNode *bst)
{
	printf("[%d]\n", GetData(bst));
}

// BSTShowAllTree()�� ���� �����Լ� //
void PrintBarAndData(BTreeNode *bst, LeftRight LR[], int bstlevel)
{
	BTreeNode *lNode = GetLeftSubTree(bst);
	BTreeNode *rNode = GetRightSubTree(bst);
	int k;

	// ���ʳ�� ����Ʈ //
	if (lNode != NULL) {
		LR[bstlevel+1] = LEFT;
		PrintBarAndData(lNode, LR, bstlevel+1);
	}
	
	// Ʈ�� ���� ��� //
	for (k=1; k<bstlevel; k++)
	{
		if (LR[k] != LR[k+1])
			printf("��");
		else
			printf("��");
	}
	// ������ ��� //
	if (LR[bstlevel] == LEFT) {           // ���ʳ���϶�
		printf("��"); PrintBSTData(bst);
	} else if (LR[bstlevel] == RIGHT) {   // �����ʳ���϶�
		printf("��"); PrintBSTData(bst);
	} else {                              // ��Ʈ����϶�
		PrintBSTData(bst);
	}

	// �����ʳ�� ����Ʈ //
	if (rNode != NULL) {
		LR[bstlevel+1] = RIGHT;
		PrintBarAndData(rNode, LR, bstlevel+1);
	}
}

void BSTShowAllTree(BTreeNode * bst)
{
	LeftRight LR[MAXLOGNUM];  // Ư�� �������� ��θ� ����

	LR[0] = ROOT;  // ó���� ��Ʈ������� ǥ��
	
	if (bst != NULL)
		PrintBarAndData(bst, LR, 0);
}

//------------------------------------------------------------------------------//

// FileBSTShowAllTree()�� ���� �����Լ� //
void FilePrintBSTData(FILE *wfp, BTreeNode *bst)
{
	fprintf(wfp, "[%d]\n", GetData(bst));
}

// FileBSTShowAllTree()�� ���� �����Լ� //
void FilePrintBarAndData(FILE *wfp, BTreeNode *bst, LeftRight LR[], int bstlevel)
{
	BTreeNode *lNode = GetLeftSubTree(bst);
	BTreeNode *rNode = GetRightSubTree(bst);
	int k;

	// ���ʳ�� ����Ʈ //
	if (lNode != NULL) {
		LR[bstlevel+1] = LEFT;
		FilePrintBarAndData(wfp, lNode, LR, bstlevel+1);
	}
	
	// Ʈ�� ���� ��� //
	for (k=1; k<bstlevel; k++)
	{
		if (LR[k] != LR[k+1])
			fprintf(wfp, "��");
		else
			fprintf(wfp, "��");
	}
	// ������ ��� //
	if (LR[bstlevel] == LEFT) {           // ���ʳ���϶�
		fprintf(wfp, "��"); FilePrintBSTData(wfp, bst);
	} else if (LR[bstlevel] == RIGHT) {   // �����ʳ���϶�
		fprintf(wfp, "��"); FilePrintBSTData(wfp, bst);
	} else {                              // ��Ʈ����϶�
		FilePrintBSTData(wfp, bst);
	}

	// �����ʳ�� ����Ʈ //
	if (rNode != NULL) {
		LR[bstlevel+1] = RIGHT;
		FilePrintBarAndData(wfp, rNode, LR, bstlevel+1);
	}
}

void FileBSTShowAllTree(BTreeNode * bst, const char *fname)
{
	FILE *wfp = NULL;
	LeftRight LR[MAXLOGNUM];  // Ư�� �������� ��θ� ����

	LR[0] = ROOT;  // ó���� ��Ʈ������� ǥ��

	wfp = fopen(fname, "wt");

	if (bst != NULL)
		FilePrintBarAndData(wfp, bst, LR, 0);
	else
		fprintf(wfp, "NULL\n");

	fclose(wfp);
}
