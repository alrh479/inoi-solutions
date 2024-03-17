#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i) 
#define int unsigned long long
#define chmn(a, b) a = (a < b ? a : b)
const int64_t INF = 1ll << 60;
const int N = 150 + 5;
int A[N][N], n, m, k, AB[N][N], dp[N][N][N], rdp[N][N][N]; //[l, r, v]
int F[N][N], path[N]; //stands for help me
set<array<int, 3>> S;
bitset<N> mark;

void apply(int v, int x, int d) {
        if (F[v][x] <= d)
                return;
        S.erase({F[v][x], v, x});
        S.insert({F[v][x] = d, v, x});
}       

void solve() {
        memset(dp, 0x3f, sizeof dp);
        FOR(i, 0, k)
                dp[i][i][path[i]] = 0;
        for (int l = k - 1; ~l; --l) {
                for (int r = l; r < k; ++r) {
                        for (int m = l; m < r; ++m) { //N ^ 3 / 6
                                FOR(v, 0, n) { //N
                                        chmn(dp[l][r][v], dp[l][m][v] + rdp[r][m + 1][v]);
                                }
                        }

                        FOR(x, 0, n) { //n ^ 4 / 2
                                FOR(v, 0, n) {
                                        chmn(dp[l][r][v], dp[l][r][x] + AB[x][v]);
                                }
                        }
                        FOR(v, 0, n) {
                                rdp[r][l][v] = dp[l][r][v];
                        }
                }
        }
        memset(F, 0x3f, sizeof F);
        F[path[0]][0] = 0;
        S.insert({0, path[0], 0});
        while (S.size()) {
                auto P = *S.begin();
                S.erase(S.begin());
                int v = P[1], x = P[2];
                FOR(u, 0, n) {
                        apply(u, x, F[v][x] + A[v][u]);
                }
                FOR(X, x + 1, k) 
                        apply(v, X, F[v][x] + dp[x + 1][X][v]);
        }
        int mn = F[0][k - 1];
        FOR(i, 1, n)
                mn = min(mn, F[i][k - 1]);
        cout << mn << '\n';
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        memset(A, 0x3f, sizeof A);
        memset(AB, 0x3f, sizeof AB);
        FOR(i, 0, N)
                A[i][i] = AB[i][i] = 0;
        cin >> n >> m >> k;
        FOR(i, 0, m) {
                int u, v, a, b;
                cin >> u >> v >> a >> b;
                --u;
                --v;
                A[u][v] = A[v][u] = min(A[u][v], a);
                AB[u][v] = AB[v][u] = min(AB[u][v], a + b);
        }
        FOR(i, 0, k) {
                cin >> path[i];
                --path[i];
        }
        FOR(k, 0, n) FOR(i, 0, n) FOR(j, 0, n)
                A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
        FOR(k, 0, n) FOR(i, 0, n) FOR(j, 0, n)
                AB[i][j] = min(AB[i][j], AB[i][k] + AB[k][j]);
        solve();
}
//09:58:44
