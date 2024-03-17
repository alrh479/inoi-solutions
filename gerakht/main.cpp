#include "bits/stdc++.h"
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
using namespace std;
const long long INF = 1ll << 60;
const int N = 20 + 2;
int n, m, q[N], T[N], G[N], mark, GP[N], deg[N], dist[N], rt, dd[N], re[N];
vector<int> d, choose[N], fin[N];

int bfs(int x, int a[]) {
	queue<int> q;
	memset(dist, 0x3f, sizeof dist);
	dist[x] = 0;
	q.push(x);

	while (q.size()) {
		int v = q.front();
		q.pop();
		FOR(i, 0, n) if (dist[i] > N && (a[v] >> i & 1)) {
			q.push(i);
			dist[i] = dist[v] + 1;
		}
	}
	return *max_element(dist, dist + n);

}
int root_T() {
	FOR(i, 0, n) if (bfs(i, T) <= 2) return i;
	return -1;
}

bool dfs(int v) {
	mark |= 1 << v;
	for (int adj = GP[v] & ~mark; adj; adj = GP[v] & ~mark) {
		int u = __lg(adj);
		assert(~deg[u] >> v & 1);
		if (__builtin_popcount(deg[u]) < dd[u]) {
			deg[u] |= 1 << v;
			return true;
		}
		mark |= 1 << u;

		for (int a2 = ~mark & deg[u]; a2; a2 = ~mark & deg[u]) {
			int u2 = __lg(a2);
			if (dfs(u2)) {
				deg[u] ^= (1 << v) ^ (1 << u2);
				return true;
			}
		}
	}
	return false;
}

void magic(int v, int first_part, int second_part) {
	memset(deg, 0, sizeof deg);	
	for (int i = 0, cnt = 0; i < n; i++) {
		GP[i] = G[i];
		if (first_part >> i & 1) {
			GP[i] &= second_part;
			dd[i] = d[cnt++];
		}
		else if (second_part >> i & 1) GP[i] &= first_part;
	}
	FOR(i, 0, n) if (second_part >> i & 1) { //belong to second-part
		mark = 0;
		if (!dfs(i)) return;
	}
	re[v] = rt;

	for (int i = 0; i < n; i++) if (first_part >> i & 1) {
		int x = __builtin_popcount(deg[i]);
		int y = fin[x].back();
		fin[x].pop_back();
		re[i] = y;
		FOR(j, 0, n) if (j != rt && (T[y] >> j & 1)) {
			int z = __lg(deg[i]);
			re[z] = j;
			deg[i] ^= 1 << z;
		}
	}
	FOR(i, 0, n) cout << re[i] + 1 << ' ';
	cout << '\n';
	exit(0);
}

void check(int v) {
	if (bfs(v, G) > 2) return;
	int x = d.size();
	for (auto c: choose[x]) if ((G[v] & c) == c) {
		assert(is_sorted(d.begin(), d.end()));
		do {
			magic(v, c, (1 << n) - 1 - c - (1 << v));
		} while (next_permutation(d.begin(), d.end()));
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	FOR(i, 0, 1 << n) {
		choose[__builtin_popcount(i)].push_back(i);
	}
	FOR(i, 1, n) {
		int u, v; cin >> u >> v; u--, v--;
		T[u] |= 1 << v;
		T[v] |= 1 << u;
	}
	FOR(i, 0, m) {
		int u, v; cin >> u >> v; u--, v--;
		G[u] |= 1 << v;
		G[v] |= 1 << u;
	}

	rt = root_T();
	assert(rt != -1);
	FOR(i, 0, n) if (T[rt] >> i & 1) {
		d.push_back(__builtin_popcount(T[i]) - 1);
		fin[d.back()].push_back(i);
	}
	sort(d.begin(), d.end());

	FOR(i, 0, n) check(i);
	cout << "-1\n";
	return 0;
}
