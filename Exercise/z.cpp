
#if 0
#pragma warning(disable:4996)
#include <stdio.h>

int n, e, b, tree[10000];

typedef struct _node
{
	int val;
	NODE left;
	NODE right;
}NODE;

int main(void)
{
	scanf("%d", &n);

	return 0;
}
#endif

//p200 연습문제2
#if 0
#include <stdio.h>

char a[100];

void itoa(int n, char * a)
{
	a[0] = (char)n;
}

int main(void)
{
	itoa(49, a);
	printf("%s\n", a);
}

#endif


//#1. 프로시험에 유용한 - 동적할당 대신 사용할수 있는 배열
#if 0
#include <iostream>
using namespace std;

int arr_idx = 0;

struct NODE {
	int v;
	NODE * prev;  //싱글 리스트를 위해 추가.
	NODE() : v(11), prev(0){}
	//NODE(int n) : v(n) {}
} a[10000];

NODE * myalloc(void)
{
	return &a[arr_idx++];
}

void main(void)
{
	NODE * pList = NULL; // 싱글 링크드 리스트의 시작
	NODE * p;

	//NODE q(3); //가능
	//NODE * q(3); //불가능

	arr_idx = 0;  // 배열 초기화

	//첫번째 노드(1) 추가
	p = myalloc();
	//p->v = 1;
	p->prev = pList;

	printf("%d", p->v);
	pList = p;

	//두번째 노드(2) 추가
	p = myalloc();
	p->v = 2;
	p->prev = pList;
	pList = p;

	//추가된 노드 확인
	for (NODE * pp = pList; pp != NULL; pp = pp->prev)
	{
		cout << pp->v << " ";
	}
}

#endif

//z1젼z1응의 NULL을 이용한 linked list
#if 0
#include <iostream>

using namespace std;

//typedef struct st1
//{
//	int a; int b;
//	ST1() : a(0), b(0) {}
//}ST1;

struct Node
{
	int val;
	Node *prev;
	Node *next;
};

Node *nodeHead;

void insertNode(int val, Node *targetNode){
	Node *newNode = new Node();
	newNode->val = val;
	newNode->prev = targetNode;
	newNode->next = targetNode->next;
	newNode->prev->next = newNode;
	newNode->next->prev = newNode;
}

void deleteNode(Node *node){
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete(node);
}

int main(void)
{
	nodeHead = new Node();
	nodeHead->val = -1;
	nodeHead->prev = nodeHead;
	nodeHead->next = nodeHead;
	//널 포인터 노드

	insertNode(1, nodeHead);
	insertNode(2, nodeHead);
	insertNode(4, nodeHead);
	insertNode(3, nodeHead);

	deleteNode(nodeHead->next);
	deleteNode(nodeHead->next);
	deleteNode(nodeHead->next);
	deleteNode(nodeHead->next);
	return 0;
}
#endif

//p322 TSP구현
//문제/알고리즘 분류/그래프/TSP
#if 0
#pragma warning (disable:4996)
#include <iostream>

/* 외판원이 자신의 집이 위치하고 있는 도시에서(1) 출발하여 다른 도시들을 각각 한번씩만 방문하고,
다시 자기 도시로 돌아오는 가장 짧은 일주여행경로를 결정하는 문제.*/
/*헤밀토니안 + weight*/

/* input.txt
4 9
1 2 2
1 3 9
2 1 1
2 3 6
2 4 4
3 2 7
3 4 8
4 1 6
4 2 3
*/

/* output.txt
ans: 21
*/

#define MAX_N	(10)
#define INF		(99)
#define MIN(x,y)	((x)>(y)?(y):(x))
int T, Tc;
int N, K;
int W[MAX_N][MAX_N];
int D[MAX_N][1<<MAX_N];		//이것 때문에 시간복잡도가 지수
int ans;

void vvv1(void){
	int i, j;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%2d ", W[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void vvv2(void){
	int i, j;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= 1<<N; j++)
		{
			printf("%2d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void init_and_input(void)
{
	int a, b, c;

	scanf("%d %d", &N, &K);	
	for (register int i = 1; i <= N; ++i){		
		for (register int j = 1; j <= N; ++j){
			if (i == j) W[i][i] = 0;
			else W[i][j] = INF;
		}
		for (register int j = 1; j <= (2 << N) - 2; ++j){
			D[i][j] = INF;
		}
	}
	for (register int i = 0; i < K; ++i){		
		scanf("%d %d %d", &a, &b, &c);
		W[a][b] = c;
	}
}

int count = 0;
int DP(int sp, int subset)
{
	if (subset == 0) return W[sp][1];	//문제에서 목적지가 1임
	
	int &ret = D[sp][subset];
	if (ret != INF) return ret;

	for (register int i = 1; i <= N; ++i){
		if (i == sp) continue;
		if (subset & (1 << i)){
			ret = MIN(ret, W[sp][i] + DP(i, subset &~(1 << i)));
		}
	}
	return ret;
}

void output(void)
{
	printf("ans: %d\n", ans);
}

int main(void)
{
	init_and_input();
	ans = DP(1, (2 << N) - 2);
	output();
	return 0;
}

#endif

//p310 모든 쌍 최단경로
//문제/알고리즘 분류/그래프/Shortest Path
#if 0
#pragma warning (disable:4996)
#include <iostream>

/* input.txt
5 14
1 2 4
1 3 2
1 4 5
2 3 1
2 5 4
3 1 1
3 2 3
3 4 1
3 5 2
4 1 -2
4 5 2
5 2 -3
5 3 3
5 4 1
*/

/* output.txt
ans: 
*/

#define MAX_N	(10)
#define INF		(99)
#define MIN(x,y)	((x)>(y)?(y):(x))
int T, Tc;
int N, K;
int W[MAX_N][MAX_N];

int ans;

void input(void)
{
	int a, b, c;

	scanf("%d %d", &N, &K);
	for (register int i = 1; i <= N; ++i){
		for (register int j = 1; j <= N; ++j){
			W[i][j] = INF;
		}
	}
	for (register int i = 1; i <= K; ++i){
		scanf("%d %d %d", &a, &b, &c);
		W[a][b] = c;
	}
}

void DP(void)			//int d[MAX_N][MAX_N]이거 인수할 때 포인터 어케?
{
	for (register int k = 1; k <= N; ++k){
		for (register int i = 1; i <= N; ++i){
			if (i == k) continue;
			for (register int j = 1; j <= N; ++j){
				if (j == i || j == k) continue;
				W[i][j] = MIN(W[i][k] + W[k][j], W[i][j]);
			}
		}
	}
}

void output(void)
{
	for (register int i = 1; i <= N; ++i){
		for (register int j = 1; j <= N; ++j){
			printf("%2d ", W[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	input();
	DP();
	output();
	return 0;
}

#endif


