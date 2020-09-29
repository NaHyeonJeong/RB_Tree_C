#include<string.h>
#include<stdlib.h>
#define RED 1
#define BLACK 0

typedef struct Node_ {
	void *key;
	void *value;
	char color;
	struct Node_ *left;
	struct Node_ *right;
} Node;
typedef struct {
	Node *root; // 트리는 루트이다
	int(*compare)(const void *key1, const void *key2);
} RBT;

void rbt_init(RBT *rbt, int(*compare)(const void *key1, const void *key2));
Node *searchR(Node *node, void *k, int(*compare)(const void *key1, const void *key2));
Node *search(RBT tree, void *k);
Node *insertR(Node *node, void *k, void *v, int(*compare)(const void *key1, const void *key2));
void insert(RBT *tree, void *k, void *v);
Node *rotateLeft(Node *h);
Node *rotateRight(Node *h);
void flipColors(Node *h);
int isRed(Node *node);
void destroyR(Node *node);
void destroy(RBT *tree);