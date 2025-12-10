#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int l, b;
int a[200009], val[400009], vis[400009], f[400009];
vector<int> wire[400009], con[200009];
vector<pair<int, int>> e[400009];
void dfs(int u, vector<int>& comp) {
    comp.push_back(u);
    vis[u] = 1;
    for (auto [v, req] : e[u])
        if (!vis[v])
            dfs(v, comp);
}
void dfscolor(int u, int& ok, int& tot) {
    tot += f[u];
    vis[u] = 1;
    if (val[u] != -1 && val[u] != f[u]) {
        ok = 0;
        return;
    }
    for (auto [v, req] : e[u])
        if (!vis[v]) {
            f[v] = (req - f[u] + 3) % 3;
            dfscolor(v, ok, tot);
            if (!ok) return;
        }
        else {
            if ((f[u] + f[v]) % 3 != req) {
                ok = 0;
                return;
            }
        }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> l >> b;
    string str; cin >> str;
    for (int i = 1; i <= l; i++) {
        if (str[i - 1] == 'R') a[i] = 0;
        else if (str[i - 1] == 'G') a[i] = 1;
        else a[i] = 2;
    }
    for (int i = 1; i <= b; i++) {
        int k; cin >> k;
        while (k--) {
            int x; cin >> x;
            wire[i].push_back(x);
            con[x].push_back(i);
        }
        val[i] = -1;
    }
    for (int i = 1; i <= l; i++) {
        if (sz(con[i]) == 0 && a[i] > 0) {
            cout << "impossible" << endl;
            return 0;
        }
        if (sz(con[i]) == 1) {
            int dest = (3 - a[i]) % 3;
            if (val[con[i][0]] >= 0 && val[con[i][0]] != dest) {
                cout << "impossible" << endl;
                return 0;
            }
            val[con[i][0]] = dest;
        }
        if (sz(con[i]) == 2) {
            int dest = (3 - a[i]) % 3;
            int u = con[i][0], v = con[i][1];
            e[u].push_back({v, dest});
            e[v].push_back({u, dest});
        }
        assert(sz(con[i]) <= 2);
    }
    // for (int i = 1; i <= b; i++) cout << val[i] << " "; cout << endl;
    int ans = 0;
    for (int i = 1; i <= b; i++) {
        if (vis[i]) continue;
        // vis[i] = 1;
        vector<int> comp = {};
        dfs(i, comp);
        int bestc = -1, best = INT_MAX;
        for (int c = 0; c <= 2; c++) {
            for (auto u : comp) vis[u] = 0;
            int ok = 1, tot = 0;
            f[i] = c;
            dfscolor(i, ok, tot);
            if (ok) {
                if (tot < best) {
                    best = tot;
                    bestc = c;
                }
            }
        }
        if (bestc == -1) {
            cout << "impossible" << endl;
            return 0;
        }
        for (auto u : comp) vis[u] = 0;
        int ok = 1, tot = 0;
        f[i] = bestc;
        dfscolor(i, ok, tot);
        ans += best;
    }
    for (int i = 1; i <= b; i++) {
        for (int j = 1; j <= f[i]; j++) {
            for (auto t : wire[i]) a[t]++;
        }
    }
    for (int i = 1; i <= l; i++) assert(a[i] % 3 == 0);
    cout << ans << endl;
}