#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e6 + 5;
int B[33][3], nxt[N][33][3];

int get(int l, int r, int cnt[]) {
	if (!l) return cnt[r];
	return cnt[r] - cnt[l - 1];
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];

	for (int i = 0; i < m; i++) {
		for (int x = 0; x < 32; x++) {
			bool o = b[i] >> x & 1;
			B[x][o]++;
		}
	}
	return 0;
}
//نرو
//سوپر حمالی 
//:|

