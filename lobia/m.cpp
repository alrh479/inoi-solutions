#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 1e6 + 5;
int fn[N], T = 0, st[N], pr[N], n, cnt = 0, dpr[N], P[N];
vector<int> adj[N];
set<int> min_r;
set<array<int, 2>> in_tree, rm;
vector<bool> mark(N, 0);

struct tree { 
        int S[N << 2];
        bool P[N << 2];
        void init() {
                fill(P, P + (N << 2), 1);
        }
        void add(int v, int l, int r, int idx, const int d) {
                if (!P[v]) return;
                if (l + 1 == r) {
                        S[v] += d;
                        return;
                }
                int m = l + r >> 1;
                if (idx < m)
                        add(v << 1, l, m, idx, d);
                else
                        add(v << 1 | 1, m, r, idx, d);
                S[v] = S[v << 1] + S[v << 1 | 1];
        }
        int get(int v, int l, int r, int L, int R) {
                if (!P[v] || r <= L || R <= l) return 0;
                if (L <= l && r <= R) return S[v];
                int m = l + r >> 1;
                return get(v << 1, l, m, L, R) + get(v << 1 | 1, m, r, L, R);
        }
        void mult(int v, int l, int r, int L, int R) {
                if (!P[v] || r <= L || R <= l) return;
                if (L <= l && r <= R) {
                        S[v] = 0;
                        P[v] = 0;
                        return;
                }
                int m = l + r >> 1;
                mult(v << 1, l, m, L, R); 
                mult(v << 1 | 1, m, r, L, R);
                S[v] = S[v << 1] + S[v << 1 | 1];
        }
        void add(int id, const int d) {
                add(1, 0, n, id, d);
        }
        int get(int r) {
                return get(1, 0, n, 0, r + 1);
        }
} fenw;

int gpr(int u) {
        return dpr[u] == u ? u : dpr[u] = gpr(dpr[u]);
}
void merge(int u, int v) {
        u = gpr(u), v = gpr(v);
        dpr[u] = v;
        cnt -= u != v;
}

int just_r() {
        iota(dpr, dpr + N, 0);
        int ans = 0;
        for (int r = n - 1; r >= 1; r--) {
                cnt++;
                mark[r] = true;
                for (auto u: adj[r]) if (mark[u])
                        merge(u, r);
                ans += cnt == 1;
        }
        return ans;
}

void dfs(int v) {
        st[v] = T;
        ++T;
        for (auto u: adj[v]) {
                adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
                pr[u] = P[u] = v;
                dfs(u);
        }
        fn[v] = T;
}

int balance(int v) {
        auto it = in_tree.lower_bound({st[v], -1});
        if (it == in_tree.end() || (*it)[0] >= fn[v]) {
                min_r.erase(v);
                return (v ? pr[v] = balance(pr[v]) : v);
        }
        return v;
}

void del(int u) {
        
        for (auto c: adj[u]) if (u < c)
                fenw.mult(1, 0, n, u + 1, c + 1);

        fenw.add(u, +1);

        in_tree.erase({st[u], u});
        min_r.insert(u);
        balance(u);
}

int get_ans() {
        int r = (min_r.size() ? *(min_r.begin()) : N - 3);
        return fenw.get(r) + min_r.empty();
}


signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        fenw.init();
        cin >> n;
        FOR(i, 1, n) {
                int u, v;
                cin >> u >> v;
                --u;
                --v;
                adj[v].push_back(u);
                adj[u].push_back(v);
        }
        long long ans = just_r();
        dfs(0);
        FOR(i, 0, n)
                in_tree.insert({st[i], i});
        for (int l = n - 1; l >= 0; l--) {
                int t = get_ans();
                ans += t;
                if (l) 
                        del(l);
        }
        cout << ans - n << '\n';
}
//09:54:13
