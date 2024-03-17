#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 40;
const int M = 1e9 + 7;
int p3[N], X[2 * N][2 * N], I[2 * N], R[2 * N], L[2 * N], a[2 * N][2 * N], ps[2 * N];

void add(int a[], int b[]) {
	for (int i = 0; i < N; i++) {
		a[i] += b[i];
		if (a[i] >= M) a[i] -= M;
	}
}

void F(int r, int t[]) {
	memset(t, 0, sizeof *t);
	int cnt = 0;
	for (int i = N - 1; i >= 0; i--) {
		int x = (r / p3[i]) % 3;
		for (int j = 0; j < x; j++) {
			add(t + cnt + (j == 1), X[i]);
		}
		cnt += x == 1;
	}
	t[cnt]++;
}
int G(int r) {
	memset(a, 0, sizeof a);
	memset(ps, 0, sizeof ps);
	int ptr = 0, ans = 0, cnt = 0;
	for (int i = N - 1; i >= 0; i--) {
		int x = (r / p3[i]) % 3;
		for (int j = 0; j < x; j++) {
			copy(X[i], X[i] + N, a[ptr] + cnt + (j == 1));
			ans += I[i];
			ptr++;
		}
		cnt += x == 1;
	}
	a[ptr][cnt] = 1;

	ans %= M;
	for (int i = ptr; i >= 0; i--) {
		for (int j = 1; j < N; j++) {
			ans += a[i][j] * ps[j - 1] % M;
		}
		for (int j = 1; j < N; j++) {
			a[i][j] += a[i][j - 1];
			if (a[i][j] >= M) a[i][j] -= M;
		}
		for (int j = 0; j < N; j++) {
			ps[j] += a[i][j];
			if (ps[j] >= M) ps[j] -= M;
		}
		ans %= M;
	}
	return ans % M;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	p3[0] = 1;
	for (int i = 1; i < N; i++)
		p3[i] = p3[i - 1] * 3ll;

	X[0][0] = 1;
	for (int i = 0; i + 1 < N; i++) {
		for (int j = 0; j < N; j++)
			X[i + 1][j] += 2ll * X[i][j];
		for (int j = 0; j + 1 < N; j++) 
			X[i + 1][j + 1] += X[i][j];
		for (int j = 0; j < N; j++) X[i + 1][j] %= M;
	}

	for (int i = 0; i + 1 < N; i++) {
		I[i + 1] = 3ll * I[i] % M;
		for (int j = 0; j < N; j++)  //[0, 2]
			for (int k = 0; k < j; k++)
				I[i + 1] += X[i][j] * X[i][k] % M;
		I[i + 1] %= M;
		for (int j = 0; j < N; j++) //[0, 1]
			for (int k = 1; k < j; k++)
				I[i + 1] += X[i][j] * X[i][k - 1] % M;
		I[i + 1] %= M;
		for (int j = 1; j < N; j++) //[1, 2]
			for (int k = 0; k < j; k++)
				I[i + 1] += X[i][j - 1] * X[i][k] % M;
		I[i + 1] %= M;
	}
	int q; cin >> q;

	while (q--) {
		int l, r;
		cin >> l >> r;
		F(r, R);
		F(l - 1, L);
		for (int i = 0; i < N; i++) {
			R[i] -= L[i];
			R[i] %= M;
		}


		int ans = G(r) - G(l - 1);
		ans %= M;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < i; j++)
				ans -= L[i] * R[j] % M;
		ans %= M;
		ans += M;
		cout << ans % M << '\n';
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
