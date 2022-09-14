#include <stdlib.h> // malloc, atoi
#include <stdio.h>
#include <ctype.h> // isdigit
#include <assert.h> // assert

#define MAX_STACK_SIZE	50

////////////////////////////////////////////////////////////////////////////////
// LIST type definition
typedef struct node
{
	char		data;
	struct node	*left;
	struct node	*right;
} NODE;

typedef struct
{
	NODE	*root;
} TREE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

/* Allocates dynamic memory for a tree head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
TREE *createTree( void); //반만 햇음

/* Deletes all data in tree and recycles memory
*/
void destroyTree( TREE *pTree); //만들어져있음

static void _destroy( NODE *root); //햇

/*  Allocates dynamic memory for a node and returns its address to caller
	return	node pointer
			NULL if overflow
*/
static NODE *_makeNode( char ch); //햇

/* converts postfix expression to binary tree
	return	1 success
			0 invalid postfix expression
*/
int postfix2tree( char *expr, TREE *pTree);

/* Print node in tree using inorder traversal
*/
void traverseTree( TREE *pTree); //만들어져있음

/* internal traversal function
	an implementation of ALGORITHM 6-6
*/
static void _traverse( NODE *root); //다른 알고리즘

/* Print tree using inorder right-to-left traversal
*/
void printTree( TREE *pTree); //만들어져있음

/* internal traversal function
*/
static void _infix_print( NODE *root, int level);

/* evaluate postfix expression
	return	value of expression
*/
float evalPostfix( char *expr);

////////////////////////////////////////////////////////////////////////////////
void destroyTree( TREE *pTree)
{
	if (pTree)
	{
		_destroy( pTree->root);
	}
		
	free( pTree);
}

////////////////////////////////////////////////////////////////////////////////
void printTree( TREE *pTree)
{
	//_infix_print(pTree->root, 0);
	
	return;
}

////////////////////////////////////////////////////////////////////////////////
void traverseTree( TREE *pTree)
{
	_traverse(pTree->root);
	
	return;
}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	TREE *tree;
	char expr[1024];
	
	fprintf( stdout, "\nInput an expression (postfix): ");
	
	while (fscanf( stdin, "%s", expr) == 1)
	{
		// creates a null tree
		tree = createTree();
		
		//if (!tree)
		{
		//	printf( "Cannot create tree\n");
		//	return 100;
		}
		
		// postfix expression -> expression tree
		int ret = postfix2tree( expr, tree);
		if (!ret)
		{
			fprintf( stdout, "invalid expression!\n");
			destroyTree( tree);
			continue;
		}
		
		// expression tree -> infix expression
		fprintf( stdout, "\nInfix expression : ");
		traverseTree( tree);
		
		// print tree with right-to-left infix traversal
		fprintf( stdout, "\n\nTree representation:\n");
		//printTree(tree);
		
		// evaluate postfix expression
		//float val = evalPostfix( expr);
		//fprintf( stdout, "\nValue = %f\n", val);
		
		// destroy tree
		//destroyTree( tree);
		
		fprintf( stdout, "\nInput an expression (postfix): ");
	}
	return 0;
}

TREE* createTree(void) {

	TREE* newTree = (TREE*)malloc(sizeof(TREE));
	newTree->root = NULL;

	return newTree;

}

static NODE* _makeNode(char ch) {
	
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = ch;

	return newNode;
}

/* converts postfix expression to binary tree
	return	1 success
			0 invalid postfix expression
*/
int postfix2tree(char* expr, TREE* pTree) {

	NODE* stack[MAX_STACK_SIZE] = {NULL, };
	int topIndex = -1;
	int len = strlen(expr);
	NODE* pnode;


	for (int i = 0; i < len; i++) {
		pnode = _makeNode(expr[i]);
		
		if (isdigit(expr[i])) {
			topIndex += 1;
			stack[topIndex] = pnode;
		}
		else {
			int rIdx = topIndex;
			topIndex -= 1;
			NODE* temp = stack[rIdx];

			if (pnode->right != NULL) {
				free(pnode->right)
			}
			pnode->right = temp;

			rIdx = topIndex;
			topIndex -= 1;
			temp = stack[rIdx];

			if (pnode->left != NULL) {
				free(pnode->left)
			}
			pnode->left = temp;

			topIndex += 1;
			stack[topIndex] = pnode;
		}
	}

	if (topIndex == 0) {
		pTree->root = stack[topIndex];
		return 1;
	}
	else
		return 0;
}

/* internal traversal function
	an implementation of ALGORITHM 6-6
*/
static void _traverse(NODE* root) {
	
	if (root == NULL)
		return;

	_traverse(root->left);
	printf("%d ", root->data);
	_traverse(root->right);
}

static void _infix_print(NODE* root, int level) {

}

/* evaluate postfix expression
	return	value of expression
*/
float evalPostfix(char* expr) {

}

static void _destroy(NODE* root) {
	if (root == NULL)
		return;

	_destroy(root->left);
	_destroy(root->right);
	_destroy(root);
}
