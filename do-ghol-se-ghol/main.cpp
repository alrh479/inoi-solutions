#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1000;
const int M = 10;
const int MAX_SIZE = 1e5;
static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();

struct custom_hash {
    size_t operator()(uint64_t x) const {
        x ^= FIXED_RANDOM;
        return x ^ (x >> 16);
    }
};
using hash_map = unordered_multiset<int, custom_hash>;

struct chash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	size_t operator()(const vector<int> &a) const {
		int x = 0;
		for (auto u: a) x ^= splitmix64(u + FIXED_RANDOM);
		return x ^ (x >> 16);
	}
};
using hash_ = unordered_map<vector<int>, int, chash>;

int a[M], b[M], n, m;

void bfs(int a[], int n, hash_ &mp) {
	vector<int> st(a, a + n);
	sort(st.begin(), st.end());

	mp[st] = 0;
	queue<vector<int>> Q;
	Q.push(st);

	while (Q.size()) {
		auto v = Q.front();
		Q.pop();
		int d = mp[v];

		for (int i = 0; i < v.size(); i++) {
			for (int j = i + 1; j < v.size(); j++) {
				vector<int> t;
				t.reserve(v.size());
				for (int k = 0; k < v.size(); k++) if (k != i && k != j) {
					t.push_back(v[k]);
				}
				t.insert(upper_bound(t.begin(), t.end(), v[i] + v[j]), v[i] + v[j]);

				if (!mp.count(t)) {
					mp[t] = d + 1;
					Q.push(t);
				}
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];

	hash_ mp1, mp2;
	bfs(a, n, mp1);
	bfs(b, m, mp2);
	
	int mn = n + m - 2;
	for (auto p: mp1) {
		if (mp2.count(p.first)) {
			mn = min(mn, p.second + mp2[p.first]);
		}
	}
	cout << mn << '\n';

	return 0;
}
//به زآن که فروشند چه خواهند خرید
