#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 5;
const int B = 1e9;
const int INF = ((int) 1e9 + 10) * B;

int a[N], n, k;
__int128_t ps[N], last[N];

bool check(int O) {
	ps[0] = (__int128_t) a[0] - O;
	for (int i = 1; i < n; i++)
		ps[i] = ps[i - 1] + a[i] - O;

	for (int i = 1; i <= n; i++) last[i] = (__int128_t) INF * INF;
	last[0] = -INF;

	for (int i = 0; i < n; i++) {
		if (ps[i] < 0) continue;
		int f = upper_bound(last, last + n + 1, ps[i]) - last;
		last[f] = ps[i];
		if (i + 1 == n) return f >= k;
	}
	return 0;
}

void solve() {
	for (int i = 0; i < n; i++)
		a[i] *= B;
	int l = 0, r = INF;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	cout << (double) l / B << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(9);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	solve();
	return 0;
}
