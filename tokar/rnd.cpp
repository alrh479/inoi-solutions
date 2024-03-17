#include "bits/stdc++.h"
using namespace std;
const long long INF = 1ll << 60;
const int N = 1e5 - 1;

signed main(int argc, char** argv) {
	ios::sync_with_stdio(0), cin.tie(0);
	if (argc == 1) {
		cout << "WHOA!\n";
		return 0;
	}
	srand(stoi(argv[1]));
	cout << N << ' ' << N << endl;
	for (int i = 0; i < N; i++) cout << (rand() & 3) + 1 << ' ';

	for (int i = 0; i < N; i++) {
		int t = rand();
		t = !!(t % 4);
		t++;
		int l = rand() % N + 1, r = rand() % N + 1;
		if (r < l) swap(l, r);
		cout << t << ' ' << l << ' ' << r << ' ';

		if (t == 1) {
			int x = rand() & 3, y = rand() & 3;
			x++, y++;
			cout << x << ' ' << y << '\n';
		}
		else {
			int k = r - l + 1;
			cout << k << '\n';
		}
	}

	return 0;
}
//به زآن که فروشند چه خواهند خرید
