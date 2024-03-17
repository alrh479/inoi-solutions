#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
using ar = array<int, 2>;
const int INF = 1ll << 30;
const int N = 1e6 + 6;
int n, x[N], p[N], q, ans[N], S[4 * N], delta[4 * N];
ar M[1500], a[N], b[N];

void add(int v, int l, int r, int L, int R, int d) {
        if (R <= l || r <= L) return;
        if (L <= l && r <= R) { 
                delta[v] += d, S[v] += d;
                return;
        }
        int m = l + r >> 1;
        add(v << 1, l, m, L, R, d), add(v << 1 | 1, m, r, L, R, d);
        S[v] = min(S[v << 1], S[v << 1 | 1]) + delta[v];
}
int find(int v, int l, int r) {
        if (l + 1 == r) {
                S[v] = INF;
                if (l + 1 != q) add(1, 0, q, l + 1, q, -1);
                return l;
        }
        int m = l + r >> 1, x;
        if (S[v << 1 | 1] <= S[v << 1]) x = find(v << 1 | 1, m, r);
        else x = find(v << 1, l, m);
        S[v] = min(S[v << 1], S[v << 1 | 1]) + delta[v];
        return x;
}

void seq() {
        FOR(i, 0, q) add(1, 0, q, i, i + 1, p[i]);
        FOR(i, 0, q) {
                int t = find(1, 0, q);
                a[i][0] = t, a[i][1] = x[t];
        }
}
void solve() {
        while (true) {
                ar lis = {0, INF};
                fill(M, M + 1500, lis);
                FOR(i, 0, q) {
                        ar p = *max_element(M, M + a[i][1]);
                        M[a[i][1]] = max(M[a[i][1]], ar{p[0] + 1, min(p[1], -a[i][0])});
                }
                lis = *max_element(M, M + 1500);
                for (int i = q - 1; i >= -lis[1]; i--) ans[i] = lis[0];
                if (!lis[1]) return;
                int ptr = 0;
                FOR(i, 0, q) if (a[i][0] < -lis[1]) b[ptr++] = a[i];
                q = ptr;
                copy(b, b + ptr, a);
        }
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        cin >> q;
        int tq = q;
        vector<int> X;
        FOR(i, 0, q) {
                cin >> p[i] >> x[i];
                X.push_back(x[i]);
        }
        sort(X.begin(), X.end());
        X.resize(unique(X.begin(), X.end()) - X.begin());
        FOR(i, 0, q)
                x[i] = lower_bound(X.begin(), X.end(), x[i]) - X.begin() + 1;
        seq(), solve();
        FOR(i, 0, tq) cout << ans[i] << '\n';
}
