#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 3e5 + 5;

int n, a[N], d[N], lz[4 * N], av[4 * N];
long long S[4 * N];
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<15,stdin),p1==p2)?EOF:*p1++)
char buf[1<<15],*p1,*p2;

inline int read() {
	int x = 0; char c;
	while(!isdigit(c = gc()));
	while(isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = gc();
	return x;
}

inline void push(int v) {
	if (lz[v]) {
		lz[v << 1] += lz[v];
		lz[v << 1 | 1] += lz[v];
		S[v << 1] += 1ll * lz[v] * av[v << 1];
		S[v << 1 | 1] += 1ll * lz[v] * av[v << 1 | 1];
		lz[v] = 0;
	}
}
void add_av(const int ind) {
	int v = 1, l = 0, r = n;
	while (r - l > 1) {
		push(v);
		av[v]++;
		int m = l + r >> 1;
		v *= 2;
		if (ind < m) r = m;
		else l = m, v |= 1;
	}
	av[v]++;
}
void add_S(int v, int l, int r, int L, int R) {
	if (L <= l && R >= r) {
		lz[v]++;
		S[v] += av[v];
		return;
	}
	push(v);
	int m = l + r >> 1;
	if (R <= m) 
		add_S(v << 1, l, m, L, R);
	else if (L >= m)
		add_S(v << 1 | 1, m, r, L, R);
	else
		add_S(v << 1, l, m, L, m), add_S(v << 1 | 1, m, r, m, R);
	S[v] = S[v << 1] + S[v << 1 | 1];
}
long long get(int v, int l, int r, int L, int R) {
	if (L <= l && R >= r) return S[v];
	push(v);
	int m = l + r >> 1;

	if (R <= m)
		return get(v << 1, l, m, L, R);
	else if (L >= m)
		return get(v << 1 | 1, m, r, L, R);
	else
		return get(v << 1, l, m, L, m) + get(v << 1 | 1, m, r, m, R);
}

signed main() {
	n = read();
	for (int i = 0; i < n; i++)
		a[i] = read();

	copy(a, a + n, d);
	sort(d, d + n);
	for (int i = 0; i < n; i++)
		a[i] = lower_bound(d, d + n, a[i]) - d;

	long long re = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] + 1 != n) re += get(1, 0, n, a[i] + 1, n);
		//add ith
		if (a[i]) add_S(1, 0, n, 0, a[i]);
		add_av(a[i]);
	}
	printf("%lld", re);
	return 0;
}
//به زآن که فروشند چه خواهند خرید
