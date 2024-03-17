#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 2e5 + 5;
int a[N], ps[N], n, m;

int get(int l, int r) {
	return ps[r] - ps[l - 1];
}
array<int, 2> I[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			int x; cin >> x;
			a[i] = x & 1;
		}
		for (int i = 1; i <= n; i++) ps[i] = a[i] + ps[i - 1];
		cin >> m;
		for (int i = 0; i < m; i++) {
			cin >> I[i][0] >> I[i][1];
		}
		sort(I, I + m, [](const array<int, 2> &a, const array<int, 2> &b) {return a[1] - a[0] < b[1] - b[0];});
		m = unique(I, I + m) - I;
		set<array<int, 2>> S;
		map<array<int, 2>, int> mp;
		int re = get(1, n);
		for (int i = 0; i < m; i++) {
			int l = I[i][0], r = I[i][1], cnt = r - l + 1, s = get(l, r), mx = 0, t = max(s, cnt - s);
			for (auto it = S.lower_bound({l, -1}); it != S.end() && (*it)[1] <= r; it = S.lower_bound({l, -1})) {
				int lp = (*it)[0];
				int rp = (*it)[1];
				s -= get(lp, rp);
				cnt -= rp - lp + 1;
				S.erase(it);
				t = max({t, mp[*it] + s, mp[*it] + cnt - s});
				cnt += rp - lp + 1;
				s += get(lp, rp);
			}
			mp[I[i]] = t;
			S.insert(I[i]);
			re = max(re, t + get(1, l - 1) + get(r + 1, n));
		}
		cout << re << '\n';
	}
	return 0;
}
//نرو
