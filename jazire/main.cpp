#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 4e5;
int n, q, a[N], mx[4 * N], x[N], y[N], lz[4 * N];
char c[N];

void push(int v) {
	lz[v << 1] += lz[v];
	lz[v << 1 | 1] += lz[v];
	mx[v << 1] += lz[v];
	mx[v << 1 | 1] += lz[v];
	lz[v] = 0;
}

void add(int v, int l, int r, int L, int R, const int d) {
	if (R <= L || r <= L || R <= l) return;
	if (L <= l && r <= R) {
		mx[v] += d;
		lz[v] += d;
		return;
	}
	push(v);
	int m = l + r >> 1;
	add(v << 1, l, m, L, R, d);
	add(v << 1 | 1, m, r, L, R, d);
	mx[v] = max(mx[v << 1], mx[v << 1 | 1]);
}
int get(int v, int l, int r, int ind) {
	if (l + 1 == r) return mx[v];
	push(v);
	int m = l + r >> 1;
	if (ind < m) return get(v << 1, l, m, ind);
	else return get(v << 1 | 1, m, r, ind);
}

int QU(int v, int l, int r, const int M) {
	if (l + 1 == r) {
		assert(mx[v] == M);
		return l;
	}
	push(v);
	int m = l + r >> 1;
	if (mx[v << 1] >= M) return QU(v << 1, l, m, M);
	else return QU(v << 1 | 1, m, r, M);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	vector<int> d(a, a + n + 1);
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> c[i];
		if (c[i] == '!') {
			cin >> y[i] >> x[i];
			d.push_back(x[i]);
		}
		else if (c[i] == '~') {
			cin >> x[i];
			d.push_back(x[i]);
		}
		else { //c[i] == '?'
			cin >> y[i];
		}
	}
	sort(d.begin(), d.end());

	for (int i = 1; i <= n; i++) a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin();

	for (int i = 0; i < q; i++) if (c[i] != '?') {
		x[i] = lower_bound(d.begin(), d.end(), x[i]) - d.begin();
	}

	for (int i = 1; i <= n; i++) add(1, 0, d.size(), a[i - 1], a[i], +1);

	for (int i = 0; i < q; i++) {
		if (c[i] == '!') {
			add(1, 0, d.size(), a[y[i] - 1], a[y[i]], -1);
			add(1, 0, d.size(), a[y[i]], a[y[i] + 1], -1);
			a[y[i]] = x[i];
			add(1, 0, d.size(), a[y[i] - 1], a[y[i]], +1);
			add(1, 0, d.size(), a[y[i]], a[y[i] + 1], +1);
			cout << mx[1] << '\n';
			assert(mx[1] >= 1);
		}
		else if (c[i] == '~') {
			cout << get(1, 0, d.size(), x[i]) << '\n';
		}
		else {
			if (mx[1] < y[i]) cout << -1 << '\n';
			else cout << d[QU(1, 0, d.size(), y[i])] << '\n';
		}
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید

