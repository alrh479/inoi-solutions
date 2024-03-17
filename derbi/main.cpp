#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 100 + 2;
const int SUM = N * (N + 1) / 2;
const int MOD = 1e9 + 7;
int dp[N][SUM], curtd, curs, n, q;
char s[N];

void add(int &a, int b) {
        a += b;
        a -= MOD * (a >= MOD);
}
void rm(int &a, int b) {
        a -= b;
        a += MOD * (a < 0);
}

void rm(int k) {
        FOR(td, 1, n + 1) {
                FOR(s, k, SUM) {
                        rm(dp[td][s], dp[td - 1][s - k]);
                }
        }
}
void add(int k) {
        for (int td = n; td >= 1; td--) {
                FOR(s, k, SUM) {
                        add(dp[td][s], dp[td - 1][s - k]);
                }
        }
}

void calc(int k) {
        int ans = 0;
        FOR(td, 0, n + 1) {
                int sum = k + (td + curtd) * (td + curtd - 1) / 2 - curs;
                add(ans, (sum >= 0 && sum < SUM ? dp[td][sum] : 0));
        }
        cout << ans << '\n';
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        dp[0][0] = 1;
        cin >> n >> q;
        FOR(i, 0, n)
                add(i);
        fill(s, s + n + 1, 'X');

        while (q--) {
                int t;
                cin >> t;
                if (t == 1) {
                        int x;
                        char c;
                        cin >> x >> c;
                        /*
                        if (c == 'R')
                                c = 'B';
                        else if (c == 'B')
                                c = 'R';
                                */
                        --x;
                        if (s[x] == c) continue;
                        if (c == 'R') {
                                rm(x);
                                curs += x;
                                curtd++;
                        }
                        else if (c == 'B') {
                                rm(x);
                        }
                        else {
                                if (s[x] == 'R') {
                                        curs -= x;
                                        curtd--;
                                }
                                add(x);
                        }
                        s[x] = c;
                }
                else {
                        int k;
                        cin >> k;
                        calc(k);
                }
        }
}
//09:15:51
