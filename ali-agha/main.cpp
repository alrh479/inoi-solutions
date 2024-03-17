#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e6 + 50;
const int MX = 14348907 + 5;
int a[N], n, m, re[N];
vector<pair<int, int>> v;

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

void solve1(int l, int r, long long S, int id) {
	if (l == r) {
		S %= m;
		if (S < 0) S += m;

		int needed = m - S;
		if (needed == m) needed -= m;

		auto it = lower_bound(v.begin(), v.end(), make_pair(needed, -1));
		if (it == v.end() || it->first != needed) return;
		int x = it->second;
		if (id || x) {
			print(id, x);
			exit(0);
		}
		return;
	}
	id *= 3;
	solve1(l + 1, r, S, id);
	solve1(l + 1, r, S - a[l], id + 2);
	solve1(l + 1, r, S + a[l], id + 1);
}
void solve2(int l, int r, long long S, int id) {
	if (l == r) {
		S %= m;
		if (S < 0) S += m;
		v.emplace_back(S, id);
		return;
	}
	id *= 3;
	solve2(l + 1, r, S, id);
	solve2(l + 1, r, S + a[l], id + 1);
	solve2(l + 1, r, S - a[l], id + 2);
}


signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];	
	}
	v.reserve(MX);
	solve2(min(n, 15), min(n, 30), 0, 0);
	sort(v.begin(), v.end());

	if (v.size() >= 2 && v[1].first == 0) 
		v.erase(v.begin());

	solve1(0, min(n, 15), 0, 0);

	cout << "laelahaellallah\n";
	return 0;
}
//به زآن که فروشند چه خواهند خرید

