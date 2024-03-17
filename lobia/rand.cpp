#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 8;
int label[N];

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        int seed = chrono::steady_clock::now().time_since_epoch().count();
        srand(seed);
        iota(label, label + N, 1);
        random_shuffle(label, label + N);

        cout << N << endl;
        FOR(i, 1, N) 
                cout << label[i] << ' ' << label[rand() % i] << '\n';
}
//15:45:35
