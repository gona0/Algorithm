//1868. 파핑파핑 지뢰찾기
#if 0
#pragma warning (disable : 4996)
#include <stdio.h>

typedef struct _st
{
	int r;
	int c;
}ST;

#define MAX	(300+10)
int T, tc;
int N;

char a[MAX][MAX];
//char v[MAX][MAX];

ST Queue[MAX*MAX];
int WP, RP;
int dr[] = { -1, 1, 0, 0, -1, 1, -1, 1 };
int dc[] = { 0, 0, -1, 1, -1, -1, 1, 1 };
void InQueue(int a, int b) { Queue[WP].r = a; Queue[WP++].c = b; }
ST DeQueue(void) { return Queue[RP++]; }

int ans;

//////////////////////////////////////////////////

void aprint(void)
{
	int i;

	printf("=(RP,WP):(%d,%d)====\n", RP, WP);
	for (i = 0; i < N; i++)
	{
		printf("%s\n", a[i]);
	}
}

void init(void)
{
	ans = 0;
}

void input(void)
{
	int i;

	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%s", &a[i][0]);
	}
}

int count_mine(int r, int c)
{
	int i, nr, nc;
	int mine;

	mine = 0;
	for (i = 0; i < 8; i++)
	{
		nr = r + dr[i];
		nc = c + dc[i];
		if (nr<0 || nc<0 || nr>N - 1 || nc>N - 1) continue;
		if (a[nr][nc] == '*')  mine++;
	}
	return mine;
}

void BFS(int sr, int sc)
{
	int i, nr, nc;
	ST out;
	int mine;

	WP = 0;
	RP = 0;

	InQueue(sr, sc);
	a[sr][sc] = '0';
	//v[sr][sc] = '1';

	while (RP<WP)
	{
		out = DeQueue();
		for (i = 0; i < 8; i++)
		{
			nr = out.r + dr[i];
			nc = out.c + dc[i];
			if (nr<0 || nc<0 || nr>N - 1 || nc>N - 1) continue;
			if (a[nr][nc] == '.')// && v[nr][nc] == 0)
			{
				mine = count_mine(nr, nc);
				if (mine == 0) InQueue(nr, nc);
				a[nr][nc] = mine + '0';
				//v[nr][nc] = '1';
			}
		}
	}
}

void output(void)
{
	printf("#%d %d\n", tc, ans);
}

int main(void)
{
	int i, j;

	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		//process1 - BFS
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (a[i][j] == '.' && count_mine(i, j) == 0) //v[i][j]...
				{
					BFS(i, j);
					ans++;
				}
			}
		}
		//process2 - count
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (a[i][j] == '.') ans++;
			}
		}
		output();
	}
	return 0;
}

#endif

//1808 . 지희의 고장난 계산기 //포기
#if 0
#pragma warning (disable:4996)
#include <iostream>

int T, Tc;
int N;
bool Calc[10];
int Divisor[1001];
int C_available;

int ans;

void init_and_input(void){
	C_available = 0;
	for (register int i = 0; i < 10; ++i){
		scanf("%d", &Calc[i]);
		if (Calc[i] == 1) ++C_available;
	}
	scanf("%d", &N);
}

void DFS(int L){
	if (L > C_available) return;

	for (register int i = 0; i < 10; ++i){
		if (Calc[i] == 1)
	}
}

int check(int num){
	//memoization으로 앞에서 나온 숫자들 저장
}

void process(void){
	for (register int i = 2; i*i < N; ++i){
		check(i);
	}
}

void output(void){
	printf("#%d %d", Tc, ans);
}

int main(void){
	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		init_and_input();
		DFS(1);
		process();
		output();
	}
}

#endif
