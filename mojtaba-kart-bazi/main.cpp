#include "bits/stdc++.h"
#define int long long
using namespace std;
const long long INF = 1ll << 60;
const int N = 6e5 + 5;
const int L = 20;
int suf[N];
int a[N], b[N], n, k, t[N], MN[N], MX[N], T[L][N];
array<int, 2> srt_t[N];
vector<int> d;
vector<array<int, 2>> V[N], non;

bitset<N> bit;
bool kol = 0;
void add(int r) {
	kol ^= 1;
	r++;
	for (; r < N; r += r & -r) bit[r] = bit[r] ^ 1;
}
bool get(int r) {
	r++;
	bool re = 0;
	for (; r; r -= r & -r) re ^= bit[r];
	return re;
}
bool get_suf(int r) {
	return kol ^ get(r - 1);
}

int rmq(int l, int r) {
	int t = __lg(r - l);
	return max(T[t][l], T[t][r - (1 << t)]);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
		d.push_back(a[i]);
		d.push_back(b[i]);
		MN[i] = min(a[i], b[i]);
		MX[i] = max(a[i], b[i]);
	}
	for (int i = 0; i < k; i++) {
		cin >> t[i];
		d.push_back(t[i]);
	}
	sort(d.begin(), d.end());
	d.resize(unique(d.begin(), d.end()) - d.begin());

	for (int i = 0; i < n; i++) 
		a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin(),
		b[i] = lower_bound(d.begin(), d.end(), b[i]) - d.begin();
	for (int i = 0; i < k; i++)
		t[i] = lower_bound(d.begin(), d.end(), t[i]) - d.begin();

	for (int i = 0; i < k; i++)
		srt_t[i] = {t[i], i};
	sort(srt_t, srt_t + k);

	for (int i = 0; i < k; i++)
		T[0][i] = srt_t[i][1];

	for (int l = 0; l < L - 1; l++)
		for (int i = 0; i + (2 << l) <= k; i++)
			T[l + 1][i] = max(T[l][i], T[l][i + (1 << l)]);
	
	for (int i = 0; i < n; i++) {
		int mn = min(a[i], b[i]), l, mx = max(a[i], b[i]);
		int ind1 = lower_bound(srt_t, srt_t + k, array<int, 2>{mn, -1}) - srt_t;
		int ind2 = upper_bound(srt_t, srt_t + k, array<int, 2>{mx, -1}) - srt_t;
		if (ind1 >= ind2) l = -1;
		else l = rmq(ind1, ind2);
		//cout << "LATEST " << l + 1 << '\n';
		int q;
		if (l == -1) {
			q = (a[i] <= b[i]);
			non.push_back({q, i});
		}
		else {
			q = 0;
			V[l].push_back({q, i});
		}
	}

	int S = 0;
	for (int i = k - 1; i >= 0; i--) {
		for (auto p: V[i]) {
			int q = p[0];
			int mx = max(a[p[1]], b[p[1]]);
			q ^= get_suf(mx);
			S += (q ? MN[p[1]] : MX[p[1]]);
		}
		add(t[i]);
	}
	for (auto p: non) {
		int q = p[0];
		int mx = max(a[p[1]], b[p[1]]);
		q ^= get_suf(mx);
		S += (q ? MN[p[1]] : MX[p[1]]);
		//cout << (q ? MN[p[1]] : MX[p[1]]) << ' ';
	}

	cout << S << '\n';
	return 0;
}
//به زآن که فروشند چه خواهند خرید
