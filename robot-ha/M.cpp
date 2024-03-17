#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 405;
const short M = 3300;
short n, m, k;
short R[N][N], L[N][N], U[N][N], D[N][N], ind[N][N], ptr = 1;
int dist[M][M];
array<short, 2> v[M];
bitset<N> X[N];
vector<short> adj[4][M];

inline void OK(short &x, short &y) {
	if (x < y) return;
	swap(x, y);
}

void bfs() {
	queue<array<short, 2>> Q;
	for (short i = 0; i < n; i++) {
		for (short j = 0; j < m; j++) if (!X[i][j]) {
			bool flag = !i || X[i - 1][j] || i + 1 == n || X[i + 1][j] || !j || X[i][j - 1] || j + 1 == m || X[i][j + 1];
			if (flag) {
				Q.push({ptr, ptr});
				dist[ptr][ptr] = 1;
				v[ptr] = {i, j};
				ind[i][j] = ptr++;
			}
		}
	}
	assert(ptr < M);

	for (int i = 0; i < ptr; i++) {
		short x = v[i][0], y = v[i][1];
		adj[0][ind[x][R[x][y]]].push_back(i);
		adj[1][ind[x][L[x][y]]].push_back(i);
		adj[2][ind[D[x][y]][y]].push_back(i);
		adj[3][ind[U[x][y]][y]].push_back(i);
	}

	while (Q.size()) {
		auto a = Q.front();
		Q.pop();
		int d = dist[a[0]][a[1]];

		auto check = [&](short x, short y) {
			OK(x, y);
			if (dist[x][y]) return;
			dist[x][y] = d + 1;
			Q.push({x, y});
		};
		for (short i = 0; i < 4; i++) {
			for (auto b: adj[i][a[0]]) {
				for (auto c: adj[i][a[1]]) {
					check(b, c);
				}
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> k;
	for (short i = 0; i < k; i++) {
		short r, c; cin >> r >> c;
		r--, c--;
		X[r][c] = true;
	}
	for (short i = 0; i < n; i++) {
		L[i][0] = 0;
		for (short j = 1; j < m; j++) {
			if (X[i][j - 1]) L[i][j] = j;
			else L[i][j] = L[i][j - 1];
		}
	}
	for (short i = 0; i < n; i++) {
		R[i][m - 1] = m - 1;
		for (short j = m - 2; j >= 0; j--) {
			if (X[i][j + 1]) R[i][j] = j;
			else R[i][j] = R[i][j + 1];
		}
	}
	for (short j = 0; j < m; j++) {
		U[0][j] = 0;
		for (short i = 1; i < n; i++) {
			if (X[i - 1][j]) U[i][j] = i;
			else U[i][j] = U[i - 1][j];
		}
	}
	for (short j = 0; j < m; j++) {
		D[n - 1][j] = n - 1;
		for (short i = n - 2; i >= 0; i--) {
			if (X[i + 1][j]) D[i][j] = i;
			else D[i][j] = D[i + 1][j];
		}
	}
	bfs();

	int q;
	cin >> q;
	while (q--) {
		short r1, r2, c1, c2; 
		int ans = 1 << 30;
		cin >> r1 >> c1 >> r2 >> c2;
		r1--, r2--, c1--, c2--;

		if (r1 == r2 && c1 == c2) {
			cout << "0\n";
			continue;
		}

		auto check = [&](short x, short y) {
			OK(x, y);
			if (!x || !dist[x][y]) return;
			ans = min(ans, dist[x][y]);
		};

		check(ind[r1][R[r1][c1]], ind[r2][R[r2][c2]]);
		check(ind[r1][L[r1][c1]], ind[r2][L[r2][c2]]);
		check(ind[D[r1][c1]][c1], ind[D[r2][c2]][c2]);
		check(ind[U[r1][c1]][c1], ind[U[r2][c2]][c2]);

		cout << (ans == (1 << 30) ? -1 : ans) << '\n';
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید

