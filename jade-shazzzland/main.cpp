#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 3e5 + 5;
int d[2][N], n, m, A, B, mark[N], ps[N], x[N], y[N];
vector<int> adj[N], adj_t[N];

void dfs(int v, int mark[], int col, vector<int> adj[]) {
	mark[v] = col;
	for (auto u: adj[v]) if (mark[u] == -1) dfs(u, mark, col, adj);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);

	memset(mark, -1, sizeof mark);
	memset(d, -1, sizeof d);
	cin >> n >> m >> A >> B;
	for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
	for (int i = 0; i < m; i++) {
		int c, d, k; cin >> c >> d >> k;
		c--, d--;
		adj[c].push_back(d);
		adj_t[d].push_back(c);
		if (k == 2) {
			adj[d].push_back(c);
			adj_t[c].push_back(d);
		}
	}
	
	vector<array<int, 2>> E;
	vector<int> Y;
	for (int i = 0; i < n; i++) if (x[i] == A) {
		E.push_back({y[i], i});	
		Y.push_back(y[i]);
	}
	sort(Y.begin(), Y.end());
	Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
	sort(E.begin(), E.end());

	vector<array<int, 2>> W;	
	for (int i = 0; i < n; i++) if (x[i] == 0) W.push_back({y[i], i});
	for (int i = 0; i < W.size(); i++) if (mark[W[i][1]] == -1) dfs(W[i][1], mark, 1, adj);
	for (int i = 0; i < E.size(); i++) if (d[0][E[i][1]] == -1) dfs(E[i][1], d[0], E[i][0], adj_t);
	for (int i = E.size() - 1; i >= 0; i--) if (d[1][E[i][1]] == -1) dfs(E[i][1], d[1], E[i][0], adj_t);

	for (int i = 0; i < n; i++) if (x[i] == A && mark[i] != -1) {
		int yy = lower_bound(Y.begin(), Y.end(), y[i]) - Y.begin();
		ps[yy]++;
	}
	for (int i = 1; i < n; i++) ps[i] += ps[i - 1];

	sort(W.rbegin(), W.rend());
	for (auto p: W) {
		int i = p[1];
		if (d[0][i] == -1) {
			cout << 0 << '\n';
			continue;
		}
		int mn = lower_bound(Y.begin(), Y.end(), d[0][i]) - Y.begin();
		int mx = lower_bound(Y.begin(), Y.end(), d[1][i]) - Y.begin();
		cout << (mn ? ps[mx] - ps[mn - 1] : ps[mx]) << '\n';
	}

	return 0;
}
//نرو
//از یه جایی به بعد نمیفهمم دارم چی میزنم
//ولی ایشالا که درسته :|

