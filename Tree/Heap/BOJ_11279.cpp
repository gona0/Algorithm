//BOJ_11279 최대 힙
//https://www.acmicpc.net/problem/11279

#if 01
#pragma warning(disable:4996)
#include <iostream>

#define MAX	(100001)

int N;
int Heap[MAX];
int HP;

#define SWAP(x,y)	{int temp; temp=x; x=y; y=temp;}
void PushHeap(int x)
{
	Heap[++HP] = x;	//마지막 위치에 삽입
	for (int i = HP; i > 1; i /= 2) {
		if (Heap[i / 2] < Heap[i]) SWAP(Heap[i / 2], Heap[i])
		else break;
	}
}

int PopHeap(void)
{
	int ans = Heap[1];
	Heap[1] = Heap[HP];
	Heap[HP--] = 0;

	for (int i = 1; i * 2 <= HP;)
	{
		if (Heap[i] > Heap[i * 2] && Heap[i] > Heap[i * 2 + 1]) break;
		else if (Heap[i * 2] > Heap[i * 2 + 1])
		{
			SWAP(Heap[i], Heap[2 * i]);
			i = 2 * i;
		}
		else
		{
			SWAP(Heap[i], Heap[2 * i + 1]);
			i = 2 * i + 1;
		}
	}
	return ans;
}

int main(void)
{
	int hub;

	scanf("%d", &N);
	for (register int i = 0; i < N; ++i){
		scanf("%d", &hub);
		if (hub == 0) {
			if (HP == 0) printf("0\n");
			else printf("%d\n", PopHeap());
		}
		else PushHeap(hub);
	}
	return 0;
}

#endif
