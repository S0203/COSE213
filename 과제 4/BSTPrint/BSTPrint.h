#ifndef __BST_PRINT_H__
#define __BST_PRINT_H__

#include "BinaryTree3.h"
#include "BinarySearchTree3.h"

typedef enum leftright { ROOT, LEFT, RIGHT } LeftRight;

// BST에 저장된 모든 노드의 데이터를 출력한다. (inorder traversal)
void BSTShowAllData(BTreeNode * bst);

// BST에 저장된 모든 노드의 데이터를 자세히 출력한다. (왼쪽노드, 오른쪽노드 데이터 포함)
void BSTShowAllNode(BTreeNode * bst);

// BST에 저장된 모든 노드의 데이터를 디렉토리 형식으로 출력한다. (트리 그림그리기)
void BSTShowAllTree(BTreeNode * bst);

// BST에 저장된 모든 노드의 데이터를 디렉토리 형식으로 '파일'에 출력한다.
void FileBSTShowAllTree(BTreeNode * bst, const char *fname);

#endif