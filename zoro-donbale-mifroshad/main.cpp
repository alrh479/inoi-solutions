#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e4 + 5;
const int Q = 100 + 5;
int dp[N], ans[Q][N], n, q, a[N], K[N], l, ps[N];

void add(const int k) {
	memset(ps, 0, sizeof ps);
	for (int i = 0; i <= n - l; i++) ps[dp[i]]++;
	for (int i = 1; i <= l; i++) ps[i] += ps[i - 1];
	for (int i = 0; i < q; i++) ans[i][k] = ps[K[i]];
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> l;

	for (int i = 0; i < n; i++) cin >> a[i];
	cin >> q;
	for (int i = 0; i < q; i++) cin >> K[i];

	for (int i = 0; i <= n - l; i++) for (int j = 0; j < l; j++) dp[i] += a[j] != a[j + i];
	
	add(0);
	for (int i = 1; i <= n - l; i++) {
		for (int j = n - l; j; j--) dp[j] = dp[j - 1] + (a[i + l - 1] != a[j + l - 1]) - (a[i - 1] != a[j - 1]);
		dp[0] = 0;
		for (int j = 0; j < l; j++) dp[0] += a[j] != a[j + i];
		add(i);
	}

	for (int i = 0; i < q; i++) {
		for (int j = 0; j <= n - l; j++) {
			cout << ans[i][j] - 1 << ' ';
		}
		cout << '\n';
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
