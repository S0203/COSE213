#ifndef __BST_PRINT_H__
#define __BST_PRINT_H__

#include "BinaryTree3.h"
#include "BinarySearchTree3.h"

typedef enum leftright { ROOT, LEFT, RIGHT } LeftRight;

// BST�� ����� ��� ����� �����͸� ����Ѵ�. (inorder traversal)
void BSTShowAllData(BTreeNode * bst);

// BST�� ����� ��� ����� �����͸� �ڼ��� ����Ѵ�. (���ʳ��, �����ʳ�� ������ ����)
void BSTShowAllNode(BTreeNode * bst);

// BST�� ����� ��� ����� �����͸� ���丮 �������� ����Ѵ�. (Ʈ�� �׸��׸���)
void BSTShowAllTree(BTreeNode * bst);

// BST�� ����� ��� ����� �����͸� ���丮 �������� '����'�� ����Ѵ�.
void FileBSTShowAllTree(BTreeNode * bst, const char *fname);

#endif