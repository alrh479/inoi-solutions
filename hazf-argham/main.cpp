#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 4e5 + 5;
int T[20][10];

int lg(int x) {
	int cnt = 0;
	while (x) x /= 10, cnt++;
	return cnt;
}
vector<uint8_t> fac(int x) {
	vector<uint8_t> v;
	while (x) {
		int r = x % 10;
		x /= 10;
		v.push_back(r);
	}
	return v;
}

void fill_T(int x) {
	fill(T[0], T[0] + 10, -1);
	for (int i = 0; i < 19; i++) {
		int r = x % 10;
		x /= 10;
		T[i][r] = i;
		copy(T[i], T[i] + 10, T[i + 1]);
	}
}
int not_same_cnt(int x, int l, int t = 19) {
	int re = 0;
	for (int i = 1; i <= l; i++) {
		assert(t >= 0);
		for (int j = 0; j < 10; j++) {
			if (T[t][j] + i >= l) {
				t = T[t][j] - 1;
				re = re * 10 + j;
				break;
			}
		}
	}
	return re;
}
int same_cnt(int A, int x) {
	int t = 19, l = lg(x), now = 0, re = A;
	for (int i = 1; i <= l; i++) {
		if (t < 0) return re;
		int r = x % 10;
		for (int j = r + 1; j < 10; j++) {
			if (T[t][j] + i >= l) {
				re = min(re, (now * 10 + j) * pw[l - i + 1] + not_same_cnt(x, l - i, T[t][j] - 1);
			}
		}
		now = now * 10 + r;
		t = T[t][r] - 1;
	}
	return x; //x was build within A
}

int lower_bound(int A, int x) {
	if (A < x) return -1;
	int l = lg(x);
	fill_T(A);
	return min(same_cnt(A, x), not_same_cnt(A, l + 1));
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);

	return 0;
}
//نرو
