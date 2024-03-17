#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 500;
int x[N], y[N], r[N], n;

bool is_in(int j, int i) { //is j in i?
	int dist = (x[j] - x[i]) * (x[j] - x[i]) + (y[j] - y[i]) * (y[j] - y[i]);
	return r[i] >= r[j] && dist < (r[i] - r[j]) * (r[i] - r[j]);
}

bitset<N> used, adj[N];
int mt[N];

bool try_kuhn(int v) {
	if (used[v]) return false;
	used[v] = true;
	for (int to = 0; to < n; to++) if (adj[v][to]) {
		if (mt[to] == -1 || try_kuhn(mt[to])) 
			return mt[to] = v, true;
	}
	return false;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> x[i] >> y[i] >> r[i];
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			adj[i][j] = is_in(j, i);
		}
	}

	memset(mt, -1, sizeof mt);
	for (int v = 0; v < n; ++v) {
		used = 0;
		try_kuhn(v);
	}
	int ans = 0;
	for (int v = 0; v < n; v++) ans += mt[v] != -1;
	cout << n - ans << endl;

	return 0;
}
//به زآن که فروشند چه خواهند خرید



///FIND alpha(G)
