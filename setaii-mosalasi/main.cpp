#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
const int inv3 = 333333336;
const int inv2 = 500000004;
const int inv6 = 1ll * inv2 * inv3 % MOD;

long long C3(int n) {
	if (n <= 2)
		return 0;
	return 1ll * n * (n - 1) % MOD * (n - 2) % MOD * inv6 % MOD;
}
long long C2(int n) {
	if (n <= 1)
		return 0;
	return 1ll * n * (n - 1) % MOD * inv2 % MOD;
}

signed main() {
	int a[3];
	cin >> a[0] >> a[1] >> a[2];
	sort(a, a + 3);
	long long A, B, C;
	A = a[0], B = a[1], C = a[2];
	long long ans = A * B % MOD * C % MOD;
	ans -= C3(A + 1);
	ans %= MOD;

	ans -= C3(B + 1);
	ans %= MOD;

	ans += C3(B - A + 1);
	ans %= MOD;


	if (A < (C - B)) {
		ans -= B * ((C2(C - B + 1) - C2(C - B - A + 1)) % MOD) % MOD;
		ans %= MOD;
		ans -= A * C2(B) % MOD;
		ans %= MOD;
	}
	else {
		ans -= B * C2(C - B + 1) % MOD;
		ans %= MOD;
		ans -= (C - B) * C2(B) % MOD;
		ans %= MOD;
		ans -= C3(B + 1);
		ans %= MOD;
		ans += C3(B - (A - (C - B)) + 1);
		ans %= MOD;
	}
	ans %= MOD;
	ans += MOD;
	ans %= MOD;

	cout << ans;
}
