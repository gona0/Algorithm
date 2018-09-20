//[5강 3번] 간담회 참석	
#if 0
#include <iostream>

#define MAX_N	(50001)
#define MAX_M	(500001)
int T, Tc;
int N, M, X;
int Max_interval;
int D_X[MAX_N];

////////////////////////////////Node
struct Node
{
	int sp; int ep; int w;
	Node * next;
	Node(int s, int e, int t) : sp(s), ep(e), w(t), next(this){}
};
Node Head[MAX_N];

void insertNode(int s, int e, int t)
{
	Node * newNode = new Node(s, e, t);
	newNode->next = Head[s].next;
	Head[s].next = newNode;
}

////////////////////////////////Heap
#define SWAP(x,y)	{Node * temp; temp=x; x=y; y=temp;}
Node * Heap[MAX_M];
int HP;

void initHeap(void) { HP = 0; }

void PushHeap(Node * x)
{
	Heap[++HP] = x;
	for (register int i = HP; i > 1; i /= 2){
		if (Heap[i]->w < Heap[i / 2]->w) SWAP(Heap[i], Heap[i / 2])	
		else break;
	}
}

Node * PopHeap(void)	//나중에 void -> Node**
{
	Node * ans = Heap[1];
	Heap[1] = Heap[HP];
	Heap[HP--] = 0;

	for (register int i = 1; 2*i < HP;){
		if (Heap[i]->w < Heap[2 * i]->w && Heap[i]->w < Heap[2 * i + 1]->w) break;
		else if (Heap[2 * i]->w < Heap[2 * i + 1]->w){
			SWAP(Heap[i], Heap[2 * i]);
			i = 2 * i;
		}
		else{
			SWAP(Heap[i], Heap[2 * i + 1]);
			i = 2 * i + 1;
		}
	}
	return ans;
}

////////////////////////////////Code
#define MAX(x,y)	((x)>(y)?(x):(y))
#define MIN(x,y)	((x)<(y)?(x):(y))
void init_and_input(void)
{
	int s, e, t;
	//init
	Max_interval = 0;
	for (register int i = 0; i <= N; ++i) D[i] = 0;
	//input
	scanf("%d%d%d", &N, &M, &X);
	for (register int i = 0; i < M; ++i){
		scanf("%d%d%d", &s, &e, &t);
		insertNode(s, e, t);
	}
}

void dijkstra(int sp, int * D)
{

}

int main(void)
{
	scanf("%T", &T);
	for (Tc = 1; Tc <= T; ++Tc)
	{
		//
		init_and_input();
		//process
		dijkstra(X, D_X);
		for (register int i = 1; i <= N; ++i){
			if (i == X) continue;
			int D[MAX_N] = { 0 };
			dijkstra(i, D);
			Max_interval = MAX(Max_interval, D[X] + D_X[i]);
		}
		//output
		printf("#%d %d\n", Tc, Max_interval);
	}
	return 0;
}

#endif
