#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("ќшибка выделени€ пам€ти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data) root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

struct Node* FindNode(struct Node* r, int data)
{
	if (r == NULL)
		return NULL;

	if (r->data == data)
		return r;

	if (data > r->data)
		return FindNode(r->left, data);
	else
		return FindNode(r->right, data);
}

int CountOccurrences(struct Node* r, int data)
{
	if (r == NULL)
		return 0;

	int count = (r->data == data) ? 1 : 0;

	count += CountOccurrences(r->left, data);
	count += CountOccurrences(r->right, data);

	return count;
}

int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1;
	struct Node* found;

	root = NULL;
	printf("-1 - окончание построени€ дерева\n");
	while (start)
	{
		printf("¬ведите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("ѕостроение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}

	print_tree(root, 0);
	printf("\n¬ведите значение дл€ поиска: ");
	scanf_s("%d", &D);

	found = FindNode(root, D);
	if (found != NULL)
		printf("Ёлемент %d найден\n", found->data);
	else
		printf("Ёлемент %d в дереве не найден\n", D);

	printf("\n¬ведите значение дл€ подсчЄта: ");
	scanf_s("%d", &D);

	int cnt = CountOccurrences(root, D);
	if (cnt == 0)
		printf("Ёлемент %d в дереве не встречаетс€\n", D);
	else
		printf("Ёлемент %d встречаетс€ %d раз(а)\n", D, cnt);

	scanf_s("%d", &D);
	return 0;
}