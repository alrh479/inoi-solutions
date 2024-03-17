#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 2000 + 5;
int dp[N][N], ps[N], n;
array<int, 3> G[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> G[i][0] >> G[i][1] >> G[i][2];
	}
	sort(G, G + n, [](const array<int, 3> &x, const array<int, 3> &y) {return x[1] < y[1];});

	for (int i = 0; i < N; i++) fill(dp[i], dp[i] + N, INF);
	for (int i = 1; i < n; i++)
		ps[i] = ps[i - 1] + G[i - 1][0];

	dp[n][0] = 0;
	for (int i = n - 1; i >= 0; i--) {
		int val = max(0ll, G[i][1] - ps[i]);
		for (int j = val; j < N; j++) {
			dp[i][j] = dp[i + 1][j];
		}
		for (int j = G[i][0]; j < N; j++)
			dp[i][j] = min(dp[i][j], dp[i + 1][j - G[i][0]] + G[i][2]);
	}

	cout << *min_element(dp[0], dp[0] + N) << '\n';

	return 0;
}
//به زآن که فروشند چه خواهند خرید
