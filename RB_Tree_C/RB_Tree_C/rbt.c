#include"rbt.h"
void rbt_init(RBT *rbt, int(*compare)(const void *key1, const void *key2)) {
	rbt->root = NULL;
	rbt->compare = compare;
}
// 검색
Node *searchR(Node *node, void *k, int(*compare)(const void *key1, const void *key2)) {
	if (node == NULL) return NULL;
	if (compare(k, node->key) < 0) return searchR(node->left, k, compare);
	if (compare(k, node->key) > 0) return searchR(node->right, k, compare);
	return node;
}
Node *search(RBT tree, void *k) {
	return searchR(tree.root, k, tree.compare);
}
Node *insertR(Node *node, void *k, void *v, int(*compare)(const void *key1, const void *key2)) {
	if (node == NULL) {
		Node *node = (Node *)malloc(sizeof(Node));
		node->key = k;
		node->value = v;
		node->color = RED;
		node->left = node->right = NULL;
		return node;
	}
	
	if (compare(k, node->key) < 0) node->left = insertR(node->left, k, v, compare);
	else if (compare(k, node->key) > 0) node->right = insertR(node->right, k, v, compare);
	else node->value = v;

	if (isRed(node->right) && isRed(node->left)) node = rotateLeft(node);
	if (isRed(node->left) && isRed(node->left->left)) node = rotateRight(node);
	if (isRed(node->left) && isRed(node->right)) flipColors(node);
	return node;
}
void insert(RBT *tree, void *k, void *v) {
	tree->root = insertR(tree->root, k, v, tree->compare);
	tree->root->color = BLACK;
}
// 수선
Node *rotateLeft(Node *h) {
	Node *x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}
Node *rotateRight(Node *h) {
	Node *x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}
void flipColors(Node *h) {
	h->color = RED;
	h->left->color = BLACK;
	h->right->color = BLACK;
}
// 기타
int isRed(Node *node) {
	if (node == NULL) return 0;
	return node->color = RED;
}
void destroyR(Node *node) {
	if (node == NULL) return;
	destroyR(node->left);
	destroyR(node->right);
	free(node);
}
void destroy(RBT *tree) {
	destroyR(tree->root);
}