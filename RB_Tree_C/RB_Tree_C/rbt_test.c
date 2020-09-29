#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"rbt.h"
#define N 10000

int my_compare(const void *a, const void *b) {
	return strcmp((char *)a, (char *)b);
}
// ������ȸ
void inorderR(Node *node) { // �������� ���� ��ȸ ����� �ϴ� �Լ�
	if (node == NULL) return;
	inorderR(node->left);
	puts(node->key);
	inorderR(node->right);
}
void inorder(RBT tree) { // ȣ�� �� �� ����� �Լ�
	inorderR(tree.root);
}

int main(void)
{
	// ���� ����
	RBT rbt;
	FILE *fp = NULL;
	int n = 0;
	int i;
	char buffer[100] = "";
	char code[N][10];
	char name[N][90];

	rbt_init(&rbt, my_compare);
	// ���� ó��
	fp = fopen("CARRIERS.txt", "r");
	while (fgets(buffer, 100, fp) != NULL) {
		char *tk;
		char *context;
		tk = strtok(buffer, "\t"); // �� �������� �ڸ�
		strcpy(code[n], tk);
		tk = strtok(NULL, "\n"); // ���� �������� �ڸ�
		strcpy(name[n], tk);
		insert(&rbt, code[n], name[n]);
		n++;
	}
	fclose(fp);
	
	printf("Key of the root node > %s\n", (char *)rbt.root->key);
	// �� 5���� ��ȸ
	for (i = 0; i<5; i++) {
		printf("Enter your search key > ");
		gets_s(buffer, 50);
		if (search(rbt, buffer) == NULL) printf(">> No such Key!\n");
		else printf(">> %s\n", (char *)(search(rbt, buffer)->value));
	}

	destroy(&rbt);
	return 0;
}