#include "bits/stdc++.h"
#define int long long
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
const long long INF = 1ll << 60;
const int SQ = 200;
const int SQ2 = 500 + 2;
const int N = SQ * SQ2;
int n, a[N], b[N], X[N];

struct block {
	int l, delta, ps[SQ];
	array<int, 2> sort_X[SQ];

	void init() {
		for (int i = l; i < l + SQ; i++) sort_X[i - l] = {0, i}; //{0, i}
	}

	void apply() {
		for (int i = l; i < l + SQ; i++) X[i] += delta;
		delta = 0;
		for (int i = l; i < l + SQ; i++) sort_X[i - l] = {X[i], i};
		sort(sort_X, sort_X + SQ);
		partial_sum(sort_X, sort_X + SQ, ps);
	}
} B[SQ2];

void add(int l, const int d) {
	int tl = l;
	while (l < N) {
		if (l % SQ == 0) {
			B[l / SQ].delta += d;
			l += SQ;
		}
		else {
			X[l] += d;
			l++;
		}
	}
	if (tl % SQ) {
		B[tl / SQ].apply();
	}
}
void get() {
	int ans = 0;
	FOR(i, 0, SQ2) {
		int d = B[i].delta;
		int ind = lower_bound(B[i].sort_X, B[i].sort_X + SQ, -d) - B[i].sort_X;
		ans += (ind ? -B[i].ps[ind - 1] - d * ind : 0);
		ans += (B[i].ps[SQ - 1] - (ind ? B[i].ps[ind - 1] : 0)) + d * (SQ - ind);
	}
	cout << ans << '\n';
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	FOR(i, 0, SQ2) B[i].l = i * SQ;

	cin >> n;
	FOR(i, 0, n) {
		cin >> a[i];
		add(a[i], +1);
	}
	FOR(i, 0, n) {
		cin >> b[i];
		add(b[i], -1);
	}
	int q; cin >> q;
	while (q--) {
		int idx, x; cin >> idx >> x; idx--;
		if (idx >= n) {
			idx -= n;
			add(b[idx], +1);
			b[idx] = x;
			add(b[idx], -1);
		}
		else {
			add(a[idx], -1);
			a[idx] = x;
			add(a[idx], +1);
		}
		get();
	}
	return 0;
}
//Reading this fills you with DETERMINATION
//09:45:03
