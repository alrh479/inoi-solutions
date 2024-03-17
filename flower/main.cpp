#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define int long long
const int64_t INF = 1ll << 60;
const int N = 2e5 + 50;
const int H = 1e6;
int a[N], b[N], n, q, h[N], mn[N << 2], mx[N << 2], sum[N << 2], ans, S[N << 2], ps[N], lft[N], nx[N], mnlft[N << 2];

void push(int v) {
        if (mn[v] == mx[v]) {
                mn[v << 1] = mx[v << 1] = mn[v << 1 | 1] = mx[v << 1 | 1] = mn[v];
        }
}

void add(int r, int d) {
        r++;
        for (; r < N; r += r & -r)
                h[r] = max(h[r], d);
}

int get(int r) {
        r++;
        int re = 0;
        for (; r; r &= (r - 1))
                re = max(re, h[r]);
        return re;
}

void build(int v, int l, int r) {
        if (l + 1 == r) {
                mn[v] = mx[v] = get(l);
                S[v] = b[l];
                mnlft[v] = (lft[l] != -1 ? lft[l] : INF);
        }
        else {
                int m = l + r >> 1;
                build(v << 1, l, m);
                build(v << 1 | 1, m, r);
                mn[v] = min(mn[v << 1], mn[v << 1 | 1]);
                mx[v] = max(mx[v << 1], mx[v << 1 | 1]);
                S[v] = S[v << 1] + S[v << 1 | 1];
                mnlft[v] = min(mnlft[v << 1], mnlft[v << 1 | 1]);
        }
}

int update(int v, int l, int r, int L, int R, int x) {
        if (r <= L || R <= l || mn[v] >= x) return INF;
        if (L <= l && r <= R && mn[v] == mx[v]) {
                ans += S[v] * (x - mx[v]);
                mn[v] = mx[v] = x;
                return mnlft[v];
        }
        push(v);
        int m = l + r >> 1;
        int re = min(update(v << 1, l, m, L, R, x), update(v << 1 | 1, m, r, L, R, x));
        mn[v] = min(mn[v << 1], mn[v << 1 | 1]);
        mx[v] = max(mx[v << 1], mx[v << 1 | 1]);
        return re;
}
int get(int v, int l, int r, int ind) {
        if (l + 1 == r) {
                return mn[v];
        }
        push(v);
        int m = l + r >> 1;
        if (ind < m)
                return get(v << 1, l, m, ind);
        else
                return get(v << 1 | 1, m, r, ind);
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        cin >> n >> q;
        FOR(i, 0, n) {
                cin >> a[i];
                add(i, a[i]);
        }
        FOR(i, 0, n)
                cin >> b[i];
        partial_sum(b, b + n, ps + 1);
        memset(lft, -1, sizeof lft);
        vector<int> st;
        for (int i = n; i >= 0; i--) {
                while (st.size() && ps[st.back()] <= ps[i])
                        st.pop_back();
                nx[i] = (st.size() ? st.back() : -1);
                st.push_back(i);
        }
        for (int i = n - 1; i >= 0; i--) {
                if (b[i] <= 0) {
                        if (nx[i] == -1) {
                                add(i, H);
                        }
                        else {
                                lft[nx[i] - 1] = i;
                        }
                }
        }
        for (int i = n - 1; i >= 0; i--)
                if (lft[i] != -1)
                        add(lft[i], get(i));
        build(1, 0, n);
        int sum = 0;
        FOR(i, 0, n) {
                ans += b[i] * get(i);
                sum -= b[i] * a[i];
        }
        while (q--) {
                int x, y;
                cin >> x >> y;
                --x;
                a[x] += y;
                sum -= y * b[x];
                int mnlft = update(1, 0, n, x, n, a[x]);
                if (mnlft != INF)
                        update(1, 0, n, mnlft, n, get(1, 0, n, x));

                cout << ans + sum << '\n';
        }
}
//13:24:25
