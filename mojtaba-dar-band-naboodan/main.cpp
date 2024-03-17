#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 5e5 + 15;
vector<int> X;
int A[N], B[N], C[N], D[N], m, n;

struct seg {
	int mn[4 * N];
	void init() {
		memset(mn, 0x3f3f3f, sizeof mn);
	}
	void update(int v, int l, int r, int ind, int I) {
		if (l + 1 == r) return void(mn[v] = min(mn[v], I));
		int m = l + r >> 1;
		if (ind < m)
			update(v << 1, l, m, ind, I);
		else 
			update(v << 1 | 1, m, r, ind, I);
		mn[v] = min(mn[v << 1], mn[v << 1 | 1]);
	}
	int get(int v, int l, int r, int L, int R) {
		if (r <= L || R <= l) return INF;
		if (L <= l && r <= R) return mn[v];
		int m = l + r >> 1;
		return min(get(v << 1, l, m, L, R), get(v << 1 | 1, m, r, L, R));
	}
	inline int g(int L, int R) {
		return get(1, 0, X.size(), L, R);
	}
	inline void u(int ind, int I) {
		update(1, 0, X.size(), ind, I);
	}	
} S[2];

void solve() {
	int ans = INF;
	S[0].u(0, 0);
	S[1].u(X.size() - 1, 0);

	for (int i = 0; i < m; i++) {
		//cout << A[i] << ' ' << B[i] << endl;
		ans = min(ans, S[0].g(A[i], B[i] + 1) + S[1].g(A[i], B[i] + 1) + D[i]);
		S[0].u(C[i], S[0].g(A[i], C[i] + 1) + D[i]);
		S[1].u(C[i], S[1].g(C[i], B[i] + 1) + D[i]);
	}
	cout << (ans == INF ? -1 : ans) << '\n';
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> m >> n;
	X.push_back(1);
	X.push_back(n);
	for (int i = 0; i < m; i++) {
		cin >> A[i] >> B[i] >> C[i] >> D[i];
		X.push_back(A[i]), X.push_back(B[i]), X.push_back(C[i]), X.push_back(min(n, B[i] + 1)), X.push_back(max(1ll, A[i] - 1));
	}
	sort(X.begin(), X.end());
	X.resize(unique(X.begin(), X.end()) - X.begin());

	for (int i = 0; i < m; i++) {
		A[i] = lower_bound(X.begin(), X.end(), A[i]) - X.begin();
		B[i] = lower_bound(X.begin(), X.end(), B[i]) - X.begin();
		C[i] = lower_bound(X.begin(), X.end(), C[i]) - X.begin();
	}
	S[0].init(), S[1].init();

	solve();

	return 0;
}
//نرو
