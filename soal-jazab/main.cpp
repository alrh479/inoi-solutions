#include "bits/stdc++.h"
using namespace std;
#define int long long
const int N = 19 + 1;
const int N_ = N + 4;

long long f[N_][N_][N_ * N_];
long long dp[N_][N_][N_ * N_];
int ptr, num[N_], suf[N], cnt[N];

int inv(int x) {
	memset(cnt, 0, sizeof cnt);
	int ans = 0;
	while (x) {
		int r = x % 10;
		x /= 10;
		cnt[r]++;
		while (--r >= 0) ans += cnt[r];
	}
	return ans;
}

int calc_inv(int x) {
	int z = 0;
	int ans = 0;
	while (x) {
		ans += (x & 1 ? z : 0);
		z += (x & 1 ? 0 : 1);
		x >>= 1;
	}
	return ans;
}

void calc_f() {
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < (1 << j); i++) {
			int o = __builtin_popcount(i);
			int z = j - o;
			f[z][o][calc_inv(i)]++;
		}
	}
}

void calc_dp(int i, int t) {
	memset(dp, 0, sizeof dp);
	if (t < 0) return;

	dp[0][0][0] = 1;
	for (int r = 0; r <= 9; r++) {
		for (int k = 0; k <= i; k++) {
			for (int x = 0; x + k <= i; x++) {
				for (int inv = 0; inv <= N * N; inv++) {
					for (int inv2 = 0; inv2 <= k * x; inv2++) {
						if (r <= t) dp[r + 1][k + x][inv + inv2 + x * suf[r]] += dp[r][k][inv] * f[k][x][inv2];
						else if (k) dp[r + 1][k + x][inv + inv2 + x * suf[r]] += dp[r][k][inv] * f[k - 1][x][inv2];
					}
				}
			}
		}
	}
}

int solve(int);

signed main() {
	calc_f();

	int n;
	cin >> n;
	int T = inv(n);
	int tn = n;
	ptr = N + 1;
	while (tn) {
		num[--ptr] = tn % 10;
		tn /= 10;
	}
	int ans = 0;
	int cur = 0;
	for (int i = 0; i <= N; i++) {
		calc_dp(N - i + 1, num[i] - 1);	
		for (int t = 0; t + cur < T; t++) ans += dp[10][N - i + 1][t];
		//cout << num[i] << ' ' << ans << ' ' << cur << ' ' << N - i + 1 << endl;
		//apply_suf
		cur += suf[num[i]];
		for (int x = num[i] - 1; x >= 0; x--) suf[x]++;
	}
	cout << ans << endl;
	return 0;
	if (ans != solve(n)) {
		cout << "HERE\n";
		cout << ans << ' ' << solve(n) << endl;
		return 0;
	}
}

int solve(int x) {
	int ans = 0;
	int C = inv(x);
	for (int i = 0; i < x; i++) ans += inv(i) < C;
	return ans;
}
//به زآن که فروشند چه خواهند خرید
