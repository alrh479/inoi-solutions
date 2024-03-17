#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 3e5 + 5;
const int M = 1e6 + 5;
const int MOD = 1e9 + 7;
int pr[N], n, q, r, val[N], x[N], t[N], cur, zero, ans[N], V[N], root[N], R[N], leaf[N], f[M], finv[M], delta[N];
vector<int> adj[N];

int inv(int a) {
        int b = MOD - 2, re = 1;
        for (; b; b >>= 1, a = a * a % MOD) if (b & 1) re = re * a % MOD;
        return re;
}

int gpr(int x) {
        while (x != root[x]) x = root[x];
        return x;
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

void merge(int v, int p, int val) {
        assert(root[v] == v);
        int tp = gpr(p);
        del(calc(tp));
        del(calc(v));
        root[v] = p;
        int l = leaf[v], x = R[v];
        R[v] -= val;
        while (v != root[v]) {
                v = root[v];
                R[v] += x;
                leaf[v] += l;
        }
        add(calc(v));
}
void hazf(int v, int p, int val) {
        int tp = gpr(p);
        del(calc(tp));
        assert(root[v] == p);
        R[v] += val;
        add(calc(v));
        int l = leaf[v], t = v, x = R[v];
        while (v != root[v]) {
                v = root[v];
                leaf[v] -= l;
                R[v] -= x;
        }
        add(calc(v));
        root[t] = t;
}

void solve() {
        FOR(i, 0, n) root[i] = pr[i];
        R[0] = r;
        cur = calc(0);
        cout << cur << '\n';

        FOR(i, 0, q) {
                if (t[i] == 1) {
                        hazf(V[i], pr[V[i]], x[i]);
                        val[V[i]] = x[i];
                }
                else {
                        merge(V[i], pr[V[i]], val[V[i]]);
                }
                cout << (zero ? 0 : cur) << '\n';
        }
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
        cin >> q;
        FOR(i, 0, q) {
                cin >> t[i] >> V[i];
                V[i]--;
                if (t[i] == 1) cin >> x[i];
        }
        dfs(0);
        solve();
}
//09:40:29
