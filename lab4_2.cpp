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
int duplicateFound = 0;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
  if (r == NULL)
  {
    r = (struct Node*)malloc(sizeof(struct Node));
    if (r == NULL)
    {
      printf("Ошибка выделения памяти");
      exit(0);
    }

    r->left = NULL;
    r->right = NULL;
    r->data = data;
    if (root == NULL) return r;

    if (data > root->data)  root->left = r;
    else                    root->right = r;
    return r;
  }

  if (data == r->data)
  {
    duplicateFound = 1;
    return root;
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

  printf("%d (%d)\n", r->data, l);  
  print_tree(r->left, l + 1);
}

int main()
{
  setlocale(LC_ALL, "");
  int D, start = 1;

  root = NULL;
  printf("-1 - окончание построения дерева\n");
  while (start)
  {
    printf("Введите число: ");
    scanf_s("%d", &D);
    if (D == -1)
    {
      printf("Построение дерева окончено\n\n");
      start = 0;
    }
    else
    {
      duplicateFound = 0;
      root = CreateTree(root, root, D);
      if (duplicateFound)
        printf("  >>> Число %d уже было введено ранее, повторно не добавлено\n", D);
    }
  }

  print_tree(root, 0);

  scanf_s("%d", &D);
  return 0;
}
