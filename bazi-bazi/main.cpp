#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 5e5 + 5;
int ps[N], a[N], n;

int sum(int l, int r) {
	l %= n, r %= n;
	if (l < 0) l += n;
	if (r < 0) r += n;

	if (r < l)
		return ps[r] + ps[n - 1] - ps[l - 1];
	else
		return ps[r] - (l ? ps[l - 1] : 0);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	partial_sum(a, a + n, ps);
	multiset<int> S;

	int hf = (n + 1) / 2;
	for (int i = 0; i < hf; i++) {
		int l = -hf + 1 + i;
		S.insert(sum(l, l + hf - 1));
	}

	int mx = *S.begin();
	for (int i = 1; i < n; i++) {
		S.erase(S.find(sum(i - hf, i - 1)));
		S.insert(sum(i, i + hf - 1));
		mx = max(mx, *S.begin());
	}
	cout << mx << '\n';

	return 0;
}
//به زآن که فروشند چه خواهند خرید
