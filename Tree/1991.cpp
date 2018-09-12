//1991. https://www.acmicpc.net/problem/1991

//문제/알고리즘 분류/트리
#if 01
#pragma warning (disable:4996)
#include <iostream>
#include <string>
#define MAX 26

//배열 이용
#if 01
struct NODE
{
	char val;
	char parent;
	char left;
	char right;
	NODE(char a) : val(a), parent(val){}
};
NODE * p[MAX];

void preorder(char a){
	if (!p[a - 'A']) return;
	printf("%c", a);
	preorder(p[a - 'A']->left);
	preorder(p[a - 'A']->right);
}
void inorder(char a){
	if (!p[a - 'A']) return;
	inorder(p[a - 'A']->left);
	printf("%c", a);
	inorder(p[a - 'A']->right);
}
void postorder(char a){
	if (!p[a - 'A']) return;
	postorder(p[a - 'A']->left);
	postorder(p[a - 'A']->right);
	printf("%c", a);
}

int main(void) {
	int N;
	char a[3];

	scanf("%d", &N);
	for (register int i = 1; i <= N; ++i){
		for (register int j = 0; j < 3; ++j){
			scanf(" %c", &a[j]);
		}		
		p[a[0] - 'A'] = new NODE(a[0]);
		p[a[0] - 'A']->left = a[1];
		p[a[0] - 'A']->right = a[2];
		if (a[1] != '.'){
			if (p[a[1] - 'A'] == 0) p[a[1] - 'A'] = new NODE(a[1]);
			p[a[1] - 'A']->parent = a[0];
		}
		if (a[2] != '.'){
			if (p[a[2] - 'A'] == 0) p[a[2] - 'A'] = new NODE(a[2]);
			p[a[2] - 'A']->parent = a[0];
		}
	}

	preorder('A');
	printf("\n");
	inorder('A');
	printf("\n");
	postorder('A');
	printf("\n");
		
	return 0;
}
#endif 

//배열 이용해서 풀기 - henry 방법 들어있씁니다.
#if 0
#include <stdio.h>

int n, a, b, tree[100][2];

void preorder(int x)
{
	if (!x) return;
	printf("%d ", x);
	preorder(tree[x][0]);
	preorder(tree[x][1]);
}

void inorder(int x)
{
	if (!x) return;
	inorder(tree[x][0]);
	printf("%d ", x);
	inorder(tree[x][1]);
}

void postorder(int x)
{
	if (!x) return;
	postorder(tree[x][0]);
	postorder(tree[x][1]);
	printf("%d ", x);
}

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d %d", &a, &b);
		if (!tree[a][0]) tree[a][0] = b;
		else tree[a][1] = b;
	}
	preorder(1);
	printf("\n");
	inorder(1);
	printf("\n");
	postorder(1);
	printf("\n");
	return 0;
}

#endif

#endif
