#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 5e5 + 5;
const int MOD[] = {(int) 1e9 + 7, (int) 1e9 + 9};
const int BASE = 37;
const int LG = 19;
vector<array<int, 2>> hs[N], h[N];
int INV[2][N], lcp[N], P[2][N], n, m, H[2][N], dp[LG][N];
string L, s[N];
array<int, 2> rmq[LG][N];

int inv(int x, const int MOD) {
        int re = 1;
        for (int b = MOD - 2; b; b >>= 1, x = x * x % MOD) if (b & 1)
                re = re * x % MOD;
        return re;
}

int get_hash(int i, int l, int r) {
        int hsh = H[i][r] - (l ? H[i][l - 1] : 0);
        hsh *= INV[i][l];
        hsh %= MOD[i];
        if (hsh < 0) 
                hsh += MOD[i];
        return hsh;
}

bool check(int l, int r) {
        return binary_search(hs[r - l].begin(), hs[r - l].end(), array<int, 2>{get_hash(0, l, r), get_hash(1, l, r)});
}

void build_lcp() {
        FOR(i, 0, L.size()) {
                int l = i - 1, r = L.size();
                while (r - l > 1) {
                        int m = l + r >> 1;
                        if (check(i, m)) 
                                l = m;
                        else
                                r = m;
                }
                lcp[i] = r;
        }
}
void build_rmq() {
        FOR(i, 0, L.size())
                rmq[0][i] = {lcp[i], i};
        FOR(j, 0, LG - 1) {
                FOR(i, 0, 1 + (int) L.size() - (2 << j)) {
                        rmq[j + 1][i] = max(rmq[j][i], rmq[j][i + (1 << j)]);
                }       
        }
}
int get(int l, int r) { //[l, r)
       int t = __lg(r - l);
       return max(rmq[t][l], rmq[t][r - (1 << t)])[1];
}
void build_dp() {
        copy(lcp, lcp + L.size(), dp[0]);
        for (int j = 1; j < LG; j++) {
                FOR(i, 0, L.size()) {
                        dp[j][i] = dp[j - 1][i];
                        if (dp[j][i] < L.size()) {
                                int mx_ind = get(i, dp[j][i] + 1);
                                dp[j][i] = dp[j - 1][mx_ind];
                        }
                }
        }
}
int calc(int l, int r) {
        int tl = l;
        int ans = 0;
        for (int j = LG - 1; j >= 0; j--) {
                if (dp[j][l] < r) {
                        ans |= 1 << j;
                        l = get(tl, dp[j][l] + 1);
                }
        }
        return (dp[0][l] >= r ? ans + 1 : -1);
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        P[0][0] = P[1][0] = INV[0][0] = INV[1][0] = 1;
        FOR(j, 0, 2) {
                FOR(i, 1, N) {
                        P[j][i] = (P[j][i - 1] * BASE) % MOD[j];
                        INV[j][i] = inv(P[j][i], MOD[j]);
                }
        }
        cin >> n >> m;
        FOR(i, 0, n) {
                cin >> s[i];
                h[i].resize(s[i].size());
                h[i][0] = {s[i][0] - 'a' + 1, s[i][0] - 'a' + 1};
                FOR(k, 0, 2) {
                        FOR(j, 1, s[i].size()) {
                                h[i][j][k] = (h[i][j - 1][k] + (s[i][j] - 'a' + 1) * P[k][j] % MOD[k]) % MOD[k];
                        }
                }
                FOR(j, 0, s[i].size())
                        hs[j].push_back(h[i][j]);
        }
        FOR(i, 0, N) {
                sort(hs[i].begin(), hs[i].end());
        }
        cin >> L;
        FOR(k, 0, 2) {
                H[k][0] = L[0] - 'a' + 1;
                FOR(i, 1, L.size()) {
                        H[k][i] = (H[k][i - 1] + (L[i] - 'a' + 1) * P[k][i] % MOD[k]) % MOD[k];
                }
        }
        build_lcp();
        build_rmq();
        build_dp();

        FOR(i, 0, m) {
                int l, r;
                cin >> l >> r;
                cout << calc(l, r) << '\n';
        }
}
//13:00:40
