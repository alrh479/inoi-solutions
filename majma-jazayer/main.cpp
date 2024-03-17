#include "bits/stdc++.h"
using namespace std;
const int INF = 1 << 30;
const int N = 2005;
const int d[] = {-1, +1};
vector<array<int, 2>> adj[N][N];
int n, m, dist[N][N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	int x1, x2, y1, y2;
	cin >> x1 >> y1 >> x2 >> y2;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c; cin >> c;
			if (c == '\\') {
				adj[i][j].push_back({i + 1, j + 1});
				adj[i + 1][j + 1].push_back({i, j});
			}
			else {
				adj[1 + i][j].push_back({i, j + 1});
				adj[i][1 + j].push_back({i + 1, j});
			}
		}
	}

	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dist[i][j] = INF;
	dist[x1][y1] = 0;

	deque<array<int, 2>> Q;
	Q.push_front({x1, y1});

	while (Q.size()) {
		auto a = Q.front();
		Q.pop_front();

		for (auto b: adj[a[0]][a[1]]) {
			int nx = b[0];
			int ny = b[1];
			if (nx < 0 || nx > n || ny < 0 || ny > m || dist[nx][ny] <= dist[a[0]][a[1]]) continue;
			Q.push_front({nx, ny});
			dist[nx][ny] = dist[a[0]][a[1]];
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				int nx = a[0] + d[i];
				int ny = a[1] + d[j];
				if (nx < 0 || nx > n || ny < 0 || ny > m || dist[nx][ny] <= dist[a[0]][a[1]] + 1) continue;
				Q.push_back({nx, ny});
				dist[nx][ny] = dist[a[0]][a[1]] + 1;
			}
		}
	}
	cout << (dist[x2][y2] == INF ? -1 : dist[x2][y2]) << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
