#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e6 + 5;
const int M = 1e9 + 9;
const int P = 1e6 + 3;
const int INV = 27749917;
int logo[N], h[N], n, m;
int S[4 * N], mult[4 * N];

void um(int v, int l, int r, int L, int R, int z) {
	if (R <= l || r <= L) return;
	if (L <= l && r <= R) {
		mult[v] = 1ll * mult[v] * z % M;
		S[v] = 1ll * S[v] * z % M;
		return;
	}
	int m = l + r >> 1;
	um(v << 1, l, m, L, R, z);
	um(v << 1 | 1, m, r, L, R, z);

	S[v] = S[v << 1] + S[v << 1 | 1];
	S[v] = 1ll * mult[v] * S[v] % M;
}
void update(int v, int l, int r, int ind, int val) {
	if (l + 1 == r) {
		S[v] = 1ll * val * mult[v] % M;
		return;
	}
	int m = l + r >> 1;
	if (ind < m) update(v << 1, l, m, ind, val);
	else update(v << 1 | 1, m, r, ind, val);
	S[v] = S[v << 1] + S[v << 1 | 1];
	S[v] = 1ll * mult[v] * S[v] % M;
}

void add(int ind, int val) {
	um(1, 0, N, ind + 1, N, P);
	update(1, 0, N, ind, val);
}
void remove(int ind) {
	um(1, 0, N, ind + 1, N, INV);
	update(1, 0, N, ind, 0);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	fill(mult, mult + 4 * N, 1);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> logo[i];
	for (int i = 1; i <= m; i++) cin >> h[i];

	for (int i = 1; i <= n; i++) {
		add(h[i], i);
	}

	long long HASH = 0, I = 0;
	for (long long i = 1, pw = 1; i <= n; i++, pw = pw * P % M) {
		I += pw;
		HASH += pw * logo[i] % M;
	}
	HASH %= M;
	I %= M;

	int ans = 0;
	for (int i = n; i <= m; i++) {
		ans += S[1] == HASH;
		remove(h[i - n + 1]);
		add(h[i + 1], i + 1);
		HASH += I;
		if (HASH >= M) HASH -= M;
	}
	cout << ans << '\n';
	return 0;
}
//نرو
