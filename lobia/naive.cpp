#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 2000;
bitset<N> mark;
int n;
vector<int> adj[N];

int dfs(int v, int l, int r) {
        mark[v] = true;
        int cnt = 1;
        for (auto u: adj[v]) if (!mark[u] && (u < l || u > r)) {
                cnt += dfs(u, l, r);
        }
        return cnt;
}


int solve(int l, int r) {
        mark = 0;
        if (l)
                return dfs(0, l, r) == n - (r - l + 1);
        else if (r != n - 1)
                return dfs(n - 1, l, r) == n - (r - l + 1);
        else
                return 0;
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        cin >> n;
        FOR(i, 1, n) {
                int u, v;
                cin >> u >> v;
                --u;
                --v;
                adj[u].push_back(v);
                adj[v].push_back(u);
        }
        int ans = 0;
        for (int l = 0; l < n; l++) {
                for (int r = l; r < n; r++) {
                        ans += solve(l, r);
                }
        }
        cout << ans << '\n';
}
//15:34:08
