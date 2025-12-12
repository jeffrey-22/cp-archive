#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < b; i++)
int n, k, m, ans1 = INT_MAX, ans2 = INT_MAX;
vector<int> e[100009];
int dfslist[100009], bfslist[100009], vis[100009], father[100009], dep[100009], fatid[100009];
int dfsid[100009], bfsid[100009];
void dfsfilllist(int u, int fa = -1) {
    father[u] = fa;
    if (u == 1) dep[u] = 1; else dep[u] = dep[fa] + 1;
    dfslist[++m] = u;
    for (int i = 0; i < sz(e[u]); i++) {
        auto v = e[u][i];
        if (v != fa) {
            fatid[v] = i;
            dfsfilllist(v, u);
        }
    }        
}
void bfsfilllist() {
    queue<int> q = {};
    q.push(1); bfslist[++m] = 1; vis[1] = 1;
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (auto v : e[u])
            if (!vis[v]) {
                vis[v] = 1;
                bfslist[++m] = v;
                q.push(v);
            }
    }
}
int cntdep(int u, int deplim) {
    if (dep[u] > deplim) return 0;
    int ret = 1;
    for (auto v : e[u])
        if (v != father[u]) {
            ret += cntdep(v, deplim);
        }
    return ret;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    m = 0; dfsfilllist(1); for (int i = 1; i <= n; i++) dfsid[dfslist[i]] = i;
    m = 0; bfsfilllist(); for (int i = 1; i <= n; i++) bfsid[bfslist[i]] = i;
    vector<int> anc = {};
    int u = k; 
    while (u != -1) {
        anc.push_back(u);
        u = father[u];
    }
    for (auto u : anc) {
        ans1 = min(ans1, bfsid[u] + dfsid[k] - dfsid[u]);
    }
    cout << ans1 << endl;
    int tot = 0;
    for (int i = 0; i < sz(anc); i++) {
        // cerr << "at anc " << anc[i] << " tot = " << tot << " dfsid = " << dfsid[anc[i]] << endl;
        ans2 = min(ans2, tot + dfsid[anc[i]]);
        if (i != sz(anc) - 1) {
            int nxt = anc[i + 1];
            assert(father[anc[i]] == nxt);
            for (int j = 0; j < fatid[anc[i]]; j++) {
                if (e[nxt][j] == father[nxt]) continue;
                int sum = cntdep(e[nxt][j], dep[k]);
                tot += sum;
                // cerr << "adding tot from " << e[nxt][j] << " for dep <= " << dep[k] << " for " << sum << endl;
            }
            for (int j = fatid[anc[i]] + 1; j < sz(e[nxt]); j++) {
                if (e[nxt][j] == father[nxt]) continue;
                int sum = cntdep(e[nxt][j], dep[k] - 1);
                tot += sum;
                // cerr << "adding tot from " << e[nxt][j] << " for dep <= " << dep[k] - 1 << " for " << sum << endl;
            }
            tot++;
        }
    }
    cout << ans2 << endl;
}