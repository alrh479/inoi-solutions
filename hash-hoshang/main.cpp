#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
int A[1 << 25], n, m, x, mask, inv;
long long ans = 0;

long long pw(long long a, int b) {
	long long re = 1;
	for (; b; b >>= 1, a = (a * a) & mask) if (b & 1)
		re = (re * a) & mask;
	return re;
}

void dfs(int v, int X) {
	if (X == 0) return void(A[v]++);
	for (int i = 1; i <= 26; i++)
		dfs((((v << 5) + v) ^ i) & mask, X - 1);
}
void rdfs(int v, int X) {
	if (X == 0) return void(ans += A[v]);
	for (int i = 1; i <= 26; i++)
		rdfs(((v ^ i) * inv) & mask, X - 1);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> x >> m;
	mask = (1 << m) - 1;
	int h = n >> 1;
	inv = pw(33, (1 << (m - 1)) - 1);
	dfs(0, h);
	rdfs(x, n - h);

	cout << ans;

	return 0;
}
//به زآن که فروشند چه خواهند خرید
