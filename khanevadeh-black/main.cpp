#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 50;
const int MX = 1e9 + N;

vector<int> L{-1}, R{-1}, S{0};
vector<int> adj[N], buy[N];
vector<pair<int, int>> ans[N];
int re[N];

int add(int v, int cl, int cr, int ind, int val) {
	if (v == -1) {
		v = R.size();
		L.push_back(-1);
		R.push_back(-1);
		S.push_back(0);
	}
	assert(~v);
	assert(R.size() == L.size() && R.size() == S.size());
	if (cr - cl == 1) {
		assert(cl == ind);
		S[v] += val;
		return v;
	}
	int mid = (1ll * cl + cr) / 2;
	if (ind >= mid) 
		R[v] = add(R[v], mid, cr, ind, val);
	else
		L[v] = add(L[v], cl, mid, ind, val);
	S[v] = (~R[v] ? S[R[v]] : 0) + (~L[v] ? S[L[v]] : 0);
	return v;
}
int get(int v, int cl, int cr, int wl, int wr) {
	if (v == -1) return 0;
	if (cl == wl && cr == wr) 
		return S[v];
	int mid = (1ll * cl + cr) / 2;
	if (wr <= mid)
		return get(L[v], cl, mid, wl, wr);
	else if (wl >= mid)
		return get(R[v], mid, cr, wl, wr);
	else
		return get(L[v], cl, mid, wl, mid) + get(R[v], mid, cr, mid, wr);
}
int ptr = N;

void dfs(int v) {
	for (auto t: buy[v]) {
		add(0, 0, MX, ptr + t, +1);
	}
	ptr--;
	for (auto u: adj[v]) {
		dfs(u);	
	}
	ptr++;

	for (auto p: ans[v]) {
		int t = p.first;
		int ind = p.second;
		re[ind] = get(0, 0, MX, 0, ptr + t + 1);
	}

	for (auto t: buy[v])
		add(0, 0, MX, ptr + t, -1);

}

signed main() {
	R.reserve(30 * N);
	L.reserve(30 * N);
	S.reserve(30 * N);

	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;

	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		adj[p].push_back(i);
	}
	int co = 0;
	while (q--) {
		char c;
		int v, t;
		cin >> c >> v >> t;
		v--;
		if (c == '$')
			buy[v].push_back(t);
		else
			ans[v].emplace_back(t, co++);
	}
	dfs(0);
	for (int i = 0; i < co; i++)
		cout << re[i] << '\n';
	cout << '\n';
	return 0;
}
