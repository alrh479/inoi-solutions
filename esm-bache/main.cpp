#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e5 + 50;
const int MOD = 1e9 + 9;
const int B = 31;
const int M = 202;
const int LG = __lg(N) + 1;

int to_hash(const string &s) {
	int x = 0;
	for (auto c: s)
		x = (x * B + (c - 'a' + 1)) % MOD;
	return x;
}
vector<int> swear[M + 5];
int p[N][LG], h[N], m, k, n, q, pw[N], sz;
char C[N];

int lca(int u, int v) {
	if (h[u] > h[v]) swap(u, v);
	while (h[u] < h[v]) {
		v = p[v][__lg(h[v] - h[u])];
	}
	if (u == v) return u;
	assert(h[u] == h[v]);

	for (int i = LG - 1; i >= 0; i--)
		if (p[v][i] != p[u][i])
			u = p[u][i], v = p[v][i];
	assert(p[u][0] == p[v][0]);
	return p[u][0];
}

signed main() {
	//ios::sync_with_stdio(0), cin.tie(0);
	pw[0] = 1;
	for (int i = 1; i < N; i++)
		pw[i] = pw[i - 1] * B % MOD;
	cin >> m >> k >> n >> q;
	for (int i = 0; i < m; i++) {
		string t;
		cin >> t;
		swear[t.size()].push_back(to_hash(t));
	}
	for (int i = 0; i < M; i++)
		sort(swear[i].begin(), swear[i].end());

	queue<int> Q;
	Q.push(0);
	sz = 1;

	while (sz <= n) {
		int v = Q.front();
		Q.pop();
		bitset<27> ok;

		int last = 0;
		int tv = v;
		int h;
		for (h = 1; h <= M && tv; h++) {
			for (int i = 0; i < k; i++)
				ok[i] = ok[i] | binary_search(swear[h].begin(), swear[h].end(), last + i + 1);
			last += (C[tv] - 'a' + 1) * pw[h];
			tv = p[tv][0];
		}
		for (int i = 0; i < k; i++)
			ok[i] = ok[i] | binary_search(swear[h].begin(), swear[h].end(), last + i + 1);

		for (int i = 0; i < k; i++) if (!ok[i]) {
			//trie[v][i] = sz;
			C[sz] = 'a' + i;
			p[sz][0] = v;
			Q.push(sz++);
		}
	}

	for (int i = 1; i <= n; i++) {
		h[i] = h[p[i][0]] + 1;
		for (int l = 1; l < LG; l++) {
			assert(p[i][l - 1] < i);
			p[i][l] = p[p[i][l - 1]][l - 1];
		}
	}
	while (q--) {
		char c; int x, y;
		cin >> c >> x >> y;
		int l = lca(x, y);

		if (c == '@') {
			if (l == 0) {
				cout << "I'm a blackboard\n";
				continue;
			}
			string s;
			while (l) {
				s += C[l];
				l = p[l][0];
			}
			reverse(s.begin(), s.end());
			cout << s << '\n';
		}
		else {
			cout << h[l] << '\n';
		}
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
