#include "BSTPrint.h"
#include "BinarySearchTree3.h"
#include "BinaryTree3.h"
#include <stdio.h>
#define MAXLOGNUM 100

// BSTShowAll()을 위한 보조함수 //
void ShowIntData(BSTData data)
{
	printf("%d ", data);
}

// BSTShowAllNode()를 위한 보조함수
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

// BSTShowAllTree()를 위한 보조함수 //
void PrintBSTData(BTreeNode *bst)
{
	printf("[%d]\n", GetData(bst));
}

// BSTShowAllTree()를 위한 보조함수 //
void PrintBarAndData(BTreeNode *bst, LeftRight LR[], int bstlevel)
{
	BTreeNode *lNode = GetLeftSubTree(bst);
	BTreeNode *rNode = GetRightSubTree(bst);
	int k;

	// 왼쪽노드 프린트 //
	if (lNode != NULL) {
		LR[bstlevel+1] = LEFT;
		PrintBarAndData(lNode, LR, bstlevel+1);
	}
	
	// 트리 구조 출력 //
	for (k=1; k<bstlevel; k++)
	{
		if (LR[k] != LR[k+1])
			printf("│");
		else
			printf("　");
	}
	// 데이터 출력 //
	if (LR[bstlevel] == LEFT) {           // 왼쪽노드일때
		printf("┌"); PrintBSTData(bst);
	} else if (LR[bstlevel] == RIGHT) {   // 오른쪽노드일때
		printf("└"); PrintBSTData(bst);
	} else {                              // 루트노드일때
		PrintBSTData(bst);
	}

	// 오른쪽노드 프린트 //
	if (rNode != NULL) {
		LR[bstlevel+1] = RIGHT;
		PrintBarAndData(rNode, LR, bstlevel+1);
	}
}

void BSTShowAllTree(BTreeNode * bst)
{
	LeftRight LR[MAXLOGNUM];  // 특정 노드까지의 경로를 저장

	LR[0] = ROOT;  // 처음은 루트노드임을 표시
	
	if (bst != NULL)
		PrintBarAndData(bst, LR, 0);
}

//------------------------------------------------------------------------------//

// FileBSTShowAllTree()를 위한 보조함수 //
void FilePrintBSTData(FILE *wfp, BTreeNode *bst)
{
	fprintf(wfp, "[%d]\n", GetData(bst));
}

// FileBSTShowAllTree()를 위한 보조함수 //
void FilePrintBarAndData(FILE *wfp, BTreeNode *bst, LeftRight LR[], int bstlevel)
{
	BTreeNode *lNode = GetLeftSubTree(bst);
	BTreeNode *rNode = GetRightSubTree(bst);
	int k;

	// 왼쪽노드 프린트 //
	if (lNode != NULL) {
		LR[bstlevel+1] = LEFT;
		FilePrintBarAndData(wfp, lNode, LR, bstlevel+1);
	}
	
	// 트리 구조 출력 //
	for (k=1; k<bstlevel; k++)
	{
		if (LR[k] != LR[k+1])
			fprintf(wfp, "│");
		else
			fprintf(wfp, "　");
	}
	// 데이터 출력 //
	if (LR[bstlevel] == LEFT) {           // 왼쪽노드일때
		fprintf(wfp, "┌"); FilePrintBSTData(wfp, bst);
	} else if (LR[bstlevel] == RIGHT) {   // 오른쪽노드일때
		fprintf(wfp, "└"); FilePrintBSTData(wfp, bst);
	} else {                              // 루트노드일때
		FilePrintBSTData(wfp, bst);
	}

	// 오른쪽노드 프린트 //
	if (rNode != NULL) {
		LR[bstlevel+1] = RIGHT;
		FilePrintBarAndData(wfp, rNode, LR, bstlevel+1);
	}
}

void FileBSTShowAllTree(BTreeNode * bst, const char *fname)
{
	FILE *wfp = NULL;
	LeftRight LR[MAXLOGNUM];  // 특정 노드까지의 경로를 저장

	LR[0] = ROOT;  // 처음은 루트노드임을 표시

	wfp = fopen(fname, "wt");

	if (bst != NULL)
		FilePrintBarAndData(wfp, bst, LR, 0);
	else
		fprintf(wfp, "NULL\n");

	fclose(wfp);
}
