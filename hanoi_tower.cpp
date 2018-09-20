//하노이의 탑 4개
#if 10
#include <iostream>

#define	INF	(0x7fffffff)
#define MAX_DISK	(50+1)

long long T[MAX_DISK];

#define MIN(x, y)	((x)<(y)?(x):(y))
long long DP(int N)
{
	if (N == 0) return 0;
	if (T[N] != 0) return T[N];

	long long ans = INF;
	for (register int i = 1; i <= N - 1; ++i){
		ans = MIN(ans, 2 * T[i] + (1ll << (N - i)) - 1);
	}
	return T[N] = ans;
}

int main(void)
{
	T[0] = 0;
	T[1] = 1;
	for (int i = 1; i <= 100; i++){
		printf("#%d %lld, 차이: %lld\n", i, DP(i), DP(i) - DP(i - 1));
	}
	return 0;
}

#endif
