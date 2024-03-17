#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
typedef tree<
pair<int, int>,
null_type,
less<pair<int, int>>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
const int N = 1e5 + 5;
const int INF = N + 5;
int h[N], n, k, ent_nashode, U, V, cur[N], color[N], d[N];
vector<int> adj[N];
ordered_set dist;

const int BUF_SZ = 1 << 25;
char buf[BUF_SZ];
int len, pos;

char next_char() {
	if (pos == len) {
		pos = 0;
		len = (int)fread(buf, 1, BUF_SZ, stdin);
		if (!len) return EOF;
	}
	return buf[pos++];
}
int read_int() {
	int x;
	char ch;
	while (!isdigit(ch = next_char()));
	x = ch ^ 48;
	while (isdigit(ch = next_char())) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x;
}

void dfs(int v, int p) {
	for (auto u: adj[v]) if (u != p) {
		h[u] = h[v] + 1;
		dfs(u, v);
	}
}
set<pair<int, int>> all[N];
set<pair<int, int>> marja, mxcur;

void erase(int c, int v) {
	marja.erase({all[c].rbegin()->first, c});
	all[c].erase({d[v], v});
	marja.insert({all[c].rbegin()->first, c});
}
void insert(int c, int v) {
	marja.erase({all[c].rbegin()->first, c});
	all[c].insert({d[v], v});
	marja.insert({all[c].rbegin()->first, c});
}

int hal(int c) {
	if (c == -1) return INF;
	int re = 0;
	int q = all[c].rbegin()->first;
	marja.erase({q, c});
	re = max(re, marja.rbegin()->first);
	marja.insert({q, c});

	int x = ent_nashode - cur[c];
	if (x) re = max(re, dist.find_by_order(x - 1)->first);
	return re;
}

void solve() {
	if (color[U] && color[V]) {
		if (color[U] != color[V]) printf("%d\n", d[U]);
		else printf("%d\n", hal(color[U]));
		return;
	}
	if (color[U]) {
		printf("%d\n", hal(color[U]));
		return;
	}
	if (color[V]) {
		printf("%d\n", hal(color[V]));
		return;
	}
	int mn = hal(marja.rbegin()->second);
	mn = min(mn, hal(mxcur.rbegin()->second));
	printf("%d\n", mn);
}
void change_cur(int c, int d) {
	mxcur.erase({cur[c], c});
	cur[c] += d;
	ent_nashode += d;
	mxcur.insert({cur[c], c});
}

signed main() {
	n = read_int(), k = read_int();
	FOR(i, 1, k + 1) {
		all[i].insert({0, -1});
		marja.insert({0, i});
	}
	FOR(i, 1, n) {
		int u = read_int() - 1, v = read_int() - 1;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	FOR(i, 1, k + 1) cur[i] = read_int();
	int q = read_int();

	dfs(0, 0);
	U = max_element(h, h + n) - h;
	h[U] = 0;
	dfs(U, U);
	V = max_element(h, h + n) - h;
	copy(h, h + n, d);
	h[V] = 0;
	dfs(V, V);
	FOR(i, 0, n) d[i] = max(d[i], h[i]);

	FOR(i, 0, n)
		dist.insert({d[i], i});	
	FOR(i, 1, k + 1)
		mxcur.insert({cur[i], i});
	ent_nashode = n;
	solve();

	while (q--) {
		int x = read_int() - 1, c = read_int();
		if (color[x]) {
			change_cur(color[x], +1);
			erase(color[x], x);
		}
		else {
			dist.erase({d[x], x});
		}
		if (c) {
			insert(c, x);
			change_cur(c, -1);
		}
		else {
			dist.insert({d[x], x});
		}
		color[x] = c;
		solve();
	}
	return 0;
}
//10:19:39
