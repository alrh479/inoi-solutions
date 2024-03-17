#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
const int64_t INF = 1 << 30;
const int N = 1e6 + 5;
const int NWN = 63;
const int M = 20;
int dist[1 << M][NWN], pr[N][M], msk[N][M], h[N], s, t, U[NWN], V[NWN], label[N], W[NWN][NWN], MSK[NWN][NWN], n;
bool yes[N], seen[NWN];
vector<array<int, 2>> adj[N];
vector<int> key[N];

void dfs(int v, int p) {
        pr[v][0] = p;
        FOR(i, 1, M) {
                pr[v][i] = pr[pr[v][i - 1]][i - 1];
                msk[v][i] = msk[pr[v][i - 1]][i - 1] | msk[v][i - 1];
        }
        for (auto P: adj[v]) {
                int u = P[0], w = P[1];
                if (u == p) continue;
                h[u] = h[v] + 1;
                msk[u][0] = w;
                dfs(u, v);
        }
}
array<int, 2> LCA(int u, int v) {
        int mask = 0;
        if (h[u] > h[v]) swap(u, v);
        for (; h[u] != h[v]; v = pr[v][__lg(h[v] - h[u])])
                mask |= msk[v][__lg(h[v] - h[u])];
        if (u == v)
                return {u, mask};
        for (int i = M - 1; i >= 0; i--) {
                if (pr[v][i] != pr[u][i]) {
                        mask |= msk[v][i];
                        mask |= msk[u][i];
                        v = pr[v][i];
                        u = pr[u][i];
                }
        }
        assert(pr[v][0] == pr[u][0]);
        mask |= msk[u][0];
        mask |= msk[v][0];
        return {pr[v][0], mask};
}

signed main() {
        ios::sync_with_stdio(0), cin.tie(0);
        cin >> n >> s >> t;
        s--;
        t--;
        int E = 0;
        FOR(i, 1, n) {
                int u, v, w, ww = 0;
                cin >> u >> v >> w;
                u--;
                v--;
                w--;
                if (w >= 0) {
                        yes[u] = yes[v] = yes[w] = true;
                        U[E] = u;
                        V[E] = v;
                        ww = 1 << E;
                        key[w].push_back(E);
                        ++E;
                }
                adj[v].push_back({u, ww});
                adj[u].push_back({v, ww});
        }
        dfs(s, s);
        vector<int> node;
        yes[s] = yes[t] = true;
        FOR(i, 0, n) if (yes[i]) 
                node.push_back(i);
        assert(node.size() < NWN);

        FOR(i, 0, node.size()) {
                int u = node[i];
                label[u] = i;
                FOR(j, 0, node.size()) {
                        int v = node[j];
                        auto P = LCA(u, v);
                        W[i][j] = h[u] + h[v] - 2 * h[P[0]];
                        MSK[i][j] = P[1];
                }
        }
        FOR(i, 0, 1 << M) 
                fill(dist[i], dist[i] + NWN, INF);
        dist[0][label[s]] = 0;
        FOR(i, 0, 1 << M) {
                memset(seen, 0, sizeof seen);
                FOR(k, 0, node.size()) {
                        int v = -1;
                        FOR(j, 0, node.size()) if (!seen[j] && (v == -1 || dist[i][j] < dist[i][v]))
                                v = j;
                        seen[v] = true;
                        if (dist[i][v] >= INF)
                                break;
                        for (auto e: key[node[v]]) {
                                int u = (h[U[e]] < h[V[e]] ? U[e] : V[e]);        
                                u = label[u];
                                if ((MSK[v][u] | i) == i) {
                                        int nwm = i | (1 << e);
                                        if (dist[nwm][u] > dist[i][v] + W[u][v]) {
                                                dist[nwm][u] = dist[i][v] + W[u][v];
                                        }
                                }
                        }
                        FOR(u, 0, node.size()) if ((MSK[v][u] | i) == i) {
                                if (dist[i][v] + W[v][u] < dist[i][u]) {
                                        dist[i][u] = dist[i][v] + W[v][u];
                                }
                        }
                }
        }
        int mn = INF;
        FOR(i, 0, 1 << M)
                mn = min(mn, dist[i][label[t]]);
        cout << (mn == INF ? -1 : mn) << '\n';
}
//09:42:20
