#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

map<int, int> cnt;
int final_c[N], n, m, f[N], inv[N], invf[N];
vector<int> dv[N];

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
	return 1ll * a / gcd(a, b) * b;
}

int bs(long long L, long long c, long long sum) {
	int l = 0, r = n + 1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		long long ans = 1ll * mid * mid * L + 2ll * mid * sum;
		if (ans > c)
			r = mid;
		else
			l = mid;
	}
	assert(1ll * l * l * L + 2ll * l * sum == c);
	return l;
}
int C(int n, int r) {
	return 1ll * f[n] * invf[r] % MOD * invf[n - r] % MOD;
}

void solve() {
	vector<int> org;
	for (int i = 1; i <= n; i++) {
		//count cycle of I
		if (!cnt.count(i) || cnt[i] == 0)
			continue;
		assert(cnt[i] > 0);

		long long sum = 0;
		for (int d: dv[i])
			sum += 1ll * final_c[d] * d;
		final_c[i] = bs(i, cnt[i], sum);

		if (!final_c[i])
			continue;
		
		for (auto j: org)
			cnt[lcm(i, j)] -= 2ll * gcd(i, j) * final_c[j] * final_c[i];

		org.push_back(i);
	}

	cout << org.size() << '\n';
	for (auto u: org)
		cout << final_c[u] << ' ' << u << '\n';
	int val = 1;
	for (auto u: org)
		for (int i = 0; i < final_c[u]; i++) {
			val = 1ll * val * C(n, u) % MOD * f[u - 1] % MOD;
			n -= u;
		}
	cout << val << '\n';
}

signed main() {

	for (int i = 1; i < N; i++)
		for (int j = i + i; j < N; j += i)
			dv[j].push_back(i);
	f[0] = f[1] = 1;
	inv[1] = 1;
	invf[0] = invf[1] = 1;
	for (int i = 2; i < N; i++) {
		f[i] = (f[i - 1] * i) % MOD;
		inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
		invf[i] = 1ll * inv[i] * invf[i - 1] % MOD;
	}

	cin >> m >> n;
	while (m--) {
		int lt, ct;
		cin >> ct >> lt;
		cnt[lt] += ct;
	}

	solve();
}
