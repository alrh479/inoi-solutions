#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 30;
const int N = 5e5 + 50;
int p[N], S[4 * N], n, mn[N], k, re[N];
int out[N];
vector<int> G[N], order, MN;

int get(int v, int l, int r, int L, int R) {
	if (r <= L || R <= l) return INF;
	if (L <= l && r <= R) return S[v];
	int m = l + r >> 1;
	return min(get(v << 1, l, m, L, R), get(v << 1 | 1, m, r, L, R));
}
void upd(int v, int l, int r, int ind, int I) {
	if (l + 1 == r) {
		S[v] = I;
		return;
	}
	int m = l + r >> 1;
	if (ind < m) upd(v << 1, l, m, ind, I);
	else upd(v << 1 | 1, m, r, ind, I);
	S[v] = min(S[v << 1], S[v << 1 | 1]);
}
inline void add_edge(int u, int v) {
	u = p[u], v = p[v];
	G[v].push_back(u);
	out[u]++;
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int x; cin >> x; x--;
		p[x] = i;
	}
	fill(S, S + 4 * N, INF);
	for (int i = n - 1; i >= 0; i--) {
		int mx = get(1, 0, n, p[i], min(p[i] + k, n));
		if (mx < n) add_edge(i, mx);
		mx = get(1, 0, n, max(0, p[i] - k + 1), p[i] + 1);
		if (mx < n) add_edge(i, mx);
		upd(1, 0, n, p[i], i);
	}
	priority_queue<int> Q;
	vector<int> X;
	for (int i = 0; i < n; i++) if (!out[i]) Q.push(i);
	for (int i = 0; i < n; i++) {
		int v = Q.top();
		Q.pop();
		for (auto u: G[v]) {
			out[u]--;
			if (!out[u]) Q.push(u);
		}
		re[v] = n - i;
	}
	for (int i = 0; i < n; i++) cout << re[i] << '\n';
}
