#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 2e5 + 5;
const int SQ = 2000;
const int SQ_ = 105;

int f[SQ_][N];

int A[N], B[N], a[N], b[N], t[N], n;
char c[N];

void get_ans(int r) { //[L, R)
	int l = 0;
	int x = 1;
	while (l < r) {
		if (l / SQ != r / SQ) {
			x = f[l / SQ][x];
			l += SQ;
		}
		else {
			x = (x == A[l] ? B[l] : x);
			l++;
		}
	}
	cout << x << '\n';
}

void rebuild(int x) {
	for (int i = x * SQ; i < (x + 1) * SQ; i++) {
		f[x][A[i]] = A[i];
		f[x][B[i]] = B[i];
	}
	for (int i = (x + 1) * SQ - 1; i >= x * SQ; i--) {
		f[x][A[i]] = f[x][B[i]];
	}
}

void change(int i) {
	A[t[i]] = a[i];
	B[t[i]] = b[i];

	int l = t[i];
	rebuild(l / SQ);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	vector<int> T;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c[i];
		if (c[i] == '~') {
			cin >> t[i] >> a[i] >> b[i];
		}
		else {
			cin >> t[i];
		}
		T.push_back(t[i]);
	}
	for (int i = 0; i < SQ_; i++)
		for (int j = 0; j < N; j++)
			f[i][j] = j;

	sort(T.begin(), T.end());
	T.resize(unique(T.begin(), T.end()) - T.begin());

	for (int i = 0; i < n; i++) {
		t[i] = lower_bound(T.begin(), T.end(), t[i]) - T.begin();
	}
	
	for (int i = 0; i < n; i++) {
		if (c[i] == '~') {
			change(i);
		}
		else {
			get_ans(t[i] + 1);
		}
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
