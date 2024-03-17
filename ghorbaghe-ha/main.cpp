#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 127;
const int M = 1e9 + 7;
int n, k, p;

int T[N][N], re[N][N], tmp[N][N];

void mult(int a[][N], int b[][N], int c[][N]) {
	memset(tmp, 0, sizeof tmp);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				tmp[i][j] += a[i][k] * b[k][j] % M;

	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) c[i][j] = tmp[i][j] % M;
}

void pw(int a[][N], int b) {
	for (int i = 0; i < N; i++) re[i][i] = 1;

	while (b) {
		if (b & 1) mult(re, a, re);
		mult(a, a, a);
		b >>= 1;
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k >> p;
	vector<vector<int>> v;
	for (int a = 0; a <= 0; a++) { ///////:(
		if (k == 1) v.push_back({a});
		else for (int b = a + 1; b < p; b++) {
			if (k == 2) v.push_back({a, b});
			else for (int c = b + 1; c < p; c++) {
				if (k == 3) v.push_back({a, b, c});
				else for (int d = c + 1; d < p; d++) {
					if (k == 4) v.push_back({a, b, c, d});
					else for (int e = d + 1; e < p; e++) {
						if (k == 5) v.push_back({a, b, c, d, e});
						else for (int f = e + 1; f < p; f++) {
							if (k == 6) v.push_back({a, b, c, d, e, f});
							else for (int g = f + 1; g < p; g++) {
								if (k == 7) v.push_back({a, b, c, d, e, f, g});
								else for (int h = g + 1; h < p; h++) {
									if (k == 8) v.push_back({a, b, c, d, e, f, g, h});
									else for (int i = h + 1; i < p; i++) {
										if (k == 9) v.push_back({a, b, c, d, e, f, g, h, i});
										for (int j = i + 1; j < p; j++) {
											if (k == 10) v.push_back({a, b, c, d, e, f, g, h, i, j});
											else assert(false);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			vector<int> t = v[i];
			int mx = *max_element(t.begin(), t.end());
			t[j] = mx + 1;
			sort(t.begin(), t.end());
			int mn = t[0];
			if (mn) for (auto &u: t) u -= mn;

			int ind = lower_bound(v.begin(), v.end(), t) - v.begin();
			T[i][ind] += ind != v.size() && v[ind] == t;
		}
	}
	pw(T, n - k);
	cout << re[0][0] << '\n';

	return 0;
}
//به زآن که فروشند چه خواهند خرید
