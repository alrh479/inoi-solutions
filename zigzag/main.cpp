#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 3e5 + 5;
int n, q, a[N], b[N];

struct seg {
        int tool = 0, jam = 0, lz = 1, pref = 0, suf = 0, last = 0, fi = 0, ans = 0;
} S[N << 2], I;

inline int sgn(int x) {
        if (x == 0) return 0;
        return (x < 0 ? -1 : +1);
}
void print(int v, int l, int r) {
        if (l + 1 == r) {
                cout << S[v].jam << ' ';
                return;
        }
        int m = l + r >> 1;
        print(v << 1, l, m);
        print(v << 1 | 1, m, r);
}

void apply(int v) { //zarb * -1
        S[v].jam *= -1; 
        S[v].last *= -1;
        S[v].fi *= -1;
        S[v].lz *= -1;
}
inline void push(int v) {
        if (S[v].lz == -1) {
                apply(v << 1), apply(v << 1 | 1);
                S[v].lz = 1;
        }
}
void merge(seg &v, seg l, seg r) {
        v.jam = l.jam + r.jam;
        v.pref = (l.pref == l.tool && l.fi && r.fi && ((sgn(l.fi) == sgn(r.fi) && l.tool % 2 == 0) || (sgn(l.fi) != sgn(r.fi) && l.tool % 2 == 1)) ? l.pref + r.pref : l.pref);
        v.suf = (r.suf == r.tool && r.last && l.last && ((sgn(l.last) == sgn(r.last) && r.tool % 2 == 0) || (sgn(l.last) != sgn(r.last) && r.tool % 2 == 1)) ? r.suf + l.suf : r.suf);
        v.last = r.last;
        v.fi = l.fi;
        v.ans = l.ans + r.ans;
        v.ans += (l.last && r.fi && sgn(l.last) != sgn(r.fi) ? l.suf * r.pref : 0);
}
void upd(int v, int l, int r, int ind, int x) {
        if (l + 1 == r) {
                S[v].jam += x;
                S[v].fi = S[v].last = S[v].jam;
                S[v].pref = S[v].suf = S[v].ans = (S[v].jam != 0);
                return;
        }
        push(v);
        int m = l + r >> 1;
        if (ind < m) upd(v << 1, l, m, ind, x);
        else upd(v << 1 | 1, m, r, ind, x);
        merge(S[v], S[v << 1], S[v << 1 | 1]);
}
void mult(int v, int l, int r, int L, int R) {
        if (R <= l || r <= L) return;
        if (L <= l && r <= R) {
                apply(v);
                return;
        }
        push(v);
        int m = l + r >> 1;
        mult(v << 1, l, m, L, R);
        mult(v << 1 | 1, m, r, L, R);
        merge(S[v], S[v << 1], S[v << 1 | 1]);
}
int get_sum(int v, int l, int r, int L, int R) {
        if (R <= l || r <= L) return 0;
        if (L <= l && r <= R) return S[v].jam;
        push(v);
        int m = l + r >> 1;
        int s = get_sum(v << 1, l, m, L, R) + get_sum(v << 1 | 1, m, r, L, R);
        merge(S[v], S[v << 1], S[v << 1 | 1]);
        return s;
}

seg get_ans(int v, int l, int r, int L, int R) {
        if (L == l && r == R) return S[v];
        int m = l + r >> 1;
        push(v);
        if (R <= m) return get_ans(v << 1, l, m, L, R);
        else if (L >= m) return get_ans(v << 1 | 1, m, r, L, R);
        seg x;
        merge(x, get_ans(v << 1, l, m, L, m), get_ans(v << 1 | 1, m, r, m, R));
        return x;
}

void build(int v, int l, int r) {
        S[v].tool = r - l;
        if (l + 1 == r) {
                S[v].fi = S[v].last = S[v].jam = b[l];
                S[v].lz = 1;
                S[v].pref = S[v].suf = S[v].ans = (b[l] != 0);
                return;
        }
        int m = l + r >> 1;
        build(v << 1, l, m);
        build(v << 1 | 1, m, r);
        merge(S[v], S[v << 1], S[v << 1 | 1]);
}

signed main() {
        //ios::sync_with_stdio(0), cin.tie(0);
        cin >> n >> q;
        FOR(i, 1, n + 1) cin >> a[i];
        FOR(i, 1, n + 1) b[i - 1] = a[i] - a[i - 1];
        build(1, 0, n);
        FOR(i, 0, q) {
                //print(1, 0, n);
                //cout << endl;
                string c; int l, r, x;
                cin >> c >> l >> r;
                if (c[0] == '?') {
                        int re = 0;
                        if (r > l) re += get_ans(1, 0, n, l, r).ans;
                        re += r - l + 1;
                        cout << re << '\n';
                }
                else if (c[0] == '*') {
                       int lth = get_sum(1, 0, n, 0, l);
                       int rth = get_sum(1, 0, n, 0, r);
                       mult(1, 0, n, l, r); 
                       upd(1, 0, n, l - 1, -2 * lth);
                       if (r < n) upd(1, 0, n, r, 2 * rth);
                }
                else if (c[0] == '+') {
                       cin >> x; 
                       upd(1, 0, n, l - 1, +x);
                       if (r < n) upd(1, 0, n, r, -x);
                }
        }
        cout << endl;
        return 0;
}
//11:42:29
