#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e6 + 5;
int a[N], n;

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	int last = 0, re = 1, en = n - a[n];
	for (int i = 1; i <= en; i++) {
		if (last <= i - a[i]) {
			re++;
			last = i;
		}
	}
	cout << re << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
