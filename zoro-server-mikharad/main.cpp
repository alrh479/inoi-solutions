#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 2000 + 50;
const int C = 102;
int dp[N][2 * C], n, m;

void smax(int &a, int b) {
	a = max(a, b);
}

struct val {
	int C, F, V;
} S[N], M[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	for (int i = 0; i < N; i++) fill(dp[i], dp[i] + 2 * C, -INF);

	cin >> n;
	for (int i = 0; i < n; i++) cin >> S[i].C >> S[i].F >> S[i].V;
	cin >> m;
	for (int i = 0; i < m; i++) cin >> M[i].C >> M[i].F >> M[i].V;

	auto cmp = [](const val &a, const val &b) {return a.F > b.F;};
	sort(S, S + n, cmp);
	sort(M, M + m, cmp);

	dp[0][0] = 0;

	for (int i = 0; i < m; i++) {
		for (int l = 0; l < n; l++) {
			for (int c = 0; c < C; c++) {
				smax(dp[l + 1][c + S[l].C], dp[l][c] - S[l].V);
				smax(dp[l + 1][c], dp[l][c]);
			}
		}
		for (int l = 1; l <= n; l++) if (S[l - 1].F >= M[i].F) {
			for (int c = M[i].C; c < C; c++) {
				smax(dp[l][c - M[i].C], dp[l][c] + M[i].V);	
			}
		}
	}
	int re = 0;
	for (int l = 0; l <= n; l++) for (int c = 0; c < C; c++) {
		//cout << (dp[l][c] <= -(1 << 30) ? -19 : dp[l][c]) << ' ';	
		re = max(re, dp[l][c]);
	}
	cout << re << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
