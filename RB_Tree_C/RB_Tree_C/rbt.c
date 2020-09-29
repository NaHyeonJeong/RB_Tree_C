#include"rbt.h"

void rbt_init(RBT *rbt, int(*compare)(const void *key1, const void *key2)) {
	rbt->root = NULL;
	rbt->compare = compare;
}
// compare의 반환 값이 음수이면 앞의 값 보다 작은 것, 양수이면 앞의 값 보다 큰 것, 같으면 순서가 맞음을 의미
/* 검색 */
Node *searchR(Node *node, void *k, int(*compare)(const void *key1, const void *key2)) {
	if (node == NULL) return NULL;
	if (compare(k, node->key) < 0) return searchR(node->left, k, compare);
	if (compare(k, node->key) > 0) return searchR(node->right, k, compare);
	return node;
}
Node *search(RBT tree, void *k) {
	return searchR(tree.root, k, tree.compare);
}
/* 삽입 : 루트는 BLACK으로 삽입되고 다음부터는 무조건 RED로 삽입 */
Node *insertR(Node *node, void *k, void *v, int(*compare)(const void *key1, const void *key2)) { // 실질적인 삽입 과정
	if (node == NULL) {
		Node *node = (Node *)malloc(sizeof(Node));
		node->key = k;
		node->value = v;
		node->color = RED;
		node->left = node->right = NULL;
		return node;
	}
	
	if (compare(k, node->key) < 0) node->left = insertR(node->left, k, v, compare); // 부모노드 보다 작은 경우 왼쪽으로
	else if (compare(k, node->key) > 0) node->right = insertR(node->right, k, v, compare); // 부모노트 보다 큰 경우 오른쪽으로
	else node->value = v; // 이미 노드가 있는 경우에는 value만 바꿈

	// 삽입 후 수선이 필요한 경우들
	if (isRed(node->right) && isRed(node->left)) node = rotateLeft(node); // 부모 노드 기준 오른쪽 자식노드가 RED이고 왼쪽 자식노드가 BLACK이면 ratateLeft
	if (isRed(node->left) && isRed(node->left->left)) node = rotateRight(node); // 부모 노드 기준 왼쪽 자식노드와 왼쪽 자식의 자식노드가 모두 RED이면 rotateRight
	if (isRed(node->left) && isRed(node->right)) flipColors(node); // 부모 노드 기준 두 자식 노드가 모두 RED이면 flipColors
	return node;
}
void insert(RBT *tree, void *k, void *v) { // 삽입이 필요한 곳에서 호출할 때 사용
	tree->root = insertR(tree->root, k, v, tree->compare);
	tree->root->color = BLACK;
}
// 수선
Node *rotateLeft(Node *h) { // 부모 노드 기준 오른쪽 자식노드가 RED이고 왼쪽 자식노드가 BLACK인 경우
	Node *x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}
Node *rotateRight(Node *h) {// 부모 노드 기준 왼쪽 자식노드와 왼쪽 자식의 자식노드가 모두 RED
	Node *x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}
void flipColors(Node *h) {// 부모 노드 기준 두 자식 노드가 모두 RED
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
	free(node); // 동적 할당 반환
}
void destroy(RBT *tree) {
	destroyR(tree->root);
}