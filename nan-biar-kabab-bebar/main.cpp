#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 2e5 + 5;
bitset<N> win;
int a[N], n, l[N], r[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	vector<array<int, 3>> L, R;
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
		L.push_back({l[i], r[i], i});
		R.push_back({r[i], l[i], i});
	}
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());
	int mnR, mnL;

	if (R.back()[0] > L.back()[0]) {
		mnR = R.back()[0];
		mnL = R.back()[1];
		win[R.back()[2]] = true;
		R.pop_back();
	}
	else {
		mnR = L.back()[1];
		mnL = L.back()[0];
		win[L.back()[2]] = true;
		L.pop_back();
	}

	while (L.size() || R.size()) {
		if (L.size() && L.back()[0] > mnR) {
			mnL = min(mnL, L.back()[0]);
			mnR = min(mnR, L.back()[1]);
			win[L.back()[2]] = true;
			L.pop_back();
		}
		else if (R.size() && R.back()[0] > mnL) {
			mnR = min(mnR, R.back()[0]);
			mnL = min(mnL, R.back()[1]);
			win[R.back()[2]] = true;
			R.pop_back();
		}
		else break;
	}
	for (int i = 0; i < n; i++)
		cout << win[i];

	return 0;
}
//به زآن که فروشند چه خواهند خرید
