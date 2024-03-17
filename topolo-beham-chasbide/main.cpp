#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 50;
bitset<N> mark, good, goodp;
int cur, n, m;
vector<int> adj[N], adj_t[N], order;

void dfs(int v) {
	mark[v] = true;
	for (auto u: adj[v]) if (!mark[u])
		dfs(u);
	order.push_back(v);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].push_back(v);
		adj_t[v].push_back(u);
	}
	for (int i = 0; i < n; i++)
		sort(adj[i].begin(), adj[i].end());
	
	for (int i = 0; i < n; i++) if (!mark[i]) dfs(i);
	reverse(order.begin(), order.end());

	set<int> S;
	for (int i = 0; i < n; i++) {
		int v = order[i];
		for (auto u: adj_t[v]) S.erase(u);
		good[i] = S.empty();
		S.insert(order[i]);
	}
	S.clear();
	for (int i = n - 1; ~i; i--) {
		int v = order[i];
		for (auto u: adj[v]) S.erase(u);
		goodp[i] = S.empty();
		S.insert(order[i]);
	}


	vector<pair<int, int>> re;
	for (int i = 1; i < n; i++) if (good[i - 1] && goodp[i] && binary_search(adj[order[i - 1]].begin(), adj[order[i - 1]].end(), order[i]))
		re.emplace_back(order[i - 1], order[i]);

	sort(re.begin(), re.end());
	cout << re.size() << '\n';
	for (auto p: re)
		cout << p.first + 1 << ' ' << p.second + 1 << '\n';
}
