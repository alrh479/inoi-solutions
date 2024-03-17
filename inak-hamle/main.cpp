#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 750;
const int dx[] = {-1, +1, 0, 0};
const int dy[] = {0, 0, -1, +1};
const string ans[] = {"NO\n", "YES\n"};

bitset<N> mark[N];
int t[N][N], dist_D[N][N], dist_S[N][N], n, m;
array<int, 2> P, D, S;
char c[N][N];

void bfs_D() {
	queue<array<int, 2>> Q;
	Q.push(D);
	while (Q.size()) {
		auto a = Q.front();
		Q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a[0] + dx[i];
			int ny = a[1] + dy[i];
			if (nx < 0 || ny < 0 || nx >= n || ny >= m || c[nx][ny] == 'B' || mark[nx][ny]) continue;
			mark[nx][ny] = true;
			Q.push({nx, ny});
			t[nx][ny] = t[a[0]][a[1]] + 1;
		}
	}
}

void create_dist_D() {
	for (int i = 0; i < n; i++) {
		int L = 0, R = 0;
		while (L < m) {
			int mn = INF;
			while (L < m && c[i][L] == 'B') L++;
			if (L == m) break;
			R = L;
			while (R < m && c[i][R] != 'B') {
				mn = min(t[i][R], mn);
				R++;
			}
			while (L < R)
				dist_D[i][L++] = mn;
		}
	}

	for (int i = 0; i < m; i++) {
		int L = 0, R = 0;
		while (L < n) {
			int mn = INF;
			while (L < n && c[L][i] == 'B') L++;
			if (L == n) break;
			R = L;
			while (R < n && c[R][i] != 'B') {
				mn = min(t[R][i], mn);
				R++;
			}
			while (L < R) {
				dist_D[L][i] = min(dist_D[L][i], mn);
				L++;
			}
		}
	}
}

void bfs() {
	for (int i = 0; i < N; i++) mark[i] = 0;

	queue<array<int, 2>> Q;
	Q.push(S);
	while (Q.size()) {
		auto a = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = a[0] + dx[i];
			int ny = a[1] + dy[i];
			if (nx < 0 || ny < 0 || nx >= n || ny >= m || c[nx][ny] == 'B' || mark[nx][ny] || dist_S[a[0]][a[1]] + 1 >= dist_D[nx][ny]) continue;
			mark[nx][ny] = true;
			Q.push({nx, ny});
			dist_S[nx][ny] = dist_S[a[0]][a[1]] + 1;
		}
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> c[i][j];
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if (c[i][j] == 'S')
			S = {i, j};
		else if (c[i][j] == 'D')
			D = {i, j};
		else if (c[i][j] == 'P')
			P = {i, j};
	}
	bfs_D();
	create_dist_D();
	bfs();
	cout << ans[mark[P[0]][P[1]]];
	return 0;
}
//به زآن که فروشند چه خواهند خرید
