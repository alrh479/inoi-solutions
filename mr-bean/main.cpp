#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define int int64_t
const int64_t INF = 1ll << 60;
const int N = 750 + 5;
int dp[N][N], nx[N][N], n, a[N];

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        cin >> n;
        FOR(i, 0, n)
                cin >> a[i];
        n = unique(a, a + n) - a;
        memset(dp, 0x3f, sizeof dp);
        for (int l = n - 1; l >= 0; l--) {
                dp[l][l] = 0;
                for (int r = l + 1; r < n; r++) {
                        dp[l][r] = min(dp[l][r], dp[l + 1][r] + 1);
                        for (int m = l + 1; m <= r; m++) if (a[l] == a[m]) {
                                dp[l][r] = min(dp[l][r], dp[l + 1][m - 1] + 1 + dp[m][r]);
                        }
                }
        }
        cout << dp[0][n - 1];
}
//11:20:30
