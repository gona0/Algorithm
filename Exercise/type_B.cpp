//1240. [S/W 문제해결 응용] 1일차 - 단순 2진 암호코드 
#if 0
#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>

int T, tc;
int N, M;
char a[55][105];
int b[55];
int c[55];
char sp[105];
int key[2][2][2][2][2] = { -1, -1, -1, -1, -1, 9, 0, -1, -1, 2, -1, -1, 1, -1, -1, -1, \
							-1, 4, -1, -1, -1, -1, -1, 6, 5, -1, -1, 8, -1, 7, 3, -1};

int count;
int flag;
int code[10];
int ans;

int My_strcmp(const char * a, char *b) // a가 기준
{
	int i;

	for (i = 0; a[i] != 0; i++)
	{
		if (a[i] != b[i]) return 0;
	}
	return 1;
}

void My_strcpy(const char * a, char * b)
{
	int i;

	for (i = 0; a[i] != 0; i++)
	{
		b[i] = a[i];
	}
}

void vvv1(void)
{
	int i;

	for (i = 0; i < 10; i++)
	{
		printf("b, c = %d, %d\n", b[i], c[i]);
	}
}

void vvv2(void)
{
	int i;

	printf("code: ");
	for (i = 1; i <= 8; i++)
	{
		printf("%d ", code[i]);
	}
	printf("\n");
}

void init(void)
{
	count = 1;
	ans = 0;
	flag = 0;
}

void input(void)
{
	int i, j;
	int count_one;

	scanf("%d %d", &N, &M);

	for (i = 0; i < N; i++)
	{
		scanf("%s", a[i]);
		count_one = 0;
		for (j = 0; j < M; j++)
		{
			if (a[i][j] == '1')
			{
				count_one++;
				c[i] = j;
			}
		}
		b[i] = count_one;
	}
}

int decode(int I)
{
	int j, k;

	for (j = 0; j < c[I] - (7*8 - 1); j++)
	{
		if (sp[j] == 1) return 0;
	}

	for (k = 1; k <= 8; k++, j+=7)
	{
		code[k] = key[sp[j + 1] - '0'][sp[j + 2] - '0'][sp[j + 3] - '0'][sp[j + 4] - '0'][sp[j + 5] - '0'];
		//printf("code[%d] = key[%d][%d][%d][%d][%d] = %d\n", k, sp[j + 1], sp[j + 2], sp[j + 3], sp[j + 4], sp[j + 5], code[k]);
	}	
	return 1;
}

void verify(void)
{
	int i;
	int hub;
	int sum;

	hub = 0;
	sum = 0;
	for (i = 1; i <= 8; i++)
	{
		sum += code[i];
		if (i & 1) hub += 3 * code[i];
		else hub += code[i];
	}

	if (hub % 10 == 0) ans = sum;
	else ans = 0;
}

void process(void)
{
	int i;

	My_strcpy(a[0], sp);

	for (i = 1; i < N; i++)
	{
		if (b[i] < 24) continue;
		if (My_strcmp(sp, a[i]) == 1)
		{
			count++;
			if (count == 5)
			{
				if (decode(i))
				{
					verify();
				}
				else
				{
					i++;
					count = 1;
					My_strcpy(a[i], sp);
				}
			}
		}
		else
		{
			count = 1;
			My_strcpy(a[i], sp);
		}
	}
}

void output(void)
{
	printf("#%d %d\n", tc, ans);
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		//vvv1();
		process();
		//vvv2();
		output();
	}
}
#endif

//1242. [S/W 문제해결 응용] 1일차 - 암호코드 스캔 
#if 0
#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>

#define GARO	(500+10)
#define SERO	(2000+10)
int T, tc;
int N, M;
char a[SERO][GARO*4] = { 0 };
int b[SERO];
int c[SERO];
char sp[GARO * 4];

char key;
int count;
int flag;
int code[8 + 2];
int ratio[4 + 1];
char key_s[10][5] = { "3211", "2221", "2122", "1411", "1132", "1231", "1114", "1312", "1213", "3112" };
char ratio_s[4 + 1];
int flip;
int ans;

char number[16][5] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" };

void vvv1(void)
{
	int i;

	for (i = 0; i < N; i++)
	{
		printf("b, c = %d, %d\n", b[i], c[i]);
	}
}

void vvv2(void)
{
	int i;

	printf("code: ");
	for (i = 1; i <= 8; i++)
	{
		printf("%d ", code[i]);
	}
	printf("\n");
}

void vvv3(void)
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < 4 * M; j++)
		{
			printf("%c", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int My_gcd(int a, int b)
{
	if (b == 0) return a;
	else		return My_gcd(b, a%b);
}

int My_strcmp(const char * a, char *b) // a가 기준
{
	int i;

	for (i = 0; a[i] != 0; i++)
	{
		if (a[i] != b[i]) return 0;
	}
	return 1;
}

void My_strcpy(const char * a, char * b)
{
	int i;

	for (i = 0; a[i] != 0; i++)
	{
		b[i] = a[i];
	}
}

void init(void)
{
	count = 1;
	ans = 0;
	flag = 0;
}

char * make_a_way(char A)
{
	if ('A' <= A && A <= 'F') return number[A - 'A' + 10];
	else return number[A - '0'];
}

void input(void)
{
	int i, j;
	int count_one;
	char temp[GARO];

	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++)
	{
		scanf("%s", temp);
		//temp 16->2 쪼개서 a[i]에 넣기
		for (j = 0; j < M; j++)
		{
			My_strcpy(make_a_way(temp[j]), a[i] + 4 * j);
		}
		
		count_one = 0;
		for (j = 0; j < 4*M; j++)
		{		
			if (a[i][j] == '1')
			{
				count_one++;
				c[i] = j;
			}
		}
		b[i] = count_one;
	}
}

int decode(int I)
{
	int j, k;
	int num;
	int divisor;

	//ratio[] 초기화
	for (j = 1; j <= 4; j++)
	{
		ratio[j] = 1;
	}

	num = 8;
	for (j = c[I]; j > c[I] - (7 * 8); j -= 7)
	{
		//k, flip 사용해서 ratio[]를 채우기
		flip = 1;
		key = sp[j];
		for (k = 1; k <= 6; k++)
		{			
			if (key == sp[j - k])
			{
				ratio[5 - flip]++;
			}
			else
			{
				flip++;
				key = sp[j - k];
			}
			if (flip == 5)
			{
				printf("나가니? key = %c\n", key);
				return 0;
			}
		}
		//ratio조정
		divisor = My_gcd(ratio[1], My_gcd(ratio[2], My_gcd(ratio[3], ratio[4])));
		printf("짝맞춰봅니다\n");
		for (k = 1; k <= 4; k++)
		{
			ratio_s[k-1] = char(ratio[k]/divisor) + '0'; 
			printf("%c\n", ratio_s[k - 1]);
		}
		
		//ratio를 보고 code에 넣기	
		for (k = 0; k <= 9; k++)
		{
			if (My_strcmp(key_s[k], ratio_s))
			{
				code[num] = k;
				break;
			}
		}
		num--;
	}
	return 1;
}

void verify(void)
{
	int i;
	int hub;
	int sum;

	hub = 0;
	sum = 0;
	for (i = 1; i <= 8; i++)
	{
		sum += code[i];
		if (i & 1) hub += 3 * code[i];
		else hub += code[i];
	}

	if (hub % 10 == 0) ans = sum;
	else ans = 0;
}

void process(void)
{
	int i;

	My_strcpy(a[0], sp);

	printf("sp 체크중\n");
	for (i = 0; sp[i] != 0; i++)
	{
		printf("%c", sp[i]);
	}
	printf("\n");

	for (i = 1; i < N; i++)
	{
		if (b[i] == 0) continue;
		if (My_strcmp(sp, a[i]) == 1)
		{
			count++;
			if (count == 5)
			{
				if (decode(i))
				{
					verify();
				}
				else
				{
					i++;
					count = 1;
					My_strcpy(a[i], sp);
				}
			}
		}
		else
		{
			count = 1;
			My_strcpy(a[i], sp);
		}
	}
}

void output(void)
{
	printf("#%d %d\n", tc, ans);
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		process();
		vvv2();
		output();
	}
}
#endif

//SelectionSort Recursive하게
#if 0
#include <stdio.h>

void SelectionSort(int A[], int n)
{
	int i, j, min, temp;

	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (A[j] < A[min]) min = j;
		}
		temp = A[min];
		A[min] = A[i];
		A[i] = temp;
	}
}

void SelectionSortRecursive(int A[], int n)
{
	int i, j, min, temp;


}

int main(void)
{
	return 0;
}

#endif

//p51 Baby-gin
#if 0
#include <stdio.h>
#pragma warning (disable:4996)

int T, tc;
int a[7];
int num[10];
int trip;
int run;
int ans;

void init(void)
{
	int i;

	trip = 0;
	run = 0;
	for (i = 0; i < 10; i++)
	{
		num[i] = 0;
	}
}

void input(void)
{
	int i;

	for (i = 1; i <= 6; i++)
	{
		scanf("%1d", &a[i]);
		num[a[i]]++;
	}
}

void process(void)
{
	int i;

	//triplete개수 세기
	for (i = 0; i < 10; i++)
	{		
		if (num[i] >= 3)
		{
			trip++;
			num[i] -= 3;
		}
	}

	////2 triplete
	//if (trip == 2)
	//{
	//	ans = 1;
	//	return;
	//}
	////1 triplete
	//else if (trip == 1)
	//{		
	//	
	//}
	////no triplete
	//else
	//{
	//}

	for (i = 0; i < 10; i++)
	{
		if (num[i] >= 1 && num[i + 1] >= 1 && num[i + 2] >= 1)
		{
			run++;
			num[i]--;
			num[i + 1]--;
			num[i + 2]--;
		}
	}

	if (trip + run == 2) ans = 1;
	else ans = 0;
}

void output(void)
{
	printf("#%d %d\n", tc, ans);
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		input();
		process();
		output();
	}

	return 0;
}


#endif

//1244. [S/W 문제해결 응용] 2일차 - 최대 상금 
#if 0
#pragma warning (disable: 4996)
#include <stdio.h>

typedef struct _st
{
	int num;
	int order;
}ST;

#define MAX	(6+6)
#define SWAP(x,y) { ST temp; temp = x; x = y; y = temp; }
int T, tc;
char num_s[MAX];
ST a[MAX];
int count[MAX];
int count_flag;
int digit = MAX;
int N;
int ans;

void print_num(void)
{
	int i;

	printf("num:	");
	for (i = 1; i <= digit; i++)
	{
		printf("%d", a[i].num);
	}
	printf("\n");
}

void print_order(void)
{
	int i;

	printf("order:	");
	for (i = 1; i <= digit; i++)
	{
		printf("%d", a[i].order);
	}
	printf("\n");
}

void print_count(void)
{
	int i;

	printf("count:	");
	for (i = 0; i <= 9; i++)
	{
		printf("%d", count[i]);
	}
	printf("\n");
}

int sum_array(void)
{
	int i;
	int S;

	S = a[1].num;
	for (i = 2; i <= digit; i++)
	{
		S *= 10;
		S += a[i].num;
	}
	return S;
}

void init(void)
{
	int i;

	ans = 0;
	count_flag = 0;
	for (i = 1; i <= digit; i++)
	{
		a[i].order = 1;
	}
	for (i = 0; i <= 9; i++)
	{
		count[i] = 0;
	}
}

void input(void)
{
	int i, j;

	//값 받기
	scanf("%s", &num_s[1]);
	for (i = 1; num_s[i] != 0; i++)
	{
		a[i].num = num_s[i] - '0';
		count[a[i].num]++;
	}
	digit = i - 1;

	//count_flag설정
	for (i = 0; i <= 9; i++)
	{
		if (count[i] > 1)
		{
			count_flag = 1;
			break;
		}
	}

	//order정하기
	for (i = 1; i <= digit; i++)
	{
		for (j = 1; j <= i; j++)
		{
			if (a[i].num < a[j].num)
			{
				a[i].order++;
			}
			else if (a[i].num > a[j].num)
			{
				a[j].order++;
			}
		}
	}

	//times 조절
	scanf("%d", &N);
	if (N > digit)
	{
		if ((digit + N) & 1) N = digit - 1;
		else N = digit; //둘다 홀인경우 or 짝인경우
	}
}

void DFS(int L, int C, int S)
{
	int i, j;
	int flag = 0;

	//printf("DFS(%d,%d,%d)\n", L, C, S);
	//print_num();
	//print_order();
	//printf("\n");


	if (C >= N)
	{
		if (S > ans) ans = S;
		return;
	}
	if (L >= digit)
	{
		if (C < N)
		{
			//N-C 값 비교해서 짝 홀/ 같은거 있으면 리턴 없으면 (N-C)&1
			if (count_flag == 1)
			{
				if (S > ans) ans = S;
			}
			else
			{
				if ((N - C) & 1) // N-C가 홀수면
				{
					if (ans < S - 9 * a[digit - 1].num + 9 * a[digit].num) ans = S - 9 * a[digit - 1].num + 9 * a[digit].num;
				}
				else
				{
					if (S > ans) ans = S;
				}
			}			
		}
		return;
	}

	//L번째 자리에서 order가 L인 것만 움직인다.
	if (a[L].order == L)
	{
		if (count[a[L].num] > 1)
		{
			flag = 1;
			count[a[L].num]--;
			for (i = L + 1; i <= digit; i++)
			{
				if (a[i].order == L) a[i].order++;
			}
		}
		DFS(L + 1, C, sum_array());
		if (flag == 1)
		{
			flag = 0;
			count[a[L].num]++;
			for (i = L + 1; i <= digit; i++)
			{
				if (a[i].order == L + 1) a[i].order--;
			}
		}
	}
	else
	{
		for (i = L + 1; i <= digit; i++)
		{
			if (a[i].order == L)
			{
				//바꾸고 같은 L이 있으면 order내에서 더해주고...
				if (count[a[i].num] > 1)
				{
					flag = 1;
					count[a[i].num]--;
					for (j = L + 1; j <= digit; j++)
					{
						if (j == i) continue;
						if (a[j].order == L) a[j].order++;
					}
				}
				SWAP(a[L], a[i]);
				DFS(L + 1, C + 1, sum_array());
				if (flag == 1)
				{
					flag = 0;
					count[a[L].num]++;
					for (j = L + 1; j <= digit; j++)
					{
						if (j == i) continue;
						if (a[j].order == L + 1) a[j].order--;
					}
				}
				SWAP(a[L], a[i]);
			}
		}
	}
}

void output(void)
{
	printf("#%d %d\n", tc, ans);
	//print_num();
	//print_order();
	//print_count();
	//printf("times:	%d\n", N);
	//printf("c_flag:	%d\n\n", count_flag);
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		DFS(1, 0, 0);
		output();
	}
	return 0;
}

#endif

//장현이네반 선생님
#if 0
#include <stdio.h>

#define SWAP(x, y) { int temp = x; x = y; y = temp;}
char data[100];
int len;
int rearIdx[100];
int frontIdx[100];

int my_strLen(char* str) {
	len = 0;
	while (*str++) {
		len++;
	}
	return len;
}

int isFinish() {
	for (int i = 0; i < len - 1; i++) {
		if (data[i] < data[i + 1])
			return 0;
	}
	return 1;
}

void changeFinishArray() {
	for (int i = 0; i < len - 1; i++) {
		if (data[i] == data[i + 1])
			return;
	}
	SWAP(data[len - 1], data[len - 2]);
}

int main() {
	freopen("input.txt", "r", stdin);
	int tc;
	int flag;
	int idx;
	char max;
	int startIdx;
	int switchCnt;
	int cnt;

	scanf("%d", &tc);
	for (int testCase = 1; testCase <= tc; testCase++) {
		startIdx = 0;
		cnt = 0;
		scanf("%s %d", data, &switchCnt);
		len = my_strLen(data);

		while (switchCnt) {
			if (isFinish()) {
				if (switchCnt & 1) {
					changeFinishArray();
				}
				break;
			}
			int i;
			for (i = startIdx; i < len; i++) {
				flag = 0;
				idx = 0;
				max = data[i];
				for (int j = i + 1; j < len; j++) {
					if (max < data[j]) {
						max = data[j];
						idx = j;
						flag = 1;

					}
					else if (max == data[j] && flag) {
						idx = j;
					}
				}

				if (flag) {
					SWAP(data[i], data[idx]);
					rearIdx[cnt] = idx;
					frontIdx[cnt] = i;
					cnt++;
					if (cnt > 1) {
						for (int k = cnt - 1; k; k--) {
							if (data[frontIdx[k]] == data[frontIdx[k - 1]] &&
								data[rearIdx[k]] < data[rearIdx[k - 1]]) {
								SWAP(data[rearIdx[k]], data[rearIdx[k - 1]]);
							}
						}
					}
					break;
				}
			}
			startIdx = i + 1;
			switchCnt--;
		}

		printf("#%d %s\n", testCase, data);
	}
	return 0;
}
#endif

//1245. [S/W 문제해결 응용] 2일차 - 균형점 
#if 0
#include <stdio.h>
#pragma warning(disable:4996)

typedef struct _st
{
	double x;
	double m;
}ST;

#define MAX	(10+4)
int T, tc;
int N;


double ans;

void input(void)
{

}

void process(void)
{

}

void output(void)
{
	printf("#%d %f", tc, ans);
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		input();
		process();
		output();
	}
	return 0;
}

#endif

//1247. [S/W 문제해결 응용] 3일차 - 최적 경로  

//나의 허접한 DFS
#if 0
#pragma warning(disable : 4996)
#include <stdio.h>

typedef struct _st
{
	int x; int y;
}ST;

#define MAX	(10+5)
#define ABS(x)	((x)>0?(x):-(x))
int T, tc;
int N;

ST sp, ep, a[MAX];
int d[MAX][MAX];
int p[MAX];
int v[MAX];

int min;

void init(void)
{
	min = 0x7fffffff;
}

void input(void)
{
	int i, j;
	scanf("%d", &N);
	
	scanf("%d %d", &sp.x, &sp.y);
	scanf("%d %d", &ep.x, &ep.y);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &a[i].x, &a[i].y);
	}

	//distance setting
	for (i = 1; i <= N; i++)
	{
		d[0][i] = ABS(a[i].x - sp.x) + ABS(a[i].y - sp.y);
		d[i][N + 1] = ABS(ep.x - a[i].x) + ABS(ep.y - a[i].y);
	}
	for (i = 2; i <= N; i++)
	{
		for (j = 1; j < i; j++)
		{
			d[i][j] = ABS(a[i].x - a[j].x) + ABS(a[i].y - a[j].y);
			d[j][i] = d[i][j];
		}
	}

	p[0] = 0;
	p[N + 1] = N + 1;
}

int sum_distance(int * p)
{
	int i;
	int sum;

	sum = 0;
	for (i = 0; i <= N; i++)
	{
		sum += d[p[i]][p[i + 1]];
	}

	return sum;
}

void DFS(int L)
{
	int i;

	if (L > N)
	{
		int hub;
		hub = sum_distance(p);
		if (hub < min) min = hub;
		return;
	}

	for (i = 1; i <= N; i++)
	{
		if (v[i] == 0)
		{
			v[i] = 1;
			p[L] = i;
			DFS(L + 1);
			v[i] = 0;
		}
	}	
}

void output(void)
{
	printf("#%d %d\n", tc, min);
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		DFS(1);
		output();
	}
	return 0;
}



#endif

//youu의 dp
#if 0
#pragma warning(disable:4996)
#include <stdio.h>

typedef struct _st
{
	int x; int y;
}ST;

#define MAX (10+5)
#define INF (0x7fffffff)
#define MIN(x,y)	((x)>(y)?(y):(x))
#define ABS(x)		((x)>0?(x):-(x))
int T, tc;
int N;

ST a[MAX];
int y[MAX], x[MAX];
int dist[MAX][MAX];
int cache[MAX][(1 << 12) + 2];

void init()
{
	int i, j;

	scanf("%d", &N);
	for (i = 0; i <= N + 2; i++)
	{
		for (j = 0; j <= (1 << 12) + 1; j++)
		{
			cache[i][j] = -1;
		}
	}
}

void input(void)
{
	int i, j;

	//scanf("%d", &N);
	scanf("%d %d", &a[0].x, &a[0].y);		//회사
	scanf("%d %d", &a[N+1].x, &a[N+1].y);	//집
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &a[i].x, &a[i].y);
	}

	for (i = 1; i <= N + 1; i++)
	{
		for (j = 0; j < i; j++)
		{
			dist[i][j] = ABS(a[i].x - a[j].x) + ABS(a[i].y - a[j].y);
			dist[j][i] = dist[i][j];
		}
	}
}

//성열이랑 같이 봐보자
int DP(int st, int visited)
{
	int i;

	if (visited == (1 << N + 1) - 1)
	{
		return dist[st][N + 1];
	}

	int &ret = cache[st][visited];
	if (ret != -1) return ret;
	ret = INF;

	for (i = 1; i <= N; i++)
	{
		if (i == st) continue;
		if ((visited & (1 << i)) == 0)
		{
			ret = MIN(ret, DP(i, visited | (1 << i)) + dist[st][i]);
		}
	}
	return ret;
}

void output(void)
{
	printf("#%d %d\n", tc, DP(0, 1 << 0));
}

int main()
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();		
		output();
	}
	return 0;
}
#endif

//1249 .[S / W 문제해결 응용] 4일차 - 보급로

//나의 BFS
#if 0
#pragma warning(disable : 4996)
#include <stdio.h>

typedef struct st_
{
	int r; int c;
}ST;

#define INF	(0x7fffffff)
#define MAX	(100+5)
int T, tc;
int N;
int a[MAX][MAX];
int time[MAX][MAX];
ST Queue[MAX*MAX*MAX];
int WP, RP;
int min_time;

void InQueue(int rr, int cc){ Queue[WP].r = rr; Queue[WP++].c = cc; }
ST DeQueue(void) { return Queue[RP++]; }
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

///////////////코드
void init(void)
{
	int i, j;

	scanf("%d", &N);

	min_time = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			time[i][j] = INF;
		}
	}
}

void input(void)
{
	int i, j;

	//scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			scanf("%1d", &a[i][j]);
		}
	}
}

void BFS(int r, int c)
{
	int i, nr, nc;
	ST out;

	WP = 0;
	RP = 0;

	InQueue(r, c);
	time[r][c] = 0;

	while (RP < WP)
	{
		out = DeQueue();
		for (i = 0; i < 4; i++)
		{
			nr = out.r + dr[i];
			nc = out.c + dc[i];
			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
			if (time[nr][nc] > time[out.r][out.c] + a[nr][nc])
			{
				InQueue(nr, nc);
				time[nr][nc] = time[out.r][out.c] + a[nr][nc];
			}
		}
	}
}

void output(void)
{
	printf("#%d %d\n", tc, time[N - 1][N - 1]);
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		BFS(0,0);
		output();
	}
}

#endif

//youu의 djikstra
#if 0
#include<stdio.h>
#define INF 987654321
int test;
int N;
int map[110][110];
int dist[110][110];
struct Q
{
	int y, x, cost;
};
Q q[110 * 110 * 4];
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };
int e;
void init()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			dist[i][j] = INF;
		}
	}
}
void up(int i)
{
	Q temp;
	if (i > 1)
	{
		if (q[i / 2].cost > q[i].cost)
		{
			temp = q[i / 2];
			q[i / 2] = q[i];
			q[i] = temp;
			up(i / 2);
		}
	}
}
void down(int i)
{
	Q temp;
	int largest = i;
	int left = 2 * i; int right = 2 * i + 1;
	if (left <= e && q[largest].cost > q[left].cost)largest = left;
	if (right <= e && q[largest].cost > q[right].cost)largest = right;
	if (largest != i)
	{
		temp = q[largest];
		q[largest] = q[i];
		q[i] = temp;
		down(largest);
	}
}

int dikstra()
{
	Q temp;
	e = 0;
	q[++e].y = 1; q[e].x = 1; q[e].cost = map[1][1]; dist[1][1] = q[e].cost;
	while (e >= 1)
	{
		temp = q[1];
		q[1] = q[e];
		e--;
		down(1);
		if (temp.y == N && temp.x == N)return temp.cost;
		for (int i = 0; i < 4; i++)
		{
			int ty = temp.y + dy[i];
			int tx = temp.x + dx[i];
			if (ty<1 || ty>N || tx<1 || tx>N)continue;
			if (dist[ty][tx] > temp.cost + map[ty][tx])
			{
				q[++e].y = ty;
				q[e].x = tx;
				q[e].cost = temp.cost + map[ty][tx];
				dist[ty][tx] = q[e].cost;
				up(e);
			}
		}
	}
	return -1;
}
int main()
{
	scanf("%d", &test);
	for (int T = 1; T <= test; T++)
	{
		scanf("%d", &N);
		init();
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				scanf("%1d", &map[i][j]);
			}
		}
		printf("#%d %d\n", T, dikstra());
	}
	return 0;
}

#endif

//1251 .[S / W 문제해결 응용] 4일차 - 하나로

//실패 KRUSKAL
#if 0
#pragma warning(disable : 4996)
#include <stdio.h>
typedef long long ll;
typedef struct st1
{
	ll x; 
	ll y;
}ST1;
typedef struct st2
{
	ll val;
	int p1;
	int p2;
}ST2;

#define MAX	(1000+5)
#define D_SQR(a,b)	((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))
#define SWAP(A,B)	{ST2 temp; temp = A; A=B; B=temp;};
int T, tc;
int N;		//1~1000
ST1 island[MAX];
ST2 L_sqr[MAX][MAX];
ST2 L_list[MAX*MAX];
int visit[MAX];
double E;

////////////////////////
//1. 일단 배열로 풀고 시간체크
//2. linked list로 풀자 - 입력받으면서 정렬
void vvv(void)
{
	int i;

	for (i = 1; i <= N*(N-1)/2; i++)
	{
		printf("%lld %d %d\n", L_list[i].val, L_list[i].p1, L_list[i].p2);
	}
	printf("==================\n");
}
void vvv_visit(void)
{
	int i;

	printf("visit: ");
	for (i = 1; i <= N; i++)
	{
		printf("%d ", visit[i]);
	}
	printf("\n");
	printf("==================\n");
}

void init(void)
{
	int i;

	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		visit[i] = 0;
	}
}

void input(void)
{
	int i, j;
	int index;

	//scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &island[i].x);
	}
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &island[i].y);
	}
	
	index = 1;
	for (i = 2; i <= N; i++)
	{
		for (j = 1; j < i; j++)
		{
			L_list[index].val = D_SQR(island[i],island[j]);
			L_list[index].p1 = i;
			L_list[index++].p2 = j;
		}
	}
	scanf("%lf", &E);
}

void sort(void)
{
	int i, j;
	ST2 temp;

	for (i = 2; i <= N*(N-1)/2; i++)
	{
		for (j = 1; j < i; j++)
		{
			if (L_list[i].val < L_list[j].val)
			{
				temp = L_list[i];
				L_list[i] = L_list[j];
				L_list[j] = temp;
			}
		}
	}
}

ll MST_KRUSKAL(void)
{
	int i, k;
	int count;
	ll sum;

	i = 1;
	sum = 0;
	count = 0;
	while (count != N-1)
	{
		if (visit[L_list[i].p1] == 0 && visit[L_list[i].p2] == 0)
		{
			visit[L_list[i].p1] = L_list[i].p1;
			visit[L_list[i].p2] = L_list[i].p1;
			sum += L_list[i].val;
			count++;		
		}
		else if (visit[L_list[i].p1] == 0 || visit[L_list[i].p2] == 0)
		{
			if (visit[L_list[i].p1]) visit[L_list[i].p2] = visit[L_list[i].p1];
			else visit[L_list[i].p1] = visit[L_list[i].p2];
			sum += L_list[i].val;
			count++;
		}	
		//둘다 T인 경우
		else if (visit[L_list[i].p1] != visit[L_list[i].p2])
		{
			for (k = 1; k <= N; k++)
			{
				if (visit[k] == visit[L_list[i].p2]) visit[k] = visit[L_list[i].p1];
			}
			sum += L_list[i].val;
			count++;
		}
		i++;
	}
	return sum;
}

void output(void)
{
	printf("#%d %.0f\n", tc, E*MST_KRUSKAL());
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		sort();
		//MST_KRUSKAL();
		output();
	}
	return 0;
}

#endif

//youu의 prim 3000ms
#if 0
#include<stdio.h>
#define INF 987654321
int test;
int N;
int y[1010];
int x[1010];
double tax;
double ans;
double cost[1010][1010];
int chk[1010];
int sel[1010];//포함 idx저장
double calculate(int y1, int y2, int x1, int x2)
{
	double ty; double tx;
	ty = (double)y1 - (double)y2; tx = (double)x1 - (double)x2;
	return (double)(ty*ty + tx*tx)*(double)tax;
}
void init()
{
	for (int i = 1; i <= N; i++)
	{
		chk[i] = 0;
		sel[i] = 0;
		for (int j = 1 + 1; j <= N; j++)
		{
			double temp = calculate(y[i], y[j], x[i], x[j]);
			cost[i][j] = temp;
			cost[j][i] = temp;
		}
	}
}
void prim()
{
	int sel_cnt = 0;
	sel[++sel_cnt] = 1;
	chk[1] = 1;
	while (1)
	{
		int min_idx = 0;
		int is_first = 1;

		double min_sum = INF;
		if (sel_cnt >= N)break;//
		for (int i = 1; i <= sel_cnt; i++)//idx
		{
			int idx = sel[i];
			for (int j = 1; j <= N; j++)
			{
				if (idx == j)continue;
				if (chk[j] == 1)continue;
				double temp_cost = cost[idx][j];
				if (is_first == 1 || min_sum > temp_cost)
				{
					is_first = 0;
					min_sum = temp_cost;
					min_idx = j;
				}
			}
		}
		sel[++sel_cnt] = min_idx;
		ans += min_sum;
		chk[min_idx] = 1;
	}
}
int main()
{
	scanf("%d", &test);
	for (int T = 1; T <= test; T++)
	{
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &x[i]);
		}
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &y[i]);
		}
		scanf("%lf", &tax);
		ans = 0;
		init();
		prim();
		printf("#%d %lld\n", T, (long long int)(ans + 0.5));

	}
	return 0;
}
#endif

//bloodstraberry의 장현 장현 heap 80ms 
#if 0
#include <stdio.h>

int T, N, M;
long long int DIST[1010][1010];

int check[1010];

double E;

typedef struct st
{
	long long int r;
	long long int c;
}RCStruct;

RCStruct RC[1010];

long long int distance(RCStruct a, RCStruct b)
{
	return (a.r - b.r) * (a.r - b.r) + (a.c - b.c) * (a.c - b.c);
}

void input()
{
	int i, k;

	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%lld", &RC[i].r);

	for (i = 1; i <= N; i++) scanf("%lld", &RC[i].c);

	scanf("%lf", &E);

}

void output()
{
	int i, k;

	printf("N : %d E : %lf\n", N, E);

	for (i = 1; i <= N; i++)
		printf("%lld %lld\n", RC[i].r, RC[i].c);
}

void init()
{
	int i, k;
	for (i = 1; i <= N; i++)
	{
		for (k = i + 1; k <= N; k++)
			DIST[i][k] = DIST[k][i] = distance(RC[i], RC[k]);
	}


	for (i = 1; i <= N; i++) check[i] = 0;
}

typedef struct st2
{
	int value;
	long long int prt;
}HEAP;

HEAP heap[1010 * 1010];
int hn;



HEAP pop()
{
	int i;

	HEAP ans, tmp;
	ans = heap[1];
	heap[1] = heap[hn];
	heap[hn].value = 0;
	heap[hn--].prt = 0x7fff000000000000;

	for (i = 1; i * 2 <= hn;)
	{
		if (heap[i].prt < heap[i * 2].prt && heap[i].prt < heap[i * 2 + 1].prt) break;
		else if (heap[i * 2].prt < heap[i * 2 + 1].prt)
		{
			tmp = heap[i];
			heap[i] = heap[i * 2];
			heap[i * 2] = tmp;

			i = i * 2;
		}
		else
		{
			tmp = heap[i];
			heap[i] = heap[i * 2 + 1];
			heap[i * 2 + 1] = tmp;

			i = i * 2 + 1;
		}
	}

	return ans;
}

void push(HEAP x)
{
	int i;
	HEAP tmp;
	heap[++hn] = x;

	for (i = hn; i > 1; i /= 2)
	{
		if (heap[i].prt > heap[i / 2].prt) break;

		tmp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = tmp;
	}

}


int main()
{
	int tc, i, k, node;
	HEAP tmp;
	long long int ANS;

	/*push({ 1, 10 });
	push({ 5, 104564554 });
	push({ 4, 10 });
	push({ 3, 16 });
	push({ 2, 10 });
	push({ 5, 12 });
	push({ 7, 1 });
	push({ 9, 1 });
	push({ 15, 150 });
	push({ 19, 1 });
	push({ 9, 120 });
	push({ 159, 1015 });
	push({ 39, 10111666 });
	push({ 9, 101564 });


	while (hn)
	{
	HEAP t = pop();
	printf("%d %d\n", t.value, t.prt);
	}

	putchar('\n');*/

	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{

		hn = 0;
		input();

		//output();

		init();

		ANS = 0;
		/*  for (i = 1; i <= N; i++)
		{
		for (k = 1; k <= N; k++)
		printf("%lld ", DIST[i][k]);
		putchar('\n');
		}*/

		node = 1;
		for (i = 1; i <= N; i++)
			if (i != node) push({ i, DIST[node][i] });

		check[node] = 1;
		for (i = 1; i <= N - 1; i++)
		{
			int cnt = 0;
			//printf("%d\n", node);
			while (1)
			{
				tmp = pop();
				if (tmp.value != node && !check[tmp.value])
				{
					node = tmp.value;
					ANS += tmp.prt;
					check[node] = 1;


					for (k = 1; k <= N; k++)
					{
						if (check[k] == 0 && node != k) push({ k, DIST[node][k] });
					}

					break;
				}
			}



		}

		printf("#%d %.0lf\n", tc, (double)ANS * E);

	}


	return 0;
}

#endif

//henry1214의 현철 KRUSKAL 600ms
#if 0
#include <cstdio>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;

struct Edge
{
	ll start, end, cost;
	bool operator < (const Edge &other) const { return cost<other.cost; }
};

ll t, n, m, ans, p[1001], x[1001], y[1001];
double E;

ll Find(ll x) 
{ 
	return x == p[x] ? x : p[x] = Find(p[x]); 
}

void Union(ll x, ll y) 
{ 
	p[Find(x)] = Find(y); 
}

ll dist(ll x1, ll y1, ll x2, ll y2)
{
	ll a = abs(x1 - x2), b = abs(y1 - y2);
	return a*a + b*b;
}

int main()
{
	scanf("%lld", &t);
	for (ll k = 1; k <= t; k++)
	{
		//init()
		for (ll i = 1; i <= n; i++) p[i] = i;

		//input()
		scanf("%lld", &n);
		for (ll i = 1; i <= n; i++) scanf("%lld", &x[i]);
		for (ll i = 1; i <= n; i++) scanf("%lld", &y[i]);
		scanf("%lf", &E);

		vector<Edge> a;
		for (ll i = 1; i <= n; i++) for (ll j = i + 1; j <= n; j++)
			a.push_back({ i, j, dist(x[i], y[i], x[j], y[j]) });

		//sort()
		sort(a.begin(), a.end());

		//KRUSKAL
		m = a.size(), ans = 0;
		for (ll i = 0; i<m; i++)
		{
			Edge e = a[i];
			ll x = Find(e.start), y = Find(e.end);
			if (x != y) Union(e.start, e.end), ans += e.cost;
		}

		//output()
		printf("#%lld %.0f\n", k, ans*E);
	}
	return 0;
}

#endif

//재도전 KRUSKAL 성공 740ms // prim이랑 heap쓴 애들은 20~80나옴
#if 0
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
typedef struct st1
{
	ll x; ll y;
}ST1;
typedef struct st2
{
	ll val; int p1; int p2;
}ST2;

#define MAX	(1000+5)
#define D_SQR(a,b)	((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))
//#define SWAP(A,B)	{ST2 temp; temp = A; A=B; B=temp;};
int T, tc;
int N;		//1~1000
int p[MAX];
ST1 obj[MAX]; 
ST2 L_list[MAX*(MAX-1)/2];
double E;

int Find(int x) { return x == p[x] ? x : Find(p[x]); }
void Union(int x, int y) { p[Find(x)] = Find(y); }

void vvv(void)
{
	int i;

	for (i = 1; i <= N*(N - 1) / 2; i++)
	{
		printf("%lld %d %d\n", L_list[i].val, L_list[i].p1, L_list[i].p2);
	}
	printf("==================\n");
}
void init(void)
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) { p[i] = i; }
}

void input(void)
{
	int index;

	for (int i = 1; i <= N; i++) { scanf("%d", &obj[i].x); }
	for (int i = 1; i <= N; i++) { scanf("%d", &obj[i].y); }

	index = 1;
	for (int i = 2; i <= N; i++)
	{
		for (int j = 1; j < i; j++)
		{
			L_list[index].val = D_SQR(obj[i], obj[j]);
			L_list[index].p1 = i;
			L_list[index++].p2 = j;
		}
	}
	scanf("%lf", &E);
}

void sort(void)
{
	ST2 temp;

	for (int i = 2; i <= N*(N - 1) / 2; i++) 
	{
		for (int j = 1; j < i; j++)
		{
			if (L_list[i].val < L_list[j].val)
			{
				temp = L_list[i];
				L_list[i] = L_list[j];
				L_list[j] = temp;
			}
		}
	}
}

ll MST_KRUSKAL(void)
{
	int count;
	ll sum;

	count = 0;
	sum = 0;
	for (int i = 1; i <= N*(N - 1) / 2; i++)
	{
		if (Find(L_list[i].p1) != Find(L_list[i].p2))
		{
			Union(L_list[i].p1, L_list[i].p2);
			sum += L_list[i].val;
		}
	}
	return sum;
}

void output(void)
{
	printf("#%d %.0f\n", tc, E*MST_KRUSKAL());
}

int compare(const void *arg1, const void *arg2)
{
	if (((ST2 *)arg1)->val > ((ST2 *)arg2)->val) return 1;
	else if (((ST2 *)arg1)->val == ((ST2 *)arg2)->val) return 0;
	else return -1;
}

int main(void)
{
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		input();
		//sort();
		qsort(&L_list[1], N*(N - 1) / 2, sizeof(ST2), compare);
		//vvv();
		//MST_KRUSKAL();
		output();
	}
	return 0;
}

#endif

//1256 .  [S/W 문제해결 응용] 6일차 - K번째 접미어 
#if 0
#pragma warning(disable:4996)
#include <iostream>
#include <cstring>
#include <stdlib.h>

#define MAX_L	(400+2)
int T, Tc;
int K;
char Str[MAX_L];
int Len;
char p[MAX_L][MAX_L];

int compare(const void * a, const void * b)
{
	for (register int i = 0; ((char *)a)[i] != 0; ++i){
		if (((char *)a)[i] == ((char *)b)[i]) continue;
		else return ((char *)a)[i] - ((char *)b)[i];
	}
	return 0;
}

void input(void){
	scanf("%d", &K);
	scanf("%s", Str);
	Len = strlen(Str);
}

void make_array(void){
	for (register int i = 0; i < Len; ++i){
		strcpy(p[i], &Str[i]);
		//printf("%s\n", p[i]);
	}
}

void output(void){
	
	//printf("(K,Len)=(%d,%d)\n", K, Len);
	if (K>Len) printf("#%d %s\n", Tc, "none");
	else printf("#%d %s\n", Tc, p[K-1]);
}

int main(void)
{
	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		input();
		make_array();
		qsort(p, Len, sizeof(char[MAX_L]), compare);
		//for (register int i = 0; i < Len; ++i){			
		//	printf("%s\n", p[i]);
		//}

		output();
	}	
}

#endif

//1257 .  [S/W 문제해결 응용] 6일차 - K번째 문자열					///아직못푸무ㅜㅜ
#if 0
#pragma warning(disable:4996)
#include <iostream>
#include <cstring>
#include <stdlib.h>

#define MAX_L	(400+2)
int T, Tc;
int K;
char Str[MAX_L];
int Len;
char A[MAX_L][MAX_L];

int compare(char * a, char * b)
{
	for (register int i = 0; ((char *)a)[i] != 0; ++i){
		if (((char *)a)[i] == ((char *)b)[i]) continue;
		else return ((char *)a)[i] - ((char *)b)[i];
	}
	return 0;
}

//int Partition(int p, int r){
//	int j = p - 1;
//	char temp[MAX_L];
//    for (int i = p; i < r; i++){
//        if (compare(A[i], A[r]) > 0){
//            j++;
//			strcpy(temp, A[i]);
//			strcpy(A[i], A[j]);
//			strcpy(A[j], temp);
//        }
//    }
//    j++;
//	strcpy(temp, A[r]);
//	strcpy(A[r], A[j]);
//	strcpy(A[j], temp);
//    return j;
//}
// 
//void QuickSort(int p, int r){
//    if (p < r){
//        int q = Partition(p, r);
//        QuickSort(p, q - 1);
//        QuickSort(q + 1, r);
//    }
//}

void input(void){
	scanf("%d", &K);
	scanf("%s", Str);
	Len = strlen(Str);
}

void make_array(void){
	for (register int i = 0; i < Len; ++i){
		strcpy(A[i], &Str[i]);
	}
}

void output(void){
	int count;
	
	if (K>Len) printf("#%d %s\n", Tc, "none");
	else {
		count = 0;
		for (register int i = 0; i < Len; ++i){
			if (A[i][0] != 0) ++count;
			if (count == K) {
				K = i;
				break;
			}
		}
		printf("#%d %s\n", Tc, A[K]);
	}
}

int main(void)
{
	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		input();
		make_array();
		SelectionSort();
		output();
	}
}

#endif

//1259 .  [S/W 문제해결 응용] 7일차 - 금속막대 

//문제/알고리즘 분류/그래프/연결 리스트
//delete코드 맞는겨?
#if 0
#pragma warning (disable : 4996)
#include <iostream>

struct Pin{
	int f; int r; 
	int used;
	Pin * next;
	Pin() :f(0), r(0), used(0), next(0) {}
	Pin(int n, int m) :f(n), r(m), used(0), next(0){}
	Pin(Pin * p) :next(p){}
};

#define MAX_N	(100)
Pin * Head[MAX_N];

int T, Tc;
int N;
int List[MAX_N];

void init(void){

	for (register int i = 0; i < MAX_N; ++i){
		if (Head[i] !=0 ) delete Head[i];
	}
}

void insertNode(Pin * &targetNode, int n, int m){
	Pin * p;
	p = new Pin(n, m);
	if (!targetNode) targetNode = new Pin();
	if (!targetNode->next) targetNode->next = p;
	else insertNode(targetNode->next, n, m);
}

void input(void){
	int n, m;

	scanf("%d", &N);
	for (register int i = 0; i < N; ++i){
		scanf("%d %d", &n, &m);
		insertNode(Head[n], n, m);
	}
}

void output(void){

	printf("#%d ", Tc);
	for (register int i = 0; List[i]!=0; ++i){
		printf("%d ", List[i]);
	}
	printf("\n");
}

int DFS(int L, int C){

	Pin * t;
	if (C >= N+N) return 1;

	if (Head[L] == 0) return 0;
	for (t = Head[L]->next; t != 0; t = t->next){
		
		if (t->used == 0){
			t->used = 1;
			List[C] = L;
			List[C + 1] = t->r;
			if(DFS(t->r, C + 2)==1) return 1;
			t->used = 0;
		}
	}
	return 0;
}

int main(void){

	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		input();
		for (register int i = 0; i < MAX_N; ++i){
			if (Head[i] == 0) continue;
			if(DFS(i, 0) == 1) break;
		}
		output();
	}
	return 0;
}

#endif

//1258 .  [S/W 문제해결 응용] 7일차 - 행렬찾기 / 화학물질1

//BFS
#if 0
#pragma warning (disable : 4996)
#include <iostream>

struct ST1{
	int r; int c;
};

#define MAX_N	(100+2)
int T, Tc;
int N;
int Map[MAX_N][MAX_N];
int V[MAX_N][MAX_N];

int Count_submx;
ST1 Queue[MAX_N*MAX_N];
ST1 A[(MAX_N*MAX_N/2 + 1) + 1];
int Area[(MAX_N*MAX_N / 2 + 1) + 1];
int WP, RP;

void InQueue(int rr, int cc){ Queue[WP].r = rr;	Queue[WP++].c = cc; }
ST1 DeQueue(void){ return Queue[RP++]; }
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void init_and_input(void){

	scanf("%d", &N);
	Count_submx = 0;
	for (register int i = 0; i < N; ++i){
		for (register int j = 0; j < N; ++j){
			scanf("%d", &Map[i][j]);
			V[i][j] = 0;
		}
	}
}

int BFS(int rr, int cc){

	int nr, nc;
	ST1 out;

	RP = 0;
	WP = 0;
	V[rr][cc] = Count_submx;
	InQueue(rr, cc);
	
	while (RP < WP){
		out = DeQueue();
		for (register int i = 0; i < 4; ++i){
			nr = out.r + dr[i];
			nc = out.c + dc[i];
			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
			if (Map[nr][nc] != 0 && V[nr][nc] == 0){
				V[nr][nc] = Count_submx;
				InQueue(nr, nc);
			}
		}
	}
	return WP;
}

#define SWAP(x,y)	{int temp1; ST1 temp2; temp1=Area[x], temp2=A[x]; Area[x]=Area[y], A[x]=A[y]; Area[y]=temp1, A[y]=temp2; }
int partition(int p, int r){
	int j = p - 1;
	for (int i = p; i < r; i++){
		if (Area[i] < Area[r]){
			j++;
			SWAP(i,j);
		}
		else if (Area[i] == Area[r]){
			if (A[i].r < A[r].r){
				j++;
				SWAP(i,j);
			}
		}
	}
	j++;
	SWAP(r, j);
	return j;
}

void QSORT(int p, int r){
	if (p < r){
		int q = partition(p, r);
		QSORT(p, q - 1);
		QSORT(q + 1, r);
	}
}

void output(void){
	printf("#%d %d ", Tc, Count_submx);
	for (register int i = 1; i <= Count_submx; ++i){
		printf("%d %d ", A[i].r, A[i].c);
	}
	printf("\n");
}

int main(void){

	//걍 4중포문 돌려라
	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		init_and_input();
		for (register int i = 0; i < N; ++i){
			for (register int j = 0; j < N; ++j){
				if (Map[i][j] != 0 && V[i][j] == 0) {
					++Count_submx;
					Area[Count_submx] = BFS(i, j);
					for (A[Count_submx].r = 0; Map[i + A[Count_submx].r][j] != 0; ++A[Count_submx].r);
					A[Count_submx].c = Area[Count_submx]/A[Count_submx].r;
				}
			}
		}		
		QSORT(1, Count_submx);
		output();
	}
	return 0;
}

#endif

//for문으로만
#if 0
#pragma warning (disable : 4996)
#include <iostream>

struct ST1{
	int r; int c;
};

#define MAX_N	(100+2)
int T, Tc;
int N;
int Map[MAX_N][MAX_N];

int Count_submx;
ST1 A[MAX_N*MAX_N / 2 + 1];
int Area[MAX_N*MAX_N / 2 + 1];

void init_and_input(void){

	scanf("%d", &N);
	Count_submx = 0;
	for (register int i = 1; i <= N; ++i){
		for (register int j = 1; j <= N; ++j){
			scanf("%d", &Map[i][j]);
		}
	}
}

#define SWAP(x,y)	{int temp1; ST1 temp2; temp1=Area[x], temp2=A[x]; Area[x]=Area[y], A[x]=A[y]; Area[y]=temp1, A[y]=temp2; }
int partition(int p, int r){
	int j = p - 1;
	for (int i = p; i < r; i++){
		if (Area[i] < Area[r]){
			j++;
			SWAP(i, j);
		}
		else if (Area[i] == Area[r]){
			if (A[i].r < A[r].r){
				j++;
				SWAP(i, j);
			}
		}
	}
	j++;
	SWAP(r, j);
	return j;
}

void QSORT(int p, int r){
	if (p < r){
		int q = partition(p, r);
		QSORT(p, q - 1);
		QSORT(q + 1, r);
	}
}

void output(void){
	printf("#%d %d ", Tc, Count_submx);
	for (register int i = 1; i <= Count_submx; ++i){
		printf("%d %d ", A[i].r, A[i].c);
	}
	printf("\n");
}

int main(void){

	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		init_and_input();
		for (register int i = 1; i <= N; ++i){
			for (register int j = 1; j <= N; ++j){
				if (Map[i][j] != 0 && Map[i][j - 1] == 0 && Map[i - 1][j] == 0) {
					++Count_submx;
					for (A[Count_submx].r = 0; Map[i + A[Count_submx].r][j] != 0; ++A[Count_submx].r);
					for (A[Count_submx].c = 0; Map[i][j + A[Count_submx].c] != 0; ++A[Count_submx].c);
					Area[Count_submx] = A[Count_submx].r*A[Count_submx].c;
				}
			}
		}
		QSORT(1, Count_submx);
		output();
	}
	return 0;
}

#endif

//1260 .  [S/W 문제해결 응용] 7일차 - 화학물질2		

//포기! DFS로 접근하면 터진대 그리고 괄호가 사이사이에 묶이는거라서 ㅜ
#if 0
#pragma warning (disable : 4996)
#include <iostream>

struct ST1{
	int r; int c; 
	int used;
	//ST1 * next;
	//ST1() : r(0), c(0), used(0), next(0) {}
	//ST1(int n, int m) : r(n), c(m), used(0), next(0){}
	//ST1(ST1 * p) : next(p){}
};

#define MAX_N	(100+5)
int T, Tc;
int N;
int Map[MAX_N][MAX_N];

int Count_submx;
ST1 A[MAX_N*MAX_N / 2 + 1];

//ST1 * Head[MAX_N];
int min;

void init_and_input(void){
	
	min = 0x7fffffff;
	Count_submx = 0;
	scanf("%d", &N);
	for (register int i = 1; i <= N; ++i){
		for (register int j = 1; j <= N; ++j){
			scanf("%d", &Map[i][j]);
		}
	}
}

//void insertNode(ST1 * &targetNode, int n, int m){
//
//	ST1 * p = new ST1(n, m);
//	if (!targetNode) targetNode = new ST1(p);
//	else insertNode(targetNode->next, n, m);
//}
//
//void DFS(int L, int sp, int ep, int S){
//
//	ST1 * t;
//
//	if (S >= min) return;
//	if (L > Count_submx){
//		if (min > S) min = S;
//		return;
//	}
//	if (Head[ep] == 0) return;
//	
//	for (t = Head[ep]->next; t != 0; t = t->next){
//		if (t->used == 0){
//			t->used = 1;
//			DFS(L+1, ep, t->c, S+ ep*sp*t->c);
//			t->used = 0;
//		}
//	}
//	return;	
//}

int main(void){
		
	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		init_and_input();
		for (register int i = 1; i <= N; ++i){
			for (register int j = 1; j <= N; ++j){
				if (Map[i][j] != 0 && Map[i][j-1] == 0 && Map[i-1][j] == 0) {
					++Count_submx;
					for (A[Count_submx].r = 0; Map[i + A[Count_submx].r][j] != 0; ++A[Count_submx].r);
					for (A[Count_submx].c = 0; Map[i][j + A[Count_submx].c] != 0; ++A[Count_submx].c);
					//insertNode(Head[A[Count_submx].r], A[Count_submx].r, A[Count_submx].c);
				}
			}
		}
		for (register int i = 1; i <= N; ++i){
			//if (!Head[i]) continue;
			DFS(1, 0, i, 0);
		}
		//output
		printf("#%d %d\n", Tc, min);
	}
	return 0;
}

#endif

//1263 .  [S/W 문제해결 응용] 8일차 - 사람 네트워크2 

//All pairs Shortest 알고리즘 이용 //9,459 ms
#if 0
#pragma warning (disable:4996)
#include <iostream>

#define MAX_N	(1000+5)
#define INF		(1000)
#define MIN(x,y)	((x)>(y)? (y) : (x))
int T, Tc;
int N;
int W[MAX_N][MAX_N];
int S[MAX_N];
int min;

void vvv(void)
{
	int i, j;

	printf("====W출력=====\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", W[i][j]);
		}
		printf("\n");
	}
	printf("====S출력=====\n");
	for (i = 1; i <= N; i++)
	{
		printf("%d ", S[i]);
	}
	printf("\n");
	printf("\n");
}

void init_and_input(void)
{
	scanf("%d", &N);
	for (register int i = 1; i <= N; ++i){		
		S[i] = 0;
		for (register int j = 1; j <= N; ++j){
			scanf("%d", &W[i][j]);
			if (W[i][j] == 0) W[i][j] = INF;
		}		
	}
}
	
void DP(void)
{
	for (register int k = 1; k <= N; ++k){
		for (register int i = 1; i <= N; ++i){
			if (i == k) continue;
			for (register int j = 1; j <= N; ++j){
				if (j == i || j == k) continue;
				if (W[i][j] == 1) continue;
				//if (W[i][j] == INF || W[i][k] == INF || W[k][j] == INF) continue;
				W[i][j] = MIN(W[i][j], W[i][k] + W[k][j]);
			}
		}
	}

	for (register int i = 1; i <= N; ++i){
		for (register int j = 1; j <= N; ++j){
			if (i == j) continue;
			if (W[i][j] == INF) continue;
			S[i] += W[i][j];
		}
	}

	//연결안된경우 나~중에 생각해봐
	min = S[1];
	for (register int i = 2; i <= N; ++i){
		if (S[i] != INF && min > S[i]) min = S[i];
	}
}

void output(void)
{
	printf("#%d %d\n", Tc, min);
}

int main(void)
{
	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		init_and_input();
		DP();
		//vvv();
		output();
	}
	return 0;
}

#endif

//BFS	//8,807 ms
#if 0
#pragma warning (disable:4996)
#include <iostream>

#define MAX_N	(1000+5)
#define INF		(1000)
#define MIN(x,y)	((x)>(y)? (y) : (x))
int T, Tc;
int N;
int W[MAX_N][MAX_N];
int Min;

int WP, RP;
int Queue[MAX_N*MAX_N];
int V[MAX_N];

void init_and_input(void)
{
	Min = INF*INF;
	scanf("%d", &N);
	for (register int i = 1; i <= N; ++i){
		for (register int j = 1; j <= N; ++j){
			scanf("%d", &W[i][j]);
			if (W[i][j] == 0) W[i][j] = INF;
		}
	}
}

void output(void)
{
	printf("#%d %d\n", Tc, Min);
}

void BFS(int n)
{	
	int out;

	for (register int i = 1; i <= N; ++i) V[i] = INF;
	WP = 0;
	RP = 0;
	V[n] = 0;
	Queue[WP++] = n;

	while (RP < WP){
		out = Queue[RP++];
		for (register int i = 1; i <= N; ++i){
			if (W[out][i] == 1 && V[i] > V[out] + 1){
				Queue[WP++] = i;
				V[i] = V[out] + 1;
			}
		}
	}
	return;
}

int main(void)
{
	int temp;

	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		init_and_input();		
		for (register int i = 1; i <= N; ++i) {
			BFS(i);
			temp = 0;
			for (register int j = 1; j <= N; ++j){
				if (V[j] == INF) continue; //연결안된거있니
				temp += V[j];
			}
			if (Min > temp) Min = temp;
		}		
		output();
	}
	return 0;
}


#endif


//1264 .  [S/W 문제해결 응용] 8일차 - 이미지 유사도 검사 
#if 0
#pragma warning (disable:4996)
#include <iostream>

#define MAX_N	(500+5)
#define MAX(x,y)	((x)>(y)?(x):(y))
int T, Tc;
int N;
char X[MAX_N], Y[MAX_N];
int A[MAX_N][MAX_N];

void input(void)
{
	scanf("%d", &N);
	scanf("%s", X+1);
	scanf("%s", Y+1);
}

void DP(void)
{
	for (register int i = 1; i <= N; ++i){
		for (register int j = 1; j <= N; ++j){
			if (X[i] == Y[j]){
				A[i][j] = A[i - 1][j - 1] + 1;			//A[0][0]=0임을 이용해서 X+1부터 받는다
			}
			else{
				A[i][j] = MAX(A[i - 1][j], A[i][j - 1]);
			}
		}
	}
}

void output(void)
{
	printf("#%d %.2f\n", Tc, (double)A[N][N]*100/N);
}

int main(void)
{
	scanf("%d", &T);
	for (Tc = 1; Tc <= T; ++Tc){
		input();
		DP();
		output();
	}
	return 0;
}

#endif
