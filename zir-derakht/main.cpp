#include <bits/stdc++.h>
using ll = long long;
using namespace std;

#define forn(a, b) for (int a = 0; a < (b); a++)
#define rofn(a, b) for (int a = (b) - 1; a >= 0; a--)
#define LOG(a) (31 - __builtin_clz(a))
#define chmx(a, b) a = max(a, b)
#define chmn(a, b) a = min(a, b)
#define pb push_back
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1,*p2;

inline int read() {
	int x = 0, f = 1; char c;
	while(!isdigit(c = gc())) if(c=='-') f=-1;
	while(isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = gc();
	return x * f;
}

const ll INFL = 1ll << 60;
const int INF = 1 << 29;
const int N = 1e5 + 50;
const int MOD = 1e9 + 7;

ll pw(ll a, ll b) {
    a %= MOD;
    b %= (MOD - 1);
    ll re = 1;
    while (b) {
        if (b & 1)
            re = (re * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return re;
}

ll dp[N];
int h[N], par[N], n, m;
bitset<N> mark;
vector<int> adj[N];

void dfs(int v) {
    mark[v] = true;
    dp[v] = 1;
    vector<int> unp;

    for (auto u: adj[v]) {
        if (!mark[u]) {
            par[u] = v;
            h[u] = h[v] + 1;
            dfs(u);
            dp[v] = (dp[v] * (dp[u] + 1)) % MOD;
        }
        else if (u != par[v] && h[u] > h[v]) {
            unp.pb(u);
        }
    }

    for (auto u: unp) {
        vector<ll> X;
        int last = n;
        while (u != par[v]) {
            X.pb((dp[u] * pw((dp[last] + 1), MOD - 2)) % MOD);
            if (X.back() < 0)
                X.back() += MOD;
            last = u;
            u = par[u];
        }

        dp[v] = 0;
        reverse(X.begin(), X.end());

        vector<ll> pref, P, suf;
        suf.pb(1);
        for (int i = X.size() - 1; i >= 1; i--) {
            suf.pb((suf.back() * X[i]) % MOD);
        }
        reverse(suf.begin(), suf.end());

        pref.pb(X[0]);
        for (int i = 1; i < X.size(); i++)
            pref.pb((pref.back() * X[i]) % MOD);

        P.resize(pref.size());
        for (int i = 0; i < P.size(); i++)
            P[i] = ((i ? P[i - 1] : 0) + pref[i]) % MOD;

        for (int i = 1; i < X.size(); i++) {
            dp[v] += (suf[i] * P[i - 1]) % MOD;
            if (dp[v] >= MOD)
                dp[v] -= MOD;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[v].pb(u);
        adj[u].pb(v);
    }
    par[0] = -1;
    dfs(0);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dp[i];
        if (ans >= MOD)
            ans -= MOD;
    }
    cout << ans << '\n';

    return 0;
}
