#include "bits/stdc++.h"
#define int short
#define ar array<int, 2>
using namespace std;
const long long INF = 90;
const int N = 72;
int n, k, w[N];
array<int, 2> dp[N][N][N];

void smin(ar &a, ar b) {a = min(a, b);}

int calc_dp() {
	for (int l = 0; l < n; l++) for (int r = 0; r < n; r++) for (int x = 0; x <= k; x++) dp[l][r][x] = {INF, 0};
	for (int l = n - 1; l >= 0; l--) {
		for (int x = 0; x <= k; x++) {
			if (x < w[l]) dp[l][l][x] = {1, -k + w[l]};
			else dp[l][l][x] = {0, -x + w[l]};
		}
		for (int r = l + 1; r < n; r++) {
			for (int x = 0; x <= k; x++) {
				for (int m = l; m < r; m++) {
					auto V = dp[l][m][x];
					auto U = dp[m + 1][r][-V[1]];
					smin(dp[l][r][x], {V[0] + U[0], U[1]});
				}
				auto V = dp[l + 1][r][x];
				if (-V[1] >= w[l]) smin(dp[l][r][x], {V[0], V[1] + w[l]});
				else smin(dp[l][r][x], {V[0] + 1, -k + w[l]});
			}
		}
	}
	return dp[0][n - 1][0][0];
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> w[i];
	cout << calc_dp();
	return 0;
}
