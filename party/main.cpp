#include <bits/stdc++.h>
using ll = long long;
using namespace std;
#define forn(a, b) for (int a = 0; a < (b); a++)
#define rofn(a, b) for (int a = (b) - 1; a >= 0; a--)
#define LOG(a) (63 - __builtin_clzll(a))
#define gc() (pt1==pt2&&(pt2=(pt1=buf)+fread(buf,1,1<<21,stdin),pt1==pt2)?EOF:*pt1++)
char buf[1<<21],*pt1,*pt2;

inline ll read() {
	ll x = 0;char c;
	while(!isdigit(c = gc()));
	while(isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = gc();
	return x;
}

const ll INFL = 1ll << 60;
const int INF = 1 << 29;
const int N = 61;
const int M = 2 * N;
const int MOD = 1e9 + 7;
const int X1 = 1e5;
const int X2 = 1e5;

ll d0[M][M], d1[M][M];
ll n;
int ptr, ans, q, cnt;
int pw2[X1 + 1], hwt[X2 + 1];

inline ll pw(ll a, int b) {
    ll re = 1;
    while (b) {
        if (b & 1)
            re = (re * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return re;
}

inline int p2(ll b) {
    b %= (MOD - 1);
    return 1ll * hwt[b / X1] * pw2[b % X1] % MOD;
}

void calc_dist(ll v) {
    for (int k = LOG(v) + 1; k < N; k++) {
        int x = k - LOG(v) - 1;
        if ((v << x) > n)
            d1[ptr][x] = 0;
        else 
            d1[ptr][x] = min(n - (v << x) + 1, ((ll)1 << x));
    }
    if (v > 1) {
        for (int k = 2; k < N; k++)
            d0[ptr][k] -= d1[ptr][k - 2];
    }
}

inline void pass() {
    for (int k = 1; k < M; k++)
        d0[ptr + 1][k] = d0[ptr][k - 1] + d1[ptr][k - 1];
    ptr++;
}

void Complete(ll v) {
    //cout << "C: " << v << ' ' << sub << " PTR: " << ptr << '\n';
    calc_dist(v);

    if ((v << 1) <= n) {
        pass();
        Complete(v << 1);
        q <<= 1;
        if (q >= MOD)
            q -= MOD;
    }

    ll s = 0;
    for (int k = 0; s != n; k++) {
        s += d0[ptr][k] + d1[ptr][k];
        q += p2(n - s) - 1;
        if (q >= MOD)
            q -= MOD;
    }
    ptr--;
}

inline int solve(ll a, ll b) {
    int x = LOG(b) - LOG(a);
    a <<= x;
    return x + (a <= b);
}

void F(ll v, ll sub) {
    if ((sub & (sub + 1)) == 0) {
        q = 0;
        Complete(v);
        ans += q;
        if (ans >= MOD)
            ans -= MOD;
        return;
    }
    

    //cout << "F: " << v << ' ' << sub << " PTR: " << ptr << '\n';
    calc_dist(v);

    ll r = (v << 1) | 1;
    ll l = (v << 1);
    int cntr = solve(r, n), cntl = solve(l, n);

    if (cntr == cntl) {
        q = 0;
        if ((v << 1) <= n) {
            pass();
            Complete(v << 1);
            ans += q;
            if (ans >= MOD)
                ans -= MOD;
        }

        if (((v << 1) | 1) <= n) {
            pass();
            F((v << 1) | 1, sub - (1ll << cntl));
        }
    }
    else {
        if (((v << 1) | 1) <= n) {
            q = 0;
            pass();
            Complete((v << 1) | 1);
            ans += q;
            if (ans >= MOD)
                ans -= MOD;
        }
        if ((v << 1) <= n) {
            pass();
            F((v << 1), sub - (1ll << cntr));
        }
    }
    

    ll s = 0;
    for (int k = 0; s != n; k++) {
        s += d0[ptr][k] + d1[ptr][k];
        ans += p2(n - s) - 1;
        if (ans >= MOD)
            ans -= MOD;
    }
    ptr--;
}

signed main() {
    ios::sync_with_stdio(0);

    pw2[0] = 1;
    for (int i = 1; i <= X1; i++) {
        pw2[i] = pw2[i - 1] << 1;
        if (pw2[i] >= MOD)
            pw2[i] -= MOD;
    }
    hwt[0] = 1;
    for (int i = 1; i <= X2; i++) {
        hwt[i] = (1ll * hwt[i - 1] * pw2[X1]) % MOD;
    }

    int query = read();
    //cin >> query;
    while (query--) {
        //cin >> n;
        n = read();
        F(1, n);
        ll re = p2(n) - 1;

        ans = (ans * pw(re, MOD - 2)) % MOD;
        cout << ans << '\n';

        ans = q = ptr = 0;
    }
    return 0;
}
//assert
//yaddasht
//nim saat dar ye vaziat
//checkpoint
//f ha ro benvisim
