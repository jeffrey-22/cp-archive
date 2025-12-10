#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;

int n, m;
vector<int> e[N][2];
map<int, bool> mp[N][2];
void add_edge(int u, int v, int w) {
    e[u][w].emplace_back(v);
    mp[u][w][v] = 1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    int ans = n;
    for (int i = 1; i <= n; i++) {
        for (int v : e[i][0]) {
            if (i > v) {
                continue;
            }
            ans += mp[v][1].count(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int u : e[i][0]) {
            for (int v : e[i][1]) {
                ans += mp[u][0].count(v) && mp[v][1].count(u);
            }
        }
    }
    for (int u = 1; u <= n; u++) {
        for (int v : e[u][0]) {
            if (v > u) {
                continue;
            }
            for (int x : e[u][0]) {
                if (x == u) {
                    continue;
                }
                for (int y : e[v][0]) {
                    if (y == u || y == x) {
                        continue;
                    }
                    ans += mp[u][1].count(x) && mp[x][1].count(y) && mp[y][1].count(v);
                    ans += mp[u][1].count(y) && mp[y][1].count(x) && mp[x][1].count(v);
                }
            }
        }
    }
    cout << ans << "\n";

    return 0;
}