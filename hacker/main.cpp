#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 2005;
const int M = 1e9 + 7;
long long dp[N][N], ans;

inline int C(int n, int r) {
	if (r < 0 || n < r) return 0;
	return dp[n][r];
}

void calc(int B, int W, int n, int I) {
	if (n + I > B + W + 1) return;
	for (int b = 0; b + 1 <= I; b++) {
		if (n - B - 1 + I - b <= W) {
			ans += C(n - I, B - I + 1) * C(I - 1, b) % M;
		}
	}
	ans %= M;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int B, W, n, I;
	cin >> B >> W >> n >> I;

	if (!W || !B) {
		cout << (I == 1 ? 1 : 0) << '\n';
		return 0;
	}

	dp[0][0] = 1;
	for (int i = 1; i < N; i++) {
		dp[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
			if (dp[i][j] >= M) dp[i][j] -= M;
		}
	}
	calc(B, W, n, I);
	calc(W, B, n, I);

	cout << ans << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
