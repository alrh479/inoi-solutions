#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e6 + 5;
vector<int> adj[N];
vector<vector<int>> V;
int a[N], n, sz;

void add_edge(int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void dfs(int v, int p) {
	for (auto u: adj[v]) if (u != p) dfs(u, v);
	V[sz].push_back(v);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];

	vector<int> st;
	for (int i = 0; i < n; i++) {
		while (st.size() && a[st.back()] > a[i]) {
			add_edge(st.back(), i);
			st.pop_back();
		}
		st.push_back(i);
	}
	V.resize(st.size());
	for (auto u: st) { 
		dfs(u, u);
		sort(V[sz].begin(), V[sz].end());
		sz++;
	}
	sort(V.begin(), V.end());
	cout << V.size() << '\n';

	for (auto &v: V) {
		cout << v.size() << ' ';
		for (auto u: v)
			cout << u + 1 << ' ';
		cout << '\n';
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
