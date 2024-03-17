#include "bits/stdc++.h"
using namespace std;
const long long INF = 1 << 30;
const int N = 5e5 + 5;
int m;
int L[1000], l[N], r[N];

bool check(int n) {
	for (int i = 0; i < m; i++) if (r[i] - n + 1 < l[i]) return false;

	queue<int> Q;
	Q.push(-1);

	for (int i = 0; i <= 500; i++) {
		int nwR = i + n - 1;

		if (Q.empty()) return false;

		int mn = Q.front();
		if (mn == -1 || mn <= i - n + 1) Q.push(i);

		if (nwR <= 500 && L[nwR] != -1) {
			while (Q.size() && Q.front() < L[nwR]) Q.pop();
		}
	}
	return !Q.empty();
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	memset(L, -1, sizeof L);

	cin >> m;
	if (m > 500) return 0;
	for (int i = 0; i < m; i++) {
		cin >> l[i] >> r[i]; r[i]--;
		L[r[i]] = max(L[r[i]], l[i]);
	}

	int lo = 1, hi = 1 << 30;
	while (hi - lo > 1) {
		int m = lo + hi >> 1;
		if (check(m)) lo = m;
		else hi = m;
	}
	cout << lo << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
