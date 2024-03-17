#include "bits/stdc++.h"
using namespace std;
#define int long long
const int N = 1e5 + 50;
const long long INF = 1ll << 60;
int dist[N], n;
vector<int> a;
vector<vector<int>> V;

int find() {
        fill(dist + 1, dist + N, INF);
        dist[0] = -INF;
        for (int i = 0; i < n; i++) *lower_bound(dist, dist + N, a[i]) = a[i];
        int m = 0;
        while (dist[m] != INF) m++;
        assert(dist[m] == INF);
        //m--
        //dist[(m + 1) / 2]
        return dist[m / 2];
}

signed main() {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) cin >> a[i];

	reverse(a.begin(), a.end());

        while (!is_sorted(a.rbegin(), a.rend())) {
                V.push_back(a);
		for (auto u: a) cout << u << ' ';
		cout << '\n';
                int m = find();
		cout << "M: " << m << endl;
                vector<int> b;
                for (int i = 0; i < n; i++) if (a[i] > m) b.push_back(a[i]);
                for (int i = 0; i < n; i++) if (a[i] <= m) b.push_back(a[i]);
                a = b;
        } 
        cout << V.size() << '\n';
        V.push_back(a);
        for (auto &v: V) {
		reverse(v.begin(), v.end());
                for (auto u: v) cout << u << ' ';
                cout << '\n';
        }
} 
