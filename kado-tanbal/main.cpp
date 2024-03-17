#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e5 + 50;
const int M = 3.5e4;
bitset<M> pr;
vector<int> primes, num, cn;
struct custom_hash {
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        x ^= FIXED_RANDOM;
        return x ^ (x >> 16);
    }
};
gp_hash_table<int, vector<int>, custom_hash> adj;
gp_hash_table<int, bool, custom_hash> mark;
int a[N], n;

void dfs(int v) {
	mark[v] = true;
	for (auto u: adj[v]) if (!mark[u]) 
		dfs(u);
	if (v < N)
		cn.push_back(v), num.push_back(a[v]);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	for (int i = 2; i < M; i++) if (!pr[i]) {
		primes.push_back(i);	
		for (int j = i + i; j < M; j += i)
			pr[j] = true;
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		int ta = a[i];
		for (auto p: primes) if (ta % p == 0) {
			while (ta % p == 0) ta /= p;
			adj[i].push_back(p + N);
			adj[p + N].push_back(i);
		}
		if (ta != 1) {
			adj[i].push_back(ta + N);
			adj[ta + N].push_back(i);
		}
	}

	for (int i = 0; i < n; i++) if (!mark[i]) {
		cn.clear();
		num.clear();
		dfs(i);
		sort(cn.begin(), cn.end());
		sort(num.begin(), num.end());
		for (int i = 0; i < cn.size(); i++)
			a[cn[i]] = num[i];
	}
	for (int i = 0; i < n; i++)
		cout << a[i] << ' ';

	return 0;
}
//به زآن که فروشند چه خواهند خرید
//منطقیه...
