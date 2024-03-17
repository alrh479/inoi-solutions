#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e5 + 5;
int rt = -1, rt2 = -1;
vector<int> adj[N];
int d[2][N], p[N], n, m, col[N], HH[N], P[N][3];
bitset<N> mark, leaf, C[3];
bool cyc = false;
set<array<int, 2>> forbid;

void find_cycle(int v, int i) {
	if (cyc) return;
	mark[v] = true;
	for (auto u: adj[v]) if (u != p[v] && !forbid.count({u, v})) {
		if (cyc) return;
		
		if (!mark[u]) p[u] = v, find_cycle(u, i);
		else if (u == rt) {
			cyc = true;
			for (; v != rt; v = p[v]) {
				C[i][v] = true;
			}
			return;
		}
	}
}

void bfs(int x, int d[]) {
	fill(d, d + N, -1);
	queue<int> Q;
	Q.push(x);
	d[x] = 0;
	while (Q.size()) {
		int v = Q.front();
		Q.pop();
		for (auto u: adj[v]) if (d[u] == -1) {
			d[u] = d[v] + 1;
			Q.push(u);
		}
	}
}

map<vector<int>, int> hasher;
//copy pasta from https://codeforces.com/blog/entry/101010
int hashify(vector<int> x) {
	sort(x.begin(), x.end());
	if(!hasher[x]) {
		hasher[x] = hasher.size() + 1;
	}
	return hasher[x];
}

int H(int v, int p, int i) {
	if (leaf[v]) return HH[v] = hashify({});
	col[v] = i;
	vector<int> ch;
	for (auto u: adj[v]) if (u != p) {
		if (col[u]) {
			cout << "NO\n"; //TODO
			exit(0);
		}
		P[u][i] = v;
		ch.push_back(H(u, v, i));
	}
	return HH[v] = hashify(ch);
}

bool check() {
	assert(rt != rt2);
	bfs(rt, d[0]);
	bfs(rt2, d[1]);
	for (int i = 0; i < n; i++) if (d[0][i] == d[1][i]) {
		leaf[i] = true;
		if (adj[i].size() != 2) return false;
	}
	int cnt = leaf.count();
	if (cnt != m - n + 2) return false;

	int a = H(rt, rt, 1); 
	if (col[rt2]) return false;
	int b = H(rt2, rt2, 2);

	if (a != b) return false;
	for (int i = 0; i < n; i++) if (leaf[i]) {
		int s = 0;
		for (auto u: adj[i]) s += col[u];
		if (s != 3) return false;
	}

	mark = 0;
	for (int i = 0; i < n; i++) if (leaf[i]) {
		int u1 = i, u2 = i;
		while (true) {
			if (u1 == rt && u2 == rt2) break;
			if (u1 == rt || u2 == rt2) return false;

			if (HH[u1] != HH[u2]) return false;
			if (mark[u1] ^ mark[u2]) return false;
			if (mark[u1]) break;
			mark[u1] = mark[u2] = true;
			u1 = P[u1][1];
			u2 = P[u2][2];
		}
	}
	return true;
}

void find_root() {
	assert(rt != -1 && adj[rt].size() >= 3);
	for (int i = 3; i < adj[rt].size(); i++) {
		forbid.insert({adj[rt][i], rt});
		forbid.insert({rt, adj[rt][i]});
	}
	for (int i = 0; i < 3; i++) {
		forbid.insert({adj[rt][i], rt});
		forbid.insert({rt, adj[rt][i]});
		cyc = false;
		mark = 0;
		p[rt] = rt;
		find_cycle(rt, i);
		forbid.erase({adj[rt][i], rt});
		forbid.erase({rt, adj[rt][i]});
	}
	for (int i = 1; i < 3; i++) C[0] &= C[i];
	int x = C[0].count();
	if (x != 1) { //1 is rt itself
		cout << "NO\n";
		exit(0);
	}
	rt2 = C[0]._Find_first();
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--, v--;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	for (int i = 0; i < n; i++) {
		if (adj[i].size() >= 3) rt = i;
		if (adj[i].size() == 1) {
			rt = -1;
			break;
		}
	}
	if (rt == -1) {
		for (int i = 0; i < n; i++) if (adj[i].size() == 1) rt = i;
		for (int i = 0; i < rt; i++) if (adj[i].size() == 1) rt2 = i;
		if (rt == -1) { //all are 2-degree
			cout << (n % 2 ? "NO\n" : "YES\n");
			return 0;
		}
		if (rt2 == -1) { //only one 1-degree
			cout << "NO\n";
			return 0;
		}
	}
	else
		find_root();
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		cnt += adj[i].size() == 1;
	}
	if (cnt > 2) {
		cout << "NO\n";
		return 0;
	}
	cout << (check() ? "YES" : "NO") << '\n';
	return 0;
}
//نرو
