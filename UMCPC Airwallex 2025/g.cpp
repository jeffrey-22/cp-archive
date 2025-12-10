#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size() 
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> pii; 
typedef vector<int> vi;
bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
    if (btoa[j] == -1) return 1;
    vis[j] = 1; int di = btoa[j];
    for (int e : g[di])
    if (!vis[e] && find(e, g, btoa, vis)) {
    btoa[e] = di;
    return 1;
    }
    return 0;
    }
    int dfsMatching(vector<vi>& g, vi& btoa) {
    vi vis;
    rep(i,0,sz(g)) {
    vis.assign(sz(btoa), 0);
    for (int j : g[i])
    if (find(j, g, btoa, vis)) {
    btoa[j] = i;
    break;
    }
    }
    return sz(btoa) - (int)count(all(btoa), -1);
    }
const int N = 100010;
int tot = 0, source, sink;
int a[N], b[N], G[N], nodeid[N], vis[N], dist[609][609], tmp_dist[N], source_cap[609], sink_cap[609], backid[609], connected[309][309];
vector<int> mpa[N], mpb[N];
int n, m;
vector<int> e[N];
vector<int> A = {}, B = {}, factory = {};
void bfs(int st) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) tmp_dist[i] = n + 2;
    queue<int> q = {}; q.push(st);
    vis[st] = 1; tmp_dist[st] = 0;
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (auto v : e[u])
            if (!vis[v]) {
                tmp_dist[v] = tmp_dist[u] + 1;
                vis[v] = 1;
                q.push(v);
            }
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > 0)
            A.pb(i);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (b[i] > 0)
            B.pb(i);
        else if (b[i] == -1)
            factory.pb(i);
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        e[u].pb(v);
        e[v].pb(u);
    }
    for (int i = 1; i <= n; i++) G[i] = n + 1;
    queue<int> q = {};
    for (auto x : factory) q.push(x);
    for (auto x : factory) G[x] = 0, vis[x] = 1;
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (auto v : e[u])
            if (!vis[v]) {
                G[v] = G[u] + 1;
                vis[v] = 1;
                q.push(v);
                // cout << "G establish " << u << "-" << v << " neting G[v] = " << G[v] << endl;
            }
    }
    // cout << "G: "; for (int i = 1; i <= n; i++) cout << G[i] << " "; cout << endl;
    memset(vis, 0, sizeof(vis));
    for (auto u : A) {
        if (!nodeid[u]) {
            nodeid[u] = ++tot;
            backid[tot] = u;
        }
        source_cap[nodeid[u]] = a[u];
    }
    for (auto u : B) {
        if (!nodeid[u]) {
            nodeid[u] = ++tot;
            backid[tot] = u;
        }
        sink_cap[nodeid[u]] = b[u];
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= tot; j++)
            dist[i][j] = n + 2;
    for (auto u : A) {
        bfs(u);
        for (auto v : B)
            dist[nodeid[u]][nodeid[v]] = dist[nodeid[v]][nodeid[u]] = tmp_dist[v];
    }
    // cout << "Nodes: "; for (int i = 1; i <= tot; i++) cout << backid[i] << " "; cout << endl;
    // cout << "Dist:" << endl;
    // for (int i = 1; i <= tot; i++) {
    //     for (int j = 1; j <= tot; j++)
    //         cout << dist[i][j] << " ";
    //     cout << endl;
    // }
    
    int cnta = 0, cntb = 0;
    
    vector<vi> FG = {{}};
    for (auto x : A) {
        while (a[x] > 0) {
            a[x]--;
            mpa[x].pb(++cnta);
            FG.pb({});
        }
    }
    for (auto x : B) {
        while (b[x] > 0) {
            b[x]--;
            mpb[x].pb(++cntb);
        }
    }
    assert(cnta <= 300);
    assert(cntb <= 300);
    int ans = 0;
    for (int i = 1; i <= tot; i++)
        if (G[backid[i]] <= n) {
            for (int j = 1; j <= tot; j++)
                if (
                    dist[i][j] < G[backid[j]]
                    // &&
                    // (dist[i][j] > 0 || G[backid[j]] > 1)
                ) {
                    for (auto aa : mpa[backid[i]])
                        for (auto bb : mpb[backid[j]])
                            if (!connected[aa][bb])
                                FG[aa].pb(bb), connected[aa][bb] = 1;
                    // cout << backid[i] << " " << backid[j] << " connected:" << endl;
                    // cout << sz(mpa[backid[i]]) << " " << sz(mpb[backid[j]]) << "  !" << endl;
                }
        }
        else
            ans += mpa[backid[i]].size();
    for (int i = 1; i <= tot; i++)
        if (G[backid[i]] > n)
            for (auto aa : mpa[backid[i]])
                FG[aa].clear();
    vi btoa(cntb + 1, -1);
    cout << ans + dfsMatching(FG, btoa) << endl;
    return 0;
}
/*
9 10
0 0 0 200 50 0 0 0 15
-1 50 100 0 100 -1 10 10 10
0 1
0 2
1 3
2 4
3 4
0 5
5 6
6 7
7 8
4 5

*/