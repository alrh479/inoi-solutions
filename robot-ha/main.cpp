#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 406;
int n, m, k;
int R[N][N], L[N][N], U[N][N], D[N][N];
bitset<N> X[N];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
	x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const array<int, 4> &x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
	size_t re = 0;
	for (auto &u: x) {
		re ^= splitmix64(u ^ FIXED_RANDOM);
		re >>= 1;
	}
        return re;
    }
};

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		int r, c; cin >> r >> c;
		r--, c--;
		X[r][c] = true;
	}
	for (int i = 0; i < n; i++) {
		L[i][0] = 0;
		for (int j = 1; j < m; j++) {
			if (X[i][j - 1]) L[i][j] = j;
			else L[i][j] = L[i][j - 1];
		}
	}
	for (int i = 0; i < n; i++) {
		R[i][m - 1] = m - 1;
		for (int j = m - 2; j >= 0; j--) {
			if (X[i][j + 1]) R[i][j] = j;
			else R[i][j] = R[i][j + 1];
		}
	}
	for (int j = 0; j < m; j++) {
		U[0][j] = 0;
		for (int i = 1; i < n; i++) {
			if (X[i - 1][j]) U[i][j] = i;
			else U[i][j] = U[i - 1][j];
		}
	}
	for (int j = 0; j < m; j++) {
		D[n - 1][j] = n - 1;
		for (int i = n - 2; i >= 0; i--) {
			if (X[i + 1][j]) D[i][j] = i;
			else D[i][j] = D[i + 1][j];
		}
	}
	int q;
	cin >> q;
	while (q--) {
		int r1, r2, c1, c2, ans = -1;
		cin >> r1 >> c1 >> r2 >> c2;
		r1--, r2--, c1--, c2--;
		queue<array<int, 4>> Q;
		Q.push({r1, c1, r2, c2});
		unordered_map<array<int, 4>, int, custom_hash> dist;
		dist[{r1, c1, r2, c2}] = 0;
		while (Q.size()) {
			auto a = Q.front();
			int r1 = a[0], r2 = a[2], c1 = a[1], c2 = a[3];
			int d = dist[a];
			if (a[0] == a[2] && a[1] == a[3]) {
				ans = d;
				break;
			}
			Q.pop();
			auto check = [&](const array<int, 4> &x) {
				if (a == x || dist.count(x)) return;
				dist[x] = d + 1;
				Q.push(x);
			};
			check({r1, R[r1][c1], r2, R[r2][c2]});
			check({r1, L[r1][c1], r2, L[r2][c2]});
			check({D[r1][c1], c1, D[r2][c2], c2});
			check({U[r1][c1], c1, U[r2][c2], c2});
		}
		cout << ans << '\n';
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
