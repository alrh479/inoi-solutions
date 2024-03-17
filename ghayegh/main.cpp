#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1000'000'000;
const int M = 1e9 + 7;
const int N = 505;
const int NN = 2 * N;
int n, a[NN], b[NN], fact[NN], inv[NN], C[NN][NN], F[NN], dp[NN][NN];
vector<int> L{0}, R{INF + 1};

int pw(int a, int b) {
	int re = 1;
	for (; b; b >>= 1, a = a * a % M) if (b & 1) re = re * a % M;
	return re;
}
int calc_c(int n, int r) {
	int re = 1;
	for (int end = n - r; n > end; n--) re = re * n % M;
	return re * inv[r] % M;
}
void add(int &a, int b) {
	a += b;
	if (a >= M) a -= M;
}

void solve() {
	F[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int k = L.size() - 1; k >= 1; k--) if (a[i] <= L[k] && R[k] <= b[i]) {
			for (int t = N - 1; t >= 2; t--) {
				add(dp[k][t], dp[k][t - 1]);
				add(F[k], dp[k][t - 1] * C[k][t] % M);
			}
			//t = 1:
			for (int j = 0; j < k; j++) {
				add(dp[k][1], F[j]);
				add(F[k], F[j] * C[k][1] % M);
			}
		}
	}
	int ans = 0;
	for (int j = 1; j < NN; j++) ans += F[j];
	ans %= M;
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
		L.push_back(a[i]);
		R.push_back(a[i] - 1);
		R.push_back(b[i]);
		L.push_back(b[i] + 1);
	}
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());
	L.resize(unique(L.begin(), L.end()) - L.begin());
	R.resize(unique(R.begin(), R.end()) - R.begin());

	fact[0] = 1;
	inv[0] = 1;
	for (int i = 1; i < NN; i++) {
		fact[i] = fact[i - 1] * i % M;
		inv[i] = pw(fact[i], M - 2);
	}

	for (int i = 0; i < L.size(); i++) {
		for (int j = 0; j < N; j++) {
			if (j > R[i] - L[i] + 1) break;
			C[i][j] = calc_c(R[i] - L[i] + 1, j);
		}
	}
	solve();

	return 0;
}
//نرو
