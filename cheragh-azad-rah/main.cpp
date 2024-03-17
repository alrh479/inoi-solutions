#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int S[4 * N], lz[4 * N], pw[N];

void tw(int &x) {
	x *= 2;
	if (x >= MOD) x -= MOD;
}
void push(int v) {
	S[v << 1] *= lz[v];
	S[v << 1 | 1] *= lz[v];
	lz[v << 1] *= lz[v];
	lz[v << 1 | 1] *= lz[v];
	
	S[v << 1] %= MOD;
	S[v << 1 | 1] %= MOD;
	lz[v << 1] %= MOD;
	lz[v << 1 | 1] %= MOD;

	lz[v] = 1;
}

void mult(int v, int l, int r, int L, int R) {
	if (R <= L || r <= L || R <= l) return;
	if (L <= l && r <= R) {
		tw(lz[v]);
		tw(S[v]);
		return;
	}
	push(v);

	int m = l + r >> 1;
	mult(v << 1, l, m, L, R);
	mult(v << 1 | 1, m, r, L, R);

	S[v] = (S[v << 1] + S[v << 1 | 1]) % MOD;
}
void update(int v, int l, int r, const int ind, const int val) {
	if (l + 1 == r) {
		S[v] = val;
		return;
	}
	int m = l + r >> 1;
	push(v);

	if (ind < m) update(v << 1, l, m, ind, val);
	else update(v << 1 | 1, m, r, ind, val);

	S[v] = (S[v << 1] + S[v << 1 | 1]) % MOD;
}
int get(int v, int l, int r, int L, int R) {
	if (R <= L || r <= L || R <= l) return 0;
	if (L <= l && r <= R) {
		return S[v];
	}
	push(v);

	int m = l + r >> 1;
	return (get(v << 1, l, m, L, R) + get(v << 1 | 1, m, r, L, R)) % MOD;
}

int n, L;
vector<int> Q[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	pw[0] = 1;
	for (int i = 1; i < N; i++) {
		pw[i] = pw[i - 1];
		tw(pw[i]);
	}
	fill(lz, lz + 4 * N, 1);

	cin >> n >> L;
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		Q[r].push_back(l);
	}
	L++;

	update(1, 0, L, 0, 1);

	int kol = 0;
	for (int i = 1; i < L; i++) {
		for (auto l: Q[i]) {
			kol++;
			mult(1, 0, L, 0, l);
		}
		int re = pw[kol] - get(1, 0, L, 0, L);
		re %= MOD;
		if (i + 1 == L) {
			if (re < 0) re += MOD;
			cout << re << '\n';
			return 0;
		}
		update(1, 0, L, i, re);
	}
	return 0;
}
//به زآن که فروشند چه خواهند خرید
