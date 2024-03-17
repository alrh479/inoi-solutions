#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 5e5 + 5;
char C[N];
int LC[N], n, H, V, q;

struct seg {
	int S[4 * N][2] = {};
	bitset<4 * N> flip;

	seg() {
		flip = 0;
	}

	void push(int v) {
		if (flip[v]) {
			flip[v << 1] = 1 ^ flip[v << 1];
			flip[v << 1 | 1] = 1 ^ flip[v << 1 | 1];
			swap(S[v << 1][0], S[v << 1][1]);
			swap(S[v << 1 | 1][0], S[v << 1 | 1][1]);

			flip[v] = false;
		}
	}

	void flip_range(int v, int l, int r, const int L, const int R) {
		if (R <= L || r <= L || R <= l) return;
		if (L <= l && r <= R) {
			flip[v] = flip[v] ^ 1;
			swap(S[v][0], S[v][1]);
			return;
		}
		push(v);
		int m = l + r >> 1;
		flip_range(v << 1, l, m, L, R);
		flip_range(v << 1 | 1, m, r, L, R);

		S[v][0] = S[v << 1][0] + S[v << 1 | 1][0];
		S[v][1] = S[v << 1][1] + S[v << 1 | 1][1];
	}

	void add(int v, int l, int r, const int ind, const int val) {
		if (l + 1 == r) {
			S[v][flip[v]] = val;
			return;
		}
		push(v);
		int m = l + r >> 1;
		if (ind < m) add(v << 1, l, m, ind, val);
		else add(v << 1 | 1, m, r, ind, val);

		S[v][0] = S[v << 1][0] + S[v << 1 | 1][0];
		S[v][1] = S[v << 1][1] + S[v << 1 | 1][1];
	}
	int get(int prty) {
		return S[1][prty];
	}
} vert, horz;

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> V >> H >> q;
	vector<int> dh{0, H}, dv{0, V};

	for (int i = 0; i < q; i++) {
		cin >> C[i] >> LC[i];
		if (C[i] == 'V')
			dv.push_back(LC[i]);
		else
			dh.push_back(LC[i]);
	}	
	sort(dh.begin(), dh.end());
	sort(dv.begin(), dv.end());

	vert.add(1, 0, dv.size(), 0, 0);
	vert.flip_range(1, 0, dv.size(), 1, dv.size());
	vert.add(1, 0, dv.size(), dv.size() - 1, V);

	horz.add(1, 0, dh.size(), 0, 0);
	horz.flip_range(1, 0, dh.size(), 1, dh.size());
	horz.add(1, 0, dh.size(), dh.size() - 1, H);

	int last[2] = {1, 1};

	for (int i = 0; i < q; i++) {
		if (C[i] == 'V') {
			int ind = lower_bound(dv.begin(), dv.end(), LC[i]) - dv.begin();
			vert.add(1, 0, dv.size(), ind, LC[i]);
			vert.flip_range(1, 0, dv.size(), ind + 1, dv.size());
			last[0] ^= 1;
		}
		else {
			int ind = lower_bound(dh.begin(), dh.end(), LC[i]) - dh.begin();
			horz.add(1, 0, dh.size(), ind, LC[i]);
			horz.flip_range(1, 0, dh.size(), ind + 1, dh.size());
			last[1] ^= 1;
		}
		int v[2] = {vert.get(0), vert.get(1)};
		int h[2] = {horz.get(0), horz.get(1)};

		int x = v[1] - v[0] + (!last[0] ? V : 0);
		int xp = V - x;

		int y = h[1] - h[0] + (!last[1] ? H : 0);
		int yp = H - y;

		int S = xp * yp + x * y;
		cout << max(S, V * H - S) << '\n';
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
