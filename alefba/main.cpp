#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
//#define int long long
static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
using namespace __gnu_pbds;

struct chash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	size_t operator()(const int &a) const {
		int x = splitmix64(a + FIXED_RANDOM);
		return x ^ (x >> 16);
	}
};

using hash_map = unordered_map<int, long long, chash>;

const long long INF = 1ll << 50;
const int N = 3e5 + 15;
const int M = 1e5 + 20;

int dpr[N];
int gpr(int u) {
	return dpr[u] == u ? u : dpr[u] = gpr(dpr[u]);
}

struct S {
	hash_map fenw;	
	long long delta = 0;
	void add(int r, long long x) {
		x -= delta;
		x -= INF;
		for (; r <= M; r += r & -r) fenw[r] = min(fenw[r], x);
	}
	long long get(int r) {
		long long re = 0;
		for (; r; r -= r & -r) re = min(re, fenw[r]);
		return re + INF + delta;
	}
	int size() {
		return fenw.size();
	}
} gooni[M];

void merge(int u, int v) {
	u = gpr(u), v = gpr(v);
	if (gooni[u].size() > gooni[v].size()) swap(u, v);
	//u.size() <= v.size()

	dpr[u] = v;
	for (auto &p: gooni[u].fenw) {
		gooni[v].fenw[p.first] = min(gooni[v].fenw[p.first], p.second + gooni[u].delta - gooni[v].delta);
	}
}

int h[N], n, m;
vector<int> adj[N];
vector<array<int, 2>> back[N];

void dfs(int v) {
	if (adj[v].size() == 0) {
		gooni[v].add(h[v], 0);
	}
	for (auto u: adj[v]) {
		h[u] = h[v] + 1;
		dfs(u);
	}
	long long re = 0;
	for (auto u: adj[v]) {
		int x = gpr(u);
		re += gooni[x].get(h[v]);
	}

	for (auto u: adj[v]) {
		int x = gpr(u);
		gooni[x].delta += re - gooni[x].get(h[v]);
	}
	for (auto u: adj[v]) merge(u, v);
	
	int x = gpr(v);
	for (auto p: back[v]) if (h[p[0]] < h[v]) {
		gooni[x].add(h[p[0]], re + p[1]);
	}
}


signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int p; cin >> p; p--;
		adj[p].push_back(i);
	}
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		u--, v--;
		back[u].push_back({v, c});
		back[v].push_back({u, c});
	}
	iota(dpr, dpr + N, 0);

	h[0] = 1;
	dfs(0);
	int x = gpr(0);

	cout << gooni[x].get(1) << '\n';

	return 0;
}
//به زآن که فروشند چه خواهند خرید
