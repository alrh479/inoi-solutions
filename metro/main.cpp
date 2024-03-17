#include "bits/stdc++.h"
using namespace std;
#define int long long
const long long INF = 1ll << 50;
const int N = 5e5 + 5;
int m, ptr;
vector<int> ls, rs;
array<int, 2> a[N], b[N];

bool check(int n) {
	for (int i = 0; i < m; i++) if (a[i][1] - n + 1 < a[i][0]) return false;
	vector<int> crs = rs;
	for (auto &u: crs) u -= n - 1;
	vector<int> v(ls.size() + rs.size());
	merge(ls.begin(), ls.end(), crs.begin(), crs.end(), v.begin());

	v.resize(unique(v.begin(), v.end()) - v.begin());

	queue<array<int, 2>> Q;
	Q.push({-INF, -INF});

	int ptr = 0;

	for (int i = 0; i + 1 < v.size(); i++) {
		if (Q.empty()) return false;
		int pos = v[i];
		int nxpos = v[i + 1];

		int mn = Q.front()[0];
		if (mn + n - 1 <= nxpos) Q.push({max(pos, mn + n - 1), nxpos});

		while (ptr < m && a[ptr][1] - n + 1 < nxpos) ptr++;
		
		while (ptr < m && a[ptr][1] - n + 1 == nxpos) {
			while (Q.size() && Q.front()[0] < a[ptr][0]) {
				if (Q.front()[1] < a[ptr][0]) Q.pop();
				else Q.front()[0] = a[ptr][0];
			}
			ptr++;
		}
	}
	return !Q.empty();

}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> a[i][0] >> a[i][1];
		a[i][1]--;
	}
	sort(a, a + m, [&](const auto &x, const auto &y) {if (x[1] != y[1]) return x[1] < y[1]; return x[0] > y[0];});

	ls.resize(m), rs.resize(m);
	for (int i = 0; i < m; i++) 
		ls[i] = a[i][0], rs[i] = a[i][1];
	sort(ls.begin(), ls.end());
	sort(rs.begin(), rs.end());
	ls.resize(unique(ls.begin(), ls.end()) - ls.begin());
	rs.resize(unique(rs.begin(), rs.end()) - rs.begin());

	int lo = 1, hi = 1 << 30;
	while (hi - lo > 1) {
		int m = lo + hi >> 1;
		if (check(m)) lo = m;
		else hi = m;
	}
	cout << lo << '\n';
	return 0;
}
