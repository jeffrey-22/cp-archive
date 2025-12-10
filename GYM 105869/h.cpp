#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int n, m, tot;
vector<vi> et, eg, egr, teg, tegr;
vector<pii> dedge;
int f[500009], vis[500009], bel[500009], outDeg[500009], sz[500009], newf[500009], bestf[500009], dep[500009];
vector<int> revbel[500009];
set<pair<int, int>> S;
queue<int> Q;
void treecolor(int u, int color) {
    bel[u] = color;
    vis[u] = 1;
    for (auto v : et[u])
        if (!vis[v])
            treecolor(v, color);
}
void dfs1(int u, int totsz, int& root, int father = 0) {
    sz[u] = 1;
    int is_u_ok = 1;
    for (auto v : et[u])
        if (v != -1 && v != father) {
            dfs1(v, totsz, root, u);
            sz[u] += sz[v];
            if (sz[v] > totsz / 2)
                is_u_ok = 0;
        }
    if (totsz - sz[u] > totsz / 2)
        is_u_ok = 0;
    if (is_u_ok)
        root = u;
}
void dfs2(int u, int father = 0) {
    sz[u] = 1;
    dep[u] = dep[father] + 1;
    bestf[u] = f[u];
    for (auto v : et[u]) 
        if (v != -1 && v != father) {
            dfs2(v, u);
            sz[u] += sz[v];
            bestf[u] = max(bestf[u], bestf[v] + 1);
        }
}
void dfs3(int u, int obf, int root, int father) {
    newf[u] = max(newf[u], obf + dep[u] - dep[root]);
    for (auto v : et[u])
        if (v != -1 && v != father)
            dfs3(v, obf, root, u);
}
void solve(int startnode, int totsz) {
    int root = -1;
    dfs1(startnode, totsz, root);
    assert(root != -1);
    // cerr << "tree-solve " << startnode << " with sz = " << totsz << " root = " << root << endl;
    dfs2(root);
    vi realson = {};
    for (auto u : et[root]) if (u != -1) realson.push_back(u);
    if (sz(realson) == 0) return;
    int last = sz(realson) - 1;
    vi maxleft(sz(realson), 0);
    vi maxright(sz(realson), 0);
    maxleft[0] = bestf[realson[0]];
    maxright[last] = bestf[realson[last]];
    for (int i = 1; i <= last; i++) maxleft[i] = max(maxleft[i - 1], bestf[realson[i]]);
    for (int i = last - 1; i >= 0; i--) maxright[i] = max(maxright[i + 1], bestf[realson[i]]);
    newf[root] = max(newf[root], bestf[root]);
    for (int i = 0; i <= last; i++) {
        int ml = 0; if (i > 0) ml = maxleft[i - 1];
        int mr = 0; if (i < last) mr = maxright[i + 1];
        int mv = max(ml, mr) + 1;
        if (last == 0) mv = 0;
        mv = max(mv, f[root]);
        dfs3(realson[i], mv, root, root);
    }
    for (auto son : realson) {
        for (int i = 0; i < sz(et[son]); i++)
            if (et[son][i] == root) {
                et[son][i] = -1;
                solve(son, sz[son]);
            }
    }
}
void process(int t) {
    vector<int>& nodes = revbel[t];
    for (auto u : nodes) newf[u] = f[u], bestf[u] = 0;
    solve(nodes[0], sz(nodes));
    for (auto u : nodes) f[u] = newf[u];
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> m;
        et = vector<vi>(n + 1, vi());
        eg = vector<vi>(n + 1, vi());
        egr = vector<vi>(n + 1, vi());
        teg = vector<vi>(n + 1, vi());
        tegr = vector<vi>(n + 1, vi());
        dedge.clear();
        for (int i = 1; i <= m; i++) {
            int u, v; string st;
            cin >> u >> st >> v;
            if (st[1] == '>') {
                dedge.push_back({u, v});
            }
            else {
                et[u].pb(v);
                et[v].pb(u);
            }
        }
        for (int i = 1; i <= n; i++) vis[i] = f[i] = 0;
        tot = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i]) {
                tot++;
                revbel[tot].clear();
                treecolor(i, tot);
            }
        for (int i = 1; i <= n; i++)
            revbel[bel[i]].push_back(i);
        for (int i = 1; i <= tot; i++)
            outDeg[i] = 0;
        for (auto [uu, vv] : dedge) {
            int u = bel[uu];
            int v = bel[vv];
            eg[u].pb(v);
            egr[v].pb(u);
            outDeg[u]++;
            teg[uu].pb(vv);
            tegr[vv].pb(uu);
        }
        Q = {};
        for (int i = 1; i <= tot; i++)
            if (!outDeg[i]) {
                Q.push(i);
            }
        int ans = 0;
        while (!Q.empty()) {
            auto u = Q.front();
            Q.pop();
            process(u);
            for (auto vv : egr[u]) {
                outDeg[vv]--;
                if (outDeg[vv] == 0) Q.push(vv);
            }
            // cerr << u << " tree-processed" << endl;
            for (auto o : revbel[u]) {
                // cerr << "including: " << o << " with f=" << f[o] << endl;
                ans = max(ans, f[o]);
                for (auto oo : tegr[o]) {
                    f[oo] = max(f[oo], f[o] + 1);
                    // cerr << "  > updated: " << oo << " to f=" << f[oo] << endl;
                }
            }
        }
        // cerr << "tree labels: "; for (int i = 1; i <= n; i++) cerr << bel[i] << " "; cerr << endl;
        // cerr << "f: "; for (int i = 1; i <= n; i++) cerr << f[i] << " "; cerr << endl;

        cout << ans << endl;
    }
    return 0;
}