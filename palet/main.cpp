#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 50;
const int K = 51;

int to[4 * N][K], a[K][K], cnt[K], n, k, q, ans[N], arr[N];
vector<pair<int, int>> dis[N], en[N];
vector<int> times[N];
char c[N];

void init(int v, int l, int r) {
	iota(to[v], to[v] + K, 0);
	if (r - l == 1) return;
	int mid = (l + r) >> 1;
	init(v << 1, l, mid);
	init(v << 1 | 1, mid, r);
}

void change(int v, int l, int r, const int time, const int col) {
	if (r - l == 1) {
		if (col != -1) {
			for (int i = 0; i < K; i++) 
				to[v][i] = a[i][col];
		}
		else
			iota(to[v], to[v] + K, 0);
		return;
	}
	int mid = (l + r) >> 1;
	if (time < mid)
		change(v << 1, l, mid, time, col);
	else
		change(v << 1 | 1, mid, r, time, col);
	for (int i = 0; i < K; i++)
		to[v][i] = to[v << 1 | 1][to[v << 1][i]];
}
void get(int v, int cl, int cr, int wl, int wr) {
	if (cr == wr && cl == wl) {
		for (int i = 0; i < K; i++) {
			cnt[i] = to[v][cnt[i]];
		}
		return;
	}
	int mid = (cl + cr) >> 1;
	if (wr <= mid)
		get(v << 1, cl, mid, wl, wr);
	else if (wl >= mid)
		get(v << 1 | 1, mid, cr, wl, wr);
	else {
		get(v << 1, cl, mid, wl, mid);
		get(v << 1 | 1, mid, cr, mid, wr);
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cin >> a[i][j];
			a[i][j]--;
		}
	}

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		arr[i]--;
	}
	cin >> q;

	for (int t = 0; t < q; t++) {
		cin >> c[t];
		if (c[t] == '#') {
			int l, r, col;
			cin >> l >> r >> col;
			l--, r--, col--;
			en[l].emplace_back(col, t);
			dis[r].emplace_back(col, t);
		}
		else {
			int i;
			cin >> i;
			i--;
			times[i].push_back(t);
		}
	}
	init(1, 0, q);
	
	for (int i = 0; i < n; i++) {
		for (auto p: en[i]) {
			change(1, 0, q, p.second, p.first);
		}
		for (auto r: times[i]) {
			iota(cnt, cnt + K, 0);
			get(1, 0, q, 0, r + 1);
			assert(arr[i] < K);
			ans[r] = cnt[arr[i]];
		}
		for (auto p: dis[i]) {
			change(1, 0, q, p.second, -1);
		}
	}
	for (int i = 0; i < q; i++) if (c[i] != '#') 
		cout << ans[i] + 1 << '\n';

	return 0;
}
