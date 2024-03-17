#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 50;
vector<pair<int, int>> adj[N];
long double e[N], fail[N], prob[N];
int n, m;

long double formula(int u) {
	return (prob[u] + 1.0) / (1.0 - fail[u]);
}

void solve() {
	for (int i = 0; i < N; i++)
		e[i] = 1e9, fail[i] = 1;
	priority_queue<pair<long double, int>> q;
	e[n - 1] = 0;
	q.push({0, n - 1});

	while (q.size()) {
		auto p = q.top();
		q.pop();
		long double dist = -p.first;
		int v = p.second;

		if (e[v] < dist) 
			continue;
		for (auto edge: adj[v]) {
			int u = edge.first;
			long double pp = 1.0 * edge.second / 1000.0;
			prob[u] += fail[u] * (1.0 - pp) * e[v];
			fail[u] *= pp;
			if (e[u] > formula(u)) {
				e[u] = formula(u);
				q.push({-e[u], u});
			}
		}
	}
	cout << fixed << setprecision(3);
	cout << e[0] << '\n';
}

signed main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, p;
		cin >> u >> v >> p;
		u--, v--;
		adj[v].emplace_back(u, p);
		adj[u].emplace_back(v, p);
	}
	solve();
}
