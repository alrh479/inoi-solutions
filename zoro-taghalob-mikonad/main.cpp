#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 2e5 + 5;
const int M = 5e5;
int bit[M];

void update(int r, int x) {
	for (; r < M; r += r & -r) bit[r] = max(bit[r], x);
}
int get(int r) {
	int re = 0;
	for (; r; r -= r & -r) re = max(re, bit[r]);
	return re;
}

int a[N], kol[M], n, d[N], st[N], fn[N], x;

int get_idx(int x) {
	int ind = lower_bound(kol, kol + 2 * n, -x) - kol;
	assert(kol[ind] == -x);
	return ind + 1;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> x;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		kol[i << 1] = -a[i];
		kol[i << 1 | 1] = -a[i] + x;
	}
	sort(kol, kol + 2 * n);

	fill(d, d + N, INF);
	d[0] = -INF;
	for (int i = 0; i < n; i++) {
		fn[i] = lower_bound(d, d + N, a[i]) - d;
		d[fn[i]] = a[i];
	}

	fill(d, d + N, INF);
	d[0] = -INF;
	for (int i = n - 1; i >= 0; i--) {
		st[i] = lower_bound(d, d + N, -a[i]) - d;
		d[st[i]] = -a[i];
	}
	int mx = fn[n - 1];
	update(get_idx(a[n - 1]), st[n - 1]);

	for (int i = n - 2; i >= 0; i--) {
		mx = max(mx, get(get_idx(a[i] - x) - 1) + fn[i]);
		update(get_idx(a[i]), st[i]);
	}
	cout << mx << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
