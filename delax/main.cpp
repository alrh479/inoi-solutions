#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 3e5 + 50;
const int L = 20;
int rmq[L][N], a[N], loc[N], X[N], onpath[N];
vector<int> path;
int t[2 * N], delta[N << 2], mn[N << 2], sum, n, q, b[N];

void modify(int p, const int val) {
        for (t[p += n] = val; p >>= 1; )
                t[p] = min(t[p << 1], t[p << 1 | 1]);
}
int query(int l, int r) {
        int mn = INF;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) 
                        mn = min(mn, t[l++]);
                else
                        mn = min(mn, t[--r]);
        }
        return mn;
}

void add(int v, int l, int r, int L, int R, int k) {
        if (r <= L || R <= l)
                return;
        if (L <= l && r <= R) {
                mn[v] += k;
                delta[v] += k;
                return;
        }
        int m = l + r >> 1;
        add(v << 1, l, m, L, R, k);
        add(v << 1 | 1, m, r, L, R, k);
        mn[v] = min(mn[v << 1], mn[v << 1 | 1]) + delta[v];
}

int get(int l, int r) { //[l, r)
        int x = __lg(r - l);
        return loc[max(rmq[x][l], rmq[x][r - (1 << x)])];
}

void build(int l, int r) {
        int mx_ind = get(l, r + 1);
        path.push_back(mx_ind);
        if (mx_ind == l || mx_ind == r)
                return;
        int L = get(l, mx_ind);
        int R = get(mx_ind + 1, r + 1);     
        if (a[L] < a[R]) {
                build(l, mx_ind - 1);
        }
        else {
                build(mx_ind + 1, r);
        }
}

void ans_q() {
        if (path.size() == 1)
                cout << sum << '\n';
        else
                cout << min(mn[1], sum) << '\n';
}

void solve() {
        ans_q();
        while (q--) {
                int id, val;
                cin >> id >> val;
                --id;
                if (onpath[id] != -1) {
                        int x = onpath[id];
                        int delta = val - b[id];
                        if (x + 1 != path.size()) 
                                add(1, 0, path.size(), x + 1, path.size(), delta);
                        sum += delta;
                }
                else {
                        int x = X[a[id]];
                        int delta = -query(a[path[x]] + 1, a[path[x - 1]]);
                        modify(a[id], val);
                        delta += query(a[path[x]] + 1, a[path[x - 1]]);
                        add(1, 0, path.size(), x, x + 1, delta);
                }
                ans_q();
        }
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        cin >> n >> q;
        FOR(i, 0, n) {
                cin >> a[i];
                loc[--a[i]] = i;
        }
        copy(a, a + n, rmq[0]);
        FOR(l, 1, L) {
                FOR(i, 0, n - (1 << l) + 1) {
                        rmq[l][i] = max(rmq[l - 1][i], rmq[l - 1][i + (1 << l - 1)]);
                }
        }       
        build(0, n - 1);
        FOR(i, 0, n)
                cin >> b[i];
        FOR(i, 0, n)
                modify(a[i], b[i]);
        for (auto i: path) {
                sum += b[i];
        }
        memset(onpath, -1, sizeof onpath);
        FOR(i, 0, path.size())
                onpath[path[i]] = i;
        FOR(i, 0, path.size() - 1) {
                add(1, 0, path.size(), i + 1, path.size(), b[path[i]]);
        }
        FOR(i, 1, path.size()) {
                int Ap = a[path[i - 1]], A = a[path[i]];
                add(1, 0, path.size(), i, i + 1, query(A + 1, Ap));
                FOR(j, A + 1, Ap)
                        X[j] = i;
        }
        add(1, 0, path.size(), 0, 1, INF);
        solve();
}
//11:18:53
