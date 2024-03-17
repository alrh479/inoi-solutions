#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define int int64_t
const int64_t INF = 1ll << 60;
const int N = 1e5 + 5;
int b[N], in[N], nx[N], n, k, a[N];
vector<int> adj[N];
set<int> S;

void rec(int i) {
        if (i == n + 1) {
                k--;
                if (!k) {
                        FOR(i, 0, n)
                                cout << a[i] << ' ';
                        cout << '\n';
                        exit(0);
                }
                return;
        }
        if (!S.size()) 
                return;
        auto it = S.begin();
        while (it != S.end()) {
                int x = *it;
                S.erase(x);
                for (auto u: adj[x]) {
                        in[u]--;
                        if (!in[u])
                                S.insert(u);
                }
                a[x] = i;
                rec(i + 1);
                S.insert(x);
                for (auto u: adj[x]) {
                        if (!in[u])
                                S.erase(u);
                        in[u]++;
                }
                it = S.upper_bound(x);
        }
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        cin >> n >> k;
        FOR(i, 0, n) {
                cin >> b[i];
                b[i] = (b[i] == -1 ? INF : b[i]);
        }
        vector<int> st;
        for (int i = n - 1; i >= 0; i--) {
                while (st.size() && b[st.back()] < b[i]) st.pop_back();
                if (st.size() && b[i] != INF) {
                        adj[i].push_back(st.back());
                        in[st.back()]++;
                }
                st.push_back(i);
        }
        for (int i = n - 1; i >= 0; i--) {
                if (b[i] == INF) {
                        FOR(j, i + 1, n) {
                                adj[j].push_back(i);
                                in[i]++;
                                if (b[j] == INF) 
                                        break;
                        }
                }
                else {
                        if (nx[b[i] - 1]) {
                                FOR(j, i + 1, nx[b[i] - 1] + 1) {
                                        adj[j].push_back(i);
                                        in[i]++;
                                }
                        }
                        else if (b[i] > 1) {
                                cout << -1;
                                return 0;
                        }
                        nx[b[i]] = i;
                }
        }
        FOR(i, 0, n) 
                if (!in[i])
                        S.insert(i);
        rec(1);
        cout << -1;
}
//11:28:05
