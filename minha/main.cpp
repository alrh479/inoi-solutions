#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 50;
long long a[N], x[N], dp[N];
int n;
set<pair<long long, long long>> S;
multiset<long long> low;

signed main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> x[i];
	sort(x, x + n);
	n = unique(x, x + n) - x;
	for (int i = 0; i < n; i++)
		a[i] = x[i + 1] - x[i];

	S.insert({0, -1});
	low.insert(1);

	for (int i = 0; i < n; i++) {
		dp[i] = min(*low.begin(), (i ? dp[i - 1] : 0) + 1);
		pair<long long, long long> p = {-1, -1};
		while (S.size()) {
			auto it = S.end();
			it--;
			if (-(it->second) > a[i])
				break;
			p = *it;
			p.second = -p.second;
			low.erase(low.find(p.first + p.second));
			S.erase(it);
		}
		if (p.first != -1) {
			low.insert(p.first + a[i]);
			S.insert({p.first, -a[i]});
		}
		/*
		cout << "I: " << i << '\n';
		for (auto p: S)
			printf("{%lld, %lld} \n", p.first, -p.second);
			*/
		while (S.size()) {
			auto it = S.end();
			it--;
			if (it->first >= dp[i]) {
				low.erase(low.find(it->first - it->second));
				S.erase(it);
			}
			else
				break;
		}
		low.insert(dp[i] + 1);
		S.insert({dp[i], -1});
	}
	/*
	for (int i = 0; i < n; i++)
		cout << dp[i] << ' ';
		*/
	cout << dp[n - 1] << '\n';
	return 0;
}

