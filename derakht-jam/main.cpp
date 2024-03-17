#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 3e5 + 5;
const int M = 1e6 + 5;
const int MOD = 1e9 + 7;
int pr[N], n, q, r, val[N], x[N], t[N], cur, zero, ans[N], V[N], root[N], R[N], leaf[N], f[M], finv[M];
vector<int> adj[N];

int inv(int a) {
        int b = MOD - 2, re = 1;
        for (; b; b >>= 1, a = a * a % MOD) if (b & 1) re = re * a % MOD;
        return re;
}

int gpr(int x) {
        return root[x] == x ? root[x] : root[x] = gpr(root[x]);
}
int C(int n, int r) {
        if (n < r || r < 0) return 0;
        return f[n] * finv[n - r] % MOD * finv[r] % MOD;
}

void dfs(int v) {
        leaf[v] = 1;
        for (auto u: adj[v]) {
                adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
                dfs(u);
                pr[u] = v;
                leaf[v] += leaf[u];
        }
}

void dfs2(int v) {
        if (val[v] != -1) {
                R[root[v]] -= val[v];
                leaf[root[v]] -= leaf[v];
                root[v] = v;
        }
        for (auto u: adj[v]) {
                root[u] = root[v];
                dfs2(u);
        }
}

void del(int c) {
        if (c == 0) zero--;
        else cur = (cur * inv(c)) % MOD;
}
void add(int c) {
        if (c == 0) zero++;
        else cur = (cur * c) % MOD;
}
int calc(int v) {
        return C(R[v] + leaf[v] - 1, R[v]);
}

void merge(int v, int p) {
        v = gpr(v), p = gpr(p);
        assert(v != p);
        root[v] = p;
        del(calc(v));
        del(calc(p));
        R[p] += R[v];
        leaf[p] += leaf[v];
        add(calc(p));
}

void solve() {
        R[0] = r;
        memset(val, -1, sizeof val);
        FOR(i, 0, q)
                val[V[i]] = R[V[i]] = x[i];
        root[0] = 0;
        dfs2(0);
        cur = 1;
        FOR(i, 0, n) if (root[i] == i) {
                int c = C(R[i] + leaf[i] - 1, R[i]);
                if (c == 0) zero++;
                else cur = (cur * c) % MOD;
        }
        for (int i = q - 1; i >= 0; i--) {
                ans[i] = (zero ? 0 : cur);
                merge(V[i], pr[V[i]]);
        }
        cout << cur << '\n';
        FOR(i, 0, q) cout << ans[i] << '\n';
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        f[0] = finv[0] = 1;
        FOR(i, 1, M) {
                f[i] = f[i - 1] * i % MOD;
                finv[i] = inv(f[i]);
        }
        cin >> n >> r;
        FOR(i, 1, n) {
                int u, v; cin >> u >> v;
                u--, v--;
                adj[v].push_back(u);
                adj[u].push_back(v);
        }
        int subtask3 = 0;
        cin >> q;
        FOR(i, 0, q) {
                cin >> t[i] >> V[i];
                subtask3 += t[i] == 2;
                V[i]--;
                if (t[i] == 1) cin >> x[i];
        }
        assert(!subtask3);
        dfs(0);
        solve();
}
//09:40:29
