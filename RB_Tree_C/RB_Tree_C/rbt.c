#include"rbt.h"

void rbt_init(RBT *rbt, int(*compare)(const void *key1, const void *key2)) {
	rbt->root = NULL;
	rbt->compare = compare;
}
// compare�� ��ȯ ���� �����̸� ���� �� ���� ���� ��, ����̸� ���� �� ���� ū ��, ������ ������ ������ �ǹ�
/* �˻� */
Node *searchR(Node *node, void *k, int(*compare)(const void *key1, const void *key2)) {
	if (node == NULL) return NULL;
	if (compare(k, node->key) < 0) return searchR(node->left, k, compare);
	if (compare(k, node->key) > 0) return searchR(node->right, k, compare);
	return node;
}
Node *search(RBT tree, void *k) {
	return searchR(tree.root, k, tree.compare);
}
/* ���� : ��Ʈ�� BLACK���� ���Եǰ� �������ʹ� ������ RED�� ���� */
Node *insertR(Node *node, void *k, void *v, int(*compare)(const void *key1, const void *key2)) { // �������� ���� ����
	if (node == NULL) {
		Node *node = (Node *)malloc(sizeof(Node));
		node->key = k;
		node->value = v;
		node->color = RED;
		node->left = node->right = NULL;
		return node;
	}
	
	if (compare(k, node->key) < 0) node->left = insertR(node->left, k, v, compare); // �θ��� ���� ���� ��� ��������
	else if (compare(k, node->key) > 0) node->right = insertR(node->right, k, v, compare); // �θ��Ʈ ���� ū ��� ����������
	else node->value = v; // �̹� ��尡 �ִ� ��쿡�� value�� �ٲ�

	// ���� �� ������ �ʿ��� ����
	if (isRed(node->right) && isRed(node->left)) node = rotateLeft(node); // �θ� ��� ���� ������ �ڽĳ�尡 RED�̰� ���� �ڽĳ�尡 BLACK�̸� ratateLeft
	if (isRed(node->left) && isRed(node->left->left)) node = rotateRight(node); // �θ� ��� ���� ���� �ڽĳ��� ���� �ڽ��� �ڽĳ�尡 ��� RED�̸� rotateRight
	if (isRed(node->left) && isRed(node->right)) flipColors(node); // �θ� ��� ���� �� �ڽ� ��尡 ��� RED�̸� flipColors
	return node;
}
void insert(RBT *tree, void *k, void *v) { // ������ �ʿ��� ������ ȣ���� �� ���
	tree->root = insertR(tree->root, k, v, tree->compare);
	tree->root->color = BLACK;
}
// ����
Node *rotateLeft(Node *h) { // �θ� ��� ���� ������ �ڽĳ�尡 RED�̰� ���� �ڽĳ�尡 BLACK�� ���
	Node *x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}
Node *rotateRight(Node *h) {// �θ� ��� ���� ���� �ڽĳ��� ���� �ڽ��� �ڽĳ�尡 ��� RED
	Node *x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}
void flipColors(Node *h) {// �θ� ��� ���� �� �ڽ� ��尡 ��� RED
	h->color = RED;
	h->left->color = BLACK;
	h->right->color = BLACK;
}
// ��Ÿ
int isRed(Node *node) {
	if (node == NULL) return 0;
	return node->color = RED;
}
void destroyR(Node *node) {
	if (node == NULL) return;
	destroyR(node->left);
	destroyR(node->right);
	free(node); // ���� �Ҵ� ��ȯ
}
void destroy(RBT *tree) {
	destroyR(tree->root);
}