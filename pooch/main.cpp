#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 3e5 + 5;
set<int> S, T;
deque<int> adj[N];
int ptr[N], cnt, P[N], n, mark[N], t, X, timer, mx, lst;

void D(int v) {
	for (auto u: adj[v]) if (u != P[v]) P[u] = v, D(u);
}

void dfs(int v) {
	mark[v] = t;
	cnt++;

	while (true) {
		int u = adj[v][ptr[v]];
		ptr[v] = (ptr[v] + 1) % adj[v].size();

		if (u == P[v]) {
			for (auto up: adj[v]) if (!mark[up]) T.insert(up);	
			return;
		}
		else if (!mark[u]) {
			dfs(u);
		}
	}
}

void find(int v) {
	++timer;
	if (mark[v] == mx) lst = timer - 1;
	for (auto u: adj[v]) if (u != P[v]) {
		find(u);
	}
	++timer;
}

void solve() {
	while (cnt < n) {
		T.clear();
		for (auto u: S) if (!mark[u]) dfs(u);	
		S = T;
		if (cnt < n) {
			X += 2 * cnt - 2;
		}
		t++;
	}
	mx = *max_element(mark, mark + N);
	for (int i = 1; i < n; i++) {
		while (adj[i].back() != P[i]) {
			int x = adj[i].front();
			adj[i].pop_front();
			adj[i].push_back(x);
		}
	}
	find(0);
	cout << X + lst << '\n';
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int l; cin >> l; adj[i].resize(l);
		for (auto &u: adj[i]) {
			cin >> u;
		}
	}
	D(0);
	cnt = 1;
	t = 1;
	mark[0] = t;
	for (auto u: adj[0])
		dfs(u);
	t++;
	if (cnt < n) X += 2 * cnt - 2;

	S = T;
	solve();
	return 0;
}
//نرو
