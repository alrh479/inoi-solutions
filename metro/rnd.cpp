#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 5e5 + 5;
const int X = 15;

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	srand(time(0));
	int M = 5;
	cout << M << '\n';
	for (int i = 0; i < M; i++) {
		int L = rand() % X, R = rand() % X;
		if (R < L) swap(L, R);
		R++;
		cout << L << ' ' << R << '\n';
	}
	return 0;
}
//به زآن که فروشند چه خواهند خرید
