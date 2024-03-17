#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 2e5 + 5;
const int M = 1e9 + 7;
vector<int> adj[N];
int bit[N], n, m, r, b, d[2][N];
array<int, 2> D[N];

void add(int r, int d) {
	d %= M;
	for (; r < N; r |= (r + 1)) {
		bit[r] += d;
		if (bit[r] >= M) bit[r] -= M;
	}
}
int get(int r) {
	int re = 0;
	for (; r >= 0; r &= (r + 1), r--)
		re += bit[r];
	return re % M;
}

void bfs(int x, int d[]) {
	queue<int> Q; Q.push(x);
	d[x] = 1;
	while (Q.size()) {
		int v = Q.front();
		Q.pop();
		for (auto u: adj[v]) if (!d[u]) {
			d[u] = d[v] + 1;
			Q.push(u);
		}
	}	
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> r >> b;
	b--, r--;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	bfs(b, d[0]);
	bfs(r, d[1]);

	for (int i = 0; i < n; i++) D[i] = {d[0][i], i};
	sort(D, D + n);

	vector<array<int, 2>> E;
	for (int i = 0; i < n; i++) if (D[i][1] != r && D[i][1] != b) 
		E.push_back({D[i][0], -d[1][D[i][1]]});
	sort(E.begin(), E.end());
	E.resize(unique(E.begin(), E.end()) - E.begin());
	
	add(1, +1);
	for (auto p: E) {
		int u = p[0], v = -p[1];
		//cout << u << " <-> " << v << endl;
		add(v, get(v - 1));

	}
	cout << get(N - 1) << '\n';

	return 0;
}
//نرو
