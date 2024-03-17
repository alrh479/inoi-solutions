#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define int long long
const int64_t INF = 1 << 30;
const int N = 1e5 + 5;
const int LG = 17;
int dp[N][LG][LG], mn[N][LG], a[N], n, lg, DP[N];

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        cin >> n;
        FOR(i, 0, n) cin >> a[i];
        
        for (int x = n - 1; x >= 0; x--) {
                mn[x][0] = a[x];
                for (int i = 1; (1 << i) + x <= n; i++)
                        mn[x][i] = min(mn[x][i - 1], mn[x + (1 << (i - 1))][i - 1]);
                FOR(j, 0, LG) {
                        if (a[x] <= j + 1) dp[x][0][j] = (a[x] == j + 1);
                        else dp[x][0][j] = INF;
                }
                for (int i = 1; (1 << i) + x <= n; i++) {
                        FOR(j, 0, LG) {
                                dp[x][i][j] = dp[x][i - 1][j] + dp[x + (1 << (i - 1))][i - 1][j];
                                if (mn[x][i] > j) 
                                        dp[x][i][j] = min(dp[x][i][j], dp[x][i - 1][j + 1] + dp[x + (1 << (i - 1))][i - 1][j + 1] + 1);
                        }
                }
        }
        fill(DP, DP + N, INF);
        DP[n] = 0;
        for (int x = n - 1; x >= 0; x--) {
                for (int i = 0; (1 << i) + x <= n; i++) {
                        DP[x] = min(DP[x], dp[x][i][0] + DP[x + (1 << i)]);
                }
        }
        cout << (DP[0] == INF ? -1 : DP[0]) << '\n';
}
//10:39:29
