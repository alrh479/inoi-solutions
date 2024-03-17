#include "bits/stdc++.h"
using namespace std;
#define int long long
const int N = 5e5 + 50;
const long long INF = 1ll << 60;
const int ALPHA = 'z' - 'a' + 1;
int ch[N][ALPHA], ptr, A, B, dist[N][2], loc[N], pr[N], n;
string s[N];
vector<int> a[N];

int pushT(const string &s, int i) {
        int v = 0;
        for (const auto &c: s) {
                if (!ch[v][c - 'a']) {
                        ch[v][c - 'a'] = ++ptr;
                        pr[ch[v][c - 'a']] = v;
                }
                v = ch[v][c - 'a'];
        }
	int prv = loc[v];
	if (prv != -1) {
		for (int j = 0; j <= s.size(); j++) 
			a[i][j] = min(a[i][j], a[prv][j]);
	}
	loc[v] = i;
	return v;
}

signed main() {
        ios::sync_with_stdio(0);
        cin.tie(0);
	memset(loc, -1, sizeof loc);
	for (int i = 0; i < N; i++) dist[i][0] = dist[i][1] = INF;

        cin >> n;
        for (int i = 0; i < n; i++) {
                cin >> s[i];
                a[i].resize(s[i].size() + 1);
                for (int j = 0; j <= s[i].size(); j++) cin >> a[i][j];
        }
        cin >> B >> A;
        A--, B--;
        int v = pushT(s[A], A);
        for (int i = 0; i < n; i++) if (i != A)
                pushT(s[i], i);
        int locB = pushT(s[B], B);

	priority_queue<array<int, 3>> S; //[-, ]
	dist[v][1] = dist[v][0] = a[A][s[A].size()];

	S.push({-dist[v][1], v, 1});
	S.push({-dist[v][0], v, 0});

	for (int j = s[A].size() - 1; j >= 0; j--) {
		v = pr[v];
		dist[v][0] = a[A][j];
		S.push({-dist[v][0], v, 0});

		for (int k = 0; k < ALPHA; k++) if (ch[v][k] && k != s[A][j] - 'a') {
			int u = ch[v][k];
			dist[u][1] = a[A][j];
			S.push({-dist[u][1], u, 1});
		}
	}

	while (S.size()) {
		auto o = S.top();
		S.pop();
		int v = o[1];
		int d = -o[0];
		int st = o[2];
		assert(d >= dist[v][st]);
		if (d != dist[v][st]) continue;

		if (st) {
			for (int k = 0; k < ALPHA; k++) if (ch[v][k]) {
				int u = ch[v][k];
				if (dist[u][1] > dist[v][1]) {
					dist[u][1] = dist[v][1];
					S.push({-dist[u][1], u, 1});
				}
			}
		}

		if (loc[v] == -1) continue;
		int x = loc[v];
		int tv = v;

		for (int j = s[x].size() - 1; j >= 0; j--) {
			tv = pr[tv];
			if (dist[v][st] + a[x][j] < dist[tv][0]) {
				dist[tv][0] = dist[v][st] + a[x][j];
				S.push({-dist[tv][0], tv, 0});
			}
			for (int k = 0; k < ALPHA; k++) if (ch[tv][k] && k != s[x][j] - 'a') {
				int u = ch[tv][k];
				if (dist[v][st] + a[x][j] < dist[u][1]) {
					dist[u][1] = dist[v][st] + a[x][j];
					S.push({-dist[u][1], u, 1});
				}
			}
		}
	}

	cout << min(dist[locB][0], dist[locB][1]) << '\n';
}
