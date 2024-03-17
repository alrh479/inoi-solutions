#include "bits/stdc++.h"
#define int long long
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
const long long INF = 1ll << 60;
const int N = 500 + 5;
const int M = 1e9 + 7;
int dp[2][N][N], C[N][N], n, m;

inline int f(int x) {
	return x & 1;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	C[0][0] = 1;
	FOR(i, 1, N) {
		C[i][0] = 1;
		FOR(j, 1, i + 1)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M;
	}
	cin >> n >> m;
	dp[0][0][0] = 1;
	FOR(i, 0, n) {
		FOR(j, 0, n + 1) FOR(k, 0, m + 1) dp[f(i + 1)][j][k] = 0;
		FOR(j, 0, n + 1) {
			FOR(k, 0, m + 1) {
				dp[f(i)][j][k] %= M;
				int cur = dp[f(i)][j][k], nx = f(i + 1);
				dp[nx][j + 1][k + 1] += cur * (j + 1) % M;
				if (j >= 2) dp[nx][j - 1][k + 1] += cur * (j - 1) % M;
				dp[nx][j][k + 1] += cur * 2 % M * j % M;
				dp[nx][j][k] += cur * j % M;
			}
		}
	}
	int ans = 0;
	FOR(j, 1, n + 1) {
		FOR(k, 1, m + 1) {
			ans += dp[f(n)][j][k] % M * C[m - k + 1][j] % M;
			//cout << n << ' ' << j << ' ' << k << ' ' << dp[n][j][k] << '\n';
		}
	}
	ans %= M;
	cout << ans << '\n';
	return 0;
}
//Reading this fills you with DETERMINATION
//09:26:41
