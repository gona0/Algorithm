//1967. https://www.acmicpc.net/problem/1967

//일단 이거 자식노드가 3개 이상 들어올 수 있음. 나는 좌우만 짰으니까 
//문제/알고리즘 분류/트리
#if 0
#pragma warning (disable : 4996)
#include <iostream>

#define MAX	(10000+5)
//배열
#if 01
struct NODE{
	int w1; 
	int w2;
	int left;
	int right;
	NODE() :w1(0), w2(0), left(0), right(0){}
};

int N;
NODE * A[MAX];
int Sum[MAX][2];

int DP(int a){
	if (!A[a]) return 0;
	if (!Sum[a][0]) Sum[a][0] = DP(A[a]->left) + A[a]->w1;
	if (!Sum[a][1]) Sum[a][1] = DP(A[a]->right) + A[a]->w2;
	
	return (Sum[a][0] > Sum[a][1]) ? Sum[a][0] : Sum[a][1];
}

void insertNode(int p, int c, int w){	
	if (!A[p]) A[p] = new NODE();
	if (!A[c]) A[c] = new NODE();
	
	if (!A[p]->left) {		
		A[p]->left = c;
		A[p]->w1 = w;
		return;
	}
	if (!A[p]->right){
		if (A[p]->left > c){
			A[p]->right = A[p]->left;
			A[p]->w2 = A[p]->w1;
			A[p]->left = c;
			A[p]->w1 = w;			
		}
		else{
			A[p]->right = c;
			A[p]->w2 = w;
		}
		return;
	}
	//else printf("3개가들어와버렸네");
}

int main(void){
	int p, c, w;
	int hub;
	int max;

	scanf("%d", &N);
	for (register int i = 0; i < N-1; ++i){
		scanf("%d %d %d", &p, &c, &w);
		insertNode(p, c, w);
	}
	max = 0;
	DP(1);
	for (register int i = 1; i <= N; ++i){
		hub = Sum[i][0] + Sum[i][1];
		//printf("%d에서 D=%d\n", i,hub);
		if (max < hub) max = hub;
	}
	printf("%d\n", max);
}
#endif
//포인터
#if 01
struct NODE{
	int id;
	int w1;
	int w2;
	NODE * left;
	NODE * right;
	NODE(int n) : id(n), w1(0), w2(0), left(0), right(0){}
};

int N;
NODE * A[MAX];
int Sum[MAX][2];

int DP(NODE * a){
	if (!a) return 0;
	if (!Sum[a->id][0]) Sum[a->id][0] = DP(A[a->id]->left) + A[a->id]->w1;
	if (!Sum[a->id][1]) Sum[a->id][1] = DP(A[a->id]->right) + A[a->id]->w2;

	return (Sum[a->id][0] > Sum[a->id][1]) ? Sum[a->id][0] : Sum[a->id][1];
}

void insertNode(NODE * t, int w){
	if (t->id )
}

int main(void){
	int p, c, w;
	int hub;
	int max;

	//input
	scanf("%d", &N);
	for (register int i = 0; i < N - 1; ++i){
		scanf("%d %d %d", &p, &c, &w);
		insertNode(p, c, w);
	}

	//make a tree
	NODE * root;


	max = 0;
	DP(1);
	for (register int i = 1; i <= N; ++i){
		hub = Sum[i][0] + Sum[i][1];
		//printf("%d에서 D=%d\n", i,hub);
		if (max < hub) max = hub;
	}
	printf("%d\n", max);
}
#endif

#endif
