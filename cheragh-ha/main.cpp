#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 5e5 + 5;
const int A = 30;
int S[2 * A * N], lz[2 * A * N], ptr = 1, XSRT[N], PX, a[N], b[N], x[N], lft[2 * A * N], rt[2 * A * N], n, q, H;
char c[N];

set<array<int, 2>> lamps[N];

void add_seg(int &v, int l, int r, const int L, const int R, const int d) {
	if (r <= L || R <= l) return;
	if (!v) {
		v = ++ptr;
		assert(ptr < 2 * A * N);
	}
	if (L <= l && r <= R) {
		lz[v] += d;
		S[v] += d * (r - l);
		return;
	}
	int m = l + r >> 1;
	add_seg(lft[v], l, m, L, R, d);
	add_seg(rt[v], m, r, L, R, d);
	S[v] = S[lft[v]] + S[rt[v]] + lz[v] * (r - l);
}

int get(int &v, int l, int r, const int L, const int R) {
	if (r <= L || R <= l || !v) return 0;
	if (L <= l && r <= R) return S[v];
	int m = l + r >> 1;
	return get(lft[v], l, m, L, R) + get(rt[v], m, r, L, R) + lz[v] * (min(R, r) - max(L, l));
}

void add(int l, int r, int d) {
	r++;
	if (r <= l || !d) return;
	add_seg(H, 0, 1 << A, l, r, d);
}

void add_lamp(int L, int R, const int idx) {
	auto &T = lamps[idx];
	auto it = T.lower_bound({L, -1});
	if (it != T.begin()) {
		it--;
		auto t = *it;
		if (t[1] >= L) {
			L = min(L, t[0]);
			R = max(R, t[1]);
			add(t[0], t[1], -1);
			T.erase(it);
			it = T.upper_bound(t);
		}
		else it++;
	}
	while (it != T.end() && (*it)[0] <= R) {
		auto t = *it;	
		add(t[0], t[1], -1);
		L = min(L, t[0]);
		R = max(R, t[1]);
		T.erase(it);
		it = T.upper_bound(t);
	}
	add(L, R, +1);
	T.insert({L, R});
}

void remove_lamp(int L, int R, const int idx) {
	auto &T = lamps[idx];
	auto it = T.lower_bound({L, -1});
	if (it != T.begin()) {
		it--;
		auto t = *it;
		if (t[1] >= L) {
			add(L, min(t[1], R), -1);
			T.erase(it);
			if (t[0] <= L - 1)
				T.insert({t[0], L - 1});
			if (t[1] >= R + 1)
				T.insert({R + 1, t[1]});
			it = T.upper_bound(t);
		}
		else it++;
	}
	while (it != T.end() && (*it)[1] <= R) {
		auto t = *it;	
		add(t[0], t[1], -1);
		T.erase(it);
		it = T.upper_bound(t);
	}
	if (it != T.end() && (*it)[0] <= R) {
		auto t = *it;	
		add(t[0], R, -1);
		T.erase(it);
		if (R + 1 <= t[1])
			T.insert({R + 1, t[1]});
	}
	//for (auto [l, r]: T) cout << l << ' ' << r << endl;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	for (int i = 0; i < q; i++) {
		cin >> c[i] >> a[i] >> b[i];
		if (c[i] != '?') {
			cin >> x[i];
			XSRT[PX++] = x[i];
		}
	}
	H = 1;
	sort(XSRT, XSRT + PX);
	PX = unique(XSRT, XSRT + PX) - XSRT;

	for (int i = 0; i < q; i++) if (c[i] != '?') x[i] = lower_bound(XSRT, XSRT + PX, x[i]) - XSRT;

	for (int i = 0; i < q; i++) {
		if (c[i] == '+') {
			add_lamp(a[i], b[i], x[i]);
		}
		else if (c[i] == '-') {
			remove_lamp(a[i], b[i], x[i]);
		}
		else {
			cout << get(H, 0, 1 << A, a[i], b[i] + 1) << '\n';
		}
	}

	return 0;
}
//نرو
