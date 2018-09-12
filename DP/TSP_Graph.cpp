//p322 TSP구현
//문제/알고리즘 분류/그래프/TSP
#if 01
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
		int a, b, c;
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
