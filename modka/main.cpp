#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const long long INF = 1ll << 59;

long long c[N][N], cur[N][N], w[N][N];
int n, m, k;

void operate(long long a[][N], long long b[][N]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = INF;
			for (int k = 0; k < n; k++) {
				c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
			}
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = c[i][j];
}
void pr(long long a[][N]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == INF) cout << "-1 ";
			else cout << a[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << "===\n";
}
void pw(int k) {
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			cur[i][j] = cur[j][i] = INF;
	while (k) {
		if (k % 2)
			operate(cur, w); //cur = cur op w
		operate(w, w); //w = w op w
		k /= 2;
	}
}

void solve() {
	pw(k);
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cur[i][j] = min(cur[i][j], cur[i][k] + cur[k][j]);
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			w[i][j] = INF;

	while (m--) {
		int u, v, tw;
		cin >> u >> v >> tw;
		u--, v--;
		w[u][v] = tw;
	}

	solve();

	if (cur[0][n - 1] == INF)
		cout << "-1\n";
	else
		cout << cur[0][n - 1] << '\n';
	return 0;
}
