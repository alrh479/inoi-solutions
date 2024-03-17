#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 150 + 5;
vector<int> adj[N];
vector<array<int, 2>> e;
int h[N], A[N][N], B[N][N], pr[N], ans, n, m, k, path[N];

int LCA(int u, int v) {
       if (h[u] > h[v])
               swap(u, v);
        while (h[v] != h[u])
                v = pr[v];
        while (v != u) {
                u = pr[u];
                v = pr[v];
        }
        return u;
}

int kpar(int v, int k) {
        while (k--)
                v = pr[v];
        return v;
}

void dfs(int v, int p) {
        for (auto u: adj[v]) if (u != p) {
                pr[u] = v;
                h[u] = h[v] + 1;
                dfs(u, v);
        }
}

void move(int x, int y) {
        if (x > y)
                swap(x, y);
        if (e.size() && e.back() == array<int, 2>{x, y}) {
                ans += B[x][y];
                e.pop_back();
        }
        else {
                ans += A[x][y];
                e.push_back({x, y});
        }
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        memset(A, 0x3f, sizeof A);
        memset(B, 0x3f, sizeof B);
        cin >> n >> m >> k;
        assert(n == m + 1);
        FOR(i, 0, m) {
                int u, v, a, b;
                cin >> u >> v >> a >> b;
                --u, --v;
                adj[u].push_back(v);
                adj[v].push_back(u);
                A[u][v] = A[v][u] = min(A[u][v], a);
                B[u][v] = B[v][u] = min(B[u][v], b);
        }
        FOR(i, 0, k) {
                cin >> path[i];
                --path[i];
        }
        dfs(0, 0);
        FOR(i, 1, k) {
                int last = path[i - 1];
                int lca = LCA(last, path[i]);
                while (last != lca) {
                        move(last, pr[last]);
                        last = pr[last];
                }
                vector<int> P{path[i]};
                while (P.back() != lca) {
                        P.push_back(pr[P.back()]);
                }
                P.pop_back();
                reverse(P.begin(), P.end());
                for (auto v: P) {
                        move(last, v);
                        last = v;
                }
        }
        cout << ans << '\n';
}
//09:58:44
