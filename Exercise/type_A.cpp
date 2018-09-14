//1204 .[S / W 문제해결 기본] 1일차 - 최빈수 구하기
#if 0
#pragma warning(disable:4996)
#include <stdio.h>

typedef struct st_
{
	int num;
	int val;
}ST;

#define SWAP(x,y)	{ST temp; temp=x; x=y; y=temp;}
int T, tc;
ST a[100+10];


void init(void)
{
	int i;

	for (i = 0; i <= 100; i++)
	{
		a[i].val = 0;
	}
}

void input(void)
{
	int i;
	int score;

	scanf("%d", &tc);
	for (i = 1; i <= 1000; i++)
	{
		scanf("%d", &score);
		a[score].num = score;
		a[score].val++;		
	}
}

void sort(void)
{
	int i, j;

	for (i = 1; i <= 100; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (a[j].val < a[i].val)
			{
				SWAP(a[i], a[j]);
			}
			else if (a[j].val == a[i].val && a[j].num < a[i].num)
			{
				SWAP(a[i], a[j]);
			}
		}
	}
}

void output(void)
{
	printf("#%d %d\n", tc, a[0].num);
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		sort();
		output();
	}

	return 0;
}

#endif

//1206 .  [S/W 문제해결 기본] 1일차 - View 
//시간이 너무 걸리네 39ms
#if 0
#pragma warning (disable:4996)
#include <stdio.h>

bool a[1000 + 10][255 + 10];

int main(void)
{
	int tc;
	int N;
	int height;
	int count;
	int flag;
	
	int i, j, k;
	
	for (tc = 1; tc <= 10; tc++)
	{
		scanf("%d", &N);
		//init
		count = 0;
		flag = 0;
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= 255; j++)
			{
				a[i][j] = 0;
			}
		}
		//input
		for (i = 1; i <= N; i++)
		{
			scanf("%d", &height);
			for (j = 1; j <= height; j++)
			{
				a[i][j] = 1;
			}
		}
		//process
		for (i = 1; i <= N; i++)
		{
			for (j = 1; a[i][j] != 0; j++)
			{
				flag = 0;
				for (k = -2; k <= 2; k++)
				{
					if (k == 0) continue;
					if (a[i + k][j] == 1) flag = 1;
				}
				if (flag == 0) count++;
			}
		}
		//output
		printf("#%d %d\n", tc, count);		
	}
}


#endif

//다시... 굳
#if 0
#pragma warning (disable:4996)
#include <stdio.h>

#define MAX	(1000+5)
#define max(a,b)	((a)>(b)?(a):(b))
int tc;
int N;
int a[MAX];

int main(void)
{
	int i;
	int count;
	

	for (tc = 1; tc <= 10; tc++)
	{
		scanf("%d", &N);
		//init
		count = 0;
		//input			
		for (i = 1; i <= N; i++)
		{
			scanf("%d", &a[i]);
		}
		//process
		for (i = 3; i <= N - 2; i++)
		{
			count += max(0, a[i] - max(max(a[i - 2], a[i - 1]), max(a[i + 1], a[i + 2])));
		}
		//output
		printf("#%d %d\n", tc, count);
	}
}

#endif

//1208 .  [S/W 문제해결 기본] 1일차 - Flatten 
#if 0
#pragma warning (disable:4996)
#include <stdio.h>

#define MAX	(100+10)

int a[MAX];

int main(void)
{
	int i, j, tc;
	int crate;
	int N, L, H;
	
	for (tc = 1; tc <= 10; tc++)
	{
		//init()
		H = 100;
		L = 1;
		for (i = 1; i <= 100; i++)
		{
			a[i] = 0;
		}
		//input()
		scanf("%d", &N);
		for (i = 1; i <= 100; i++)
		{
			scanf("%d", &crate);
			for (j = 1; j <= crate; j++)
			{
				a[j]++;
			}			
		}
		//process()
		while (N)
		{
			while (a[L] == 100) L++;
			while (a[H] == 0) H--;			
			a[L]++;
			a[H]--;
			N--;
		}
		//귀찮아서 그냥 한번더
		for (i = 1; i < 100; i++)
		{
			if (a[i] == 100 && a[i + 1] != 100) L = i;
			if (a[i] != 0 && a[i + 1] == 0) H = i;
		}
		//output()
		printf("#%d %d\n", tc, H - L);		
	}
}

#endif

//1209 .  [S/W 문제해결 기본] 2일차 - Sum //고심 끝에 안하기로 결정

//1210 .  [S/W 문제해결 기본] 2일차 - Ladder1 
#if 0
#pragma warning (disable:4996)
#include <stdio.h>
typedef struct st1
{
	int r; int c;
}ST1;

int a[102][102];
ST1 SP, EP;
int WP, RP;
ST1 Queue[102*102];
void InQueue(int rr, int cc) { Queue[WP].r = rr; Queue[WP++].c = cc; }
ST1 DeQueue(void) { return Queue[RP++]; }
int dr[] = { 0, 0, -1 };
int dc[] = { -1, 1, 0 };

int tc;

void input(void)
{
	scanf("%d", &tc);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			scanf("%d", &a[i][j]);
			if (a[i][j] == 2)
			{
				EP.r = i; 
				EP.c = j;
			}
		}
	}
}

ST1 BFS(int r, int c)
{
	int i, nr, nc;
	ST1 out;

	WP = 0;
	RP = 0;

	InQueue(r, c);
	//a[r][c] = 2;

	while (RP < WP)
	{
		out = DeQueue();
		for (i = 0; i < 3; i++)
		{
			nr = out.r + dr[i];
			nc = out.c + dc[i];
			if (nr < 0 || nc < 0 || nr >= 100 || nc >= 100) continue;
			if (a[nr][nc] == 1)
			{
				InQueue(nr, nc);
				a[nr][nc] = 2;
				break;
			}
		}
	}
	return Queue[WP-1];
}

int main(void)
{
	for (tc = 1; tc <= 10; tc++)
	{
		ST1 temp;

		input();
		temp = BFS(EP.r, EP.c);
		//output();
		printf("#%d %d\n", tc, temp.c);
	}
	return 0;
}

#endif

//1211 .  [S/W 문제해결 기본] 2일차 - Ladder2 //푸는중이었지만 안풀듯
#if 0
#pragma warning (disable:4996)
#include <stdio.h>
typedef struct st1
{
	int r; int c;
}ST1;

int a[102][102];
int v[102][102];
int SP[51];
int WP, RP;
ST1 Queue[102 * 102];
void InQueue(int rr, int cc) { Queue[WP].r = rr; Queue[WP++].c = cc; }
ST1 DeQueue(void) { return Queue[RP++]; }
int dr[] = { 0, 0, 1 };
int dc[] = { -1, 1, 0 };

int tc;
int sp_count;

void input(void)
{
	sp_count = 0;
	scanf("%d", &tc);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (a[0][i] == 1)
		{
			sp_count++;
			SP[sp_count] = i;
		}
	}
}

int BFS(int r, int c)
{
	int i, nr, nc;
	ST1 out;

	WP = 0;
	RP = 0;

	InQueue(r, c);
	//a[r][c] = 2;

	while (RP < WP)
	{
		out = DeQueue();
		for (i = 0; i < 3; i++)
		{
			nr = out.r + dr[i];
			nc = out.c + dc[i];
			if (nr < 0 || nc < 0 || nr >= 100 || nc >= 100) continue;
			if (a[nr][nc] == 1)
			{
				InQueue(nr, nc);
				a[nr][nc] = 2;
				break;
			}
		}
	}
	//return v[Q[wp - 1].r][wp - 1].c]; ////////////////////
}

int main(void)
{
	for (tc = 1; tc <= 10; tc++)
	{
		int temp;
		int min = 0x7fffffff;

		input();
		for (int i = 1; i <= sp_count; i++)
		{
			temp = BFS(); //////////////
		}		
		//output();
		printf("#%d %d\n", tc, temp.c);
	}
	return 0;
}

#endif
