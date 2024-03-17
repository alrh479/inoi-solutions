#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e6 + 50;

int pw(int a, int b) {
	int re = 1;
	while (b) {
		if (b & 1) re *= a;
		a *= a;
	}
	return re;
}
int a[N], n, m, re[N];

void solve(int l, int r, long long S, int id, vector<array<int, 2>> &v) {
	if (l == r) {
		S %= m;
		if (S < 0) S += m;
		v.push_back({S, id});
		return;
	}
	id *= 3;
	solve(l + 1, r, S + a[l], id + 1, v);
	solve(l + 1, r, S - a[l], id + 2, v);
	solve(l + 1, r, S, id, v);
}

void print(int mask1, int mask2) {
	for (int x = min(n, 15) - 1; x >= 0; x--, mask1 /= 3) {
		re[x] = mask1 % 3;
	}
	for (int y = min(n, 30) - 1; y >= min(n, 15); y--, mask2 /= 3) {
		re[y] = mask2 % 3;
	}
	cout << "alhamdolellah\n";
	for (int i = 0; i < n; i++)
		cout << re[i] << ' ';
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];	
	}

	vector<array<int, 2>> v1, v2;
	v1.reserve(14348908); //3^15 + 1
	v2.reserve(14348908);

	solve(0, min(n, 15), 0, 0, v1);
	solve(min(n, 15), min(n, 30), 0, 0, v2);

	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	shuffle(v1.begin(), v1.end(), rng);
	sort(v2.begin(), v2.end());

	for (auto u: v1) {
		int needed = (m - u[0]) % m;
		auto lw = upper_bound(v2.begin(), v2.end(), array<int, 2>{needed + 1, -1}) - v2.begin();
		if (lw == 0) continue;
		lw--;
		if (v2[lw][0] == needed && (u[1] || v2[lw][1])) {
			print(u[1], v2[lw][1]);
			return 0;
		}
	}
	cout << "laelahaellallah\n";
	return 0;
}
//به زآن که فروشند چه خواهند خرید
