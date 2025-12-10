#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int lcalim = 16;
int n, q, cap;
int fa[200009][17], dep[200009], sz[200009], ans[200009];
int sumc[200009][17];
vector<pair<int, int>> e[200009];
tuple<int, int, int> nxt[200009];
void dfs1(int u, int totsz, int& root, int father = 0) {
    sz[u] = 1;
    int is_u_ok = 1;
    for (auto [v, c] : e[u])
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
    // cerr << "Considering" << u << endl;
}
void dfs2(int u, int father = 0) {
    dep[u] = dep[father] + 1;
    fa[u][0] = father;
    sz[u] = 1;
    for (int i = 1; i <= lcalim; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = 1; i <= lcalim; i++)
        sumc[u][i] = min(cap + 1, sumc[u][i - 1] + sumc[fa[u][i - 1]][i - 1]);
    for (auto [v, c] : e[u])
        if (v != -1 && v != father) {
            sumc[v][0] = c;
            dfs2(v, u);
            sz[u] += sz[v];
        }
}
void dfs3(int u, int father = 0) {
    int fuelleft = cap;
    if (sumc[u][lcalim] <= fuelleft) {
        nxt[u] = {0, u, sumc[u][lcalim]};
    } else {
        int w = u;
        for (int i = lcalim; i >= 0; i--)
            if (sumc[w][i] <= fuelleft) {
                fuelleft -= sumc[w][i];
                w = fa[w][i];
            }
        auto [totw, endpoint, endsum] = nxt[w];
        nxt[u] = {totw + 1, endpoint, endsum};
    }
    for (auto [v, c] : e[u])
        if (v != -1 && v != father) {
            dfs3(v, u);
        }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 0; i <= lcalim; i++)
        if ((1 << i) & (dep[u] - dep[v]))
            u = fa[u][i];
    if (u == v) return u;
    for (int i = lcalim; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
void solve(int tot, int onenode, vector<tuple<int, int, int>> &queries) {
    // cerr << "solving for " << onenode << endl;
    int root = -1;
    dfs1(onenode, tot, root);
    assert(sz[onenode] == tot);
    assert(root != -1);
    sumc[root][0] = 0;
    // cerr << "dfs1 complete!" << endl;
    dfs2(root);
    // cerr << "dfs2 complete!" << endl;
    dfs3(root);
    // cerr << "dfs3 complete!" << endl;
    map<int, vector<tuple<int, int, int>>> nextQueries = {};
    vector<tuple<int, int, int>> currentQueries = {};
    for (auto [u, v, qid] : queries) {
        int w = lca(u, v);
        if (w == root) {
            currentQueries.push_back({u, v, qid});
        } else {
            for (int i = 0; i <= lcalim; i++)
                if ((1 << i) & (dep[w] - dep[root] - 1))
                    w = fa[w][i];
            if (!nextQueries.count(w))
                nextQueries[w] = vector<tuple<int, int, int>>();
            nextQueries[w].push_back({u, v, qid});
        }
    }
    // cerr << "query division complete!" << endl;
    for (auto [u, v, qid] : currentQueries) {
        if (dep[u] < dep[v]) swap(u, v);
        auto [cntA, pointA, leftA] = nxt[u];
        auto [cntB, pointB, leftB] = nxt[v];
        int cntC = 0;
        if (leftA + leftB <= cap)
            cntC = 0;
        else
            cntC = 1;
        // cerr << "Handling query " << qid << " " << u << "->" << v << endl;
        // cerr << "left A = " << leftA << " left B = " << leftB << endl;
        // cerr << "cnt A B C =" << cntA << " " << cntB << " " << cntC << endl;
        ans[qid] = cntA + cntB + cntC;
    }
    // cerr << "query processing complete!" << endl;
    
    for (auto [nxtson, c] : e[root])
        if (nxtson != -1) {
            for (int t = 0; t < sz(e[nxtson]); t++) {
                auto [v, cc] = e[nxtson][t];
                if (v == root) {e[nxtson][t] = {-1, -1}; break;}
            }
            solve(sz[nxtson], nxtson, nextQueries[nxtson]);
        }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> q >> cap;
        for (int i = 0; i <= n; i++) e[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            e[u].pb({v, c});
            e[v].pb({u, c});
        }
        vector<tuple<int, int, int>> queries = {};
        for (int i = 1; i <= q; i++) {
            int u, v;
            cin >> u >> v;
            queries.push_back({u, v, i});
        }
        solve(n, 1, queries);
        for (int i = 1; i <= q; i++) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}