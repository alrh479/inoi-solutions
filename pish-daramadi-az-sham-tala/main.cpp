#include "bits/stdc++.h"
using namespace std;
#define int long long
const int INF = 1ll << 55;
long long p, v, n;

int mult(int a, int b) {
	int A = __lg(a), B = __lg(b);
	if (A + B >= 55) return INF;
	return a * b;
}

int pw(int a, int b) {
	int re = 1;
	for (; b; b >>= 1, a = mult(a, a)) if (b & 1) re = mult(re, a);
	return re;
}
int sqrt(int a, const int x) {
	int l = 0, r = a;
	while (r - l > 1) {
		int m = l + r >> 1;
		if (pw(m, x) > a) r = m;
		else l = m;
	}
	return l;
}
int solve(int I) {
	int s = sqrt(n, I), P = pw(s, I), sum = s * I;
	while (P < n) {
		sum++;
		P /= s;
		P *= s + 1;
	}
	return sum;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> p >> v;
	if (n == 1) {
		cout << 0;
		return 0;
	}
	int cost = INF;
	for (int i = 1; i <= 50; i++) {
		if (i * v >= cost) break;
		int J = solve(i);	
		cost = min(cost, mult(J, p) + mult(i, v));
	}
	cout << (long long) cost << endl;
	return 0;
}
//الان میتونی بری
/*P1 * P2 * P3 * ---- * Pi >= N
P1 + P2 + P3 + P4 + P5 + ... + Pi = J
cost is IV + JP
A B => WLOG A < B --> if B - A >= 2 --> (A + 1)(B - 1) yeilds bigger
Pk is N^(1 / I)
*/
