#include <stdio.h>

#define N 1000 + 5
int dist[N][N], x[N], cp[N], n;
long long ans;

long long solve(int l, int r) {
	if (r - l <= 1)
		return 0;
	int u = x[l];
	long long h = 0;
	for (int i = l + 1; i < r; i++)
		h = (h > dist[u][x[i]] ? h : dist[u][x[i]]);
	int ptr = l;
	for (int i = l + 1; i < r; i++) {
		if (dist[u][x[i]] == h)
			cp[ptr++] = x[i];
	}
	int m = ptr;
	cp[ptr++] = u;
	for (int i = l + 1; i < r; i++) {
		if (dist[u][x[i]] != h) {
			cp[ptr++] = x[i];
		}
	}
	for (int i = l; i < r; i++)
		x[i] = cp[i];
	ans += h - solve(l, m) - solve(m, r);
	return h >> 1;
}

signed main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &dist[i][j]);
	for (int i = 0; i < n; i++)
		x[i] = i;
	solve(0, n);
	printf("%lld", ans);
}
