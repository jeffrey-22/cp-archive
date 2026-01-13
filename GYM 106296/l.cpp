#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int(x).size())
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int n, root;
vector<int> e[59];
vector<tuple<int, int, char>> robots;
int a[59][59];
int deg[59], sz[59], par[59];
void dfs(int u, int fa = 0) {
    par[u] = fa;
    sz[u] = 1;
    for (auto v : e[u])
        if (v != fa) {
            dfs(v, u);
            sz[u] += sz[v];
        }
}
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
char dt[4] = {'C', 'A', 'B', 'D'};
void paint(int u, int x = n + 1, int y = 1, int t = 0) {
    robots[u - 1] = {x, y, dt[t]};
    a[x][y] = -1;
    int wx = x, wy = y;
    for (;;) {
        wx += dx[t], wy += dy[t];
        if (wx < 1 || wy < 1 || wx > n + 1 || wy > n + 1) break;
        if (a[wx][wy] != 0) break;
        a[wx][wy] = 1;
    }
    int tx = x, ty = y;
    int nt = (t + 1) % 4;
    for (auto v : e[u])
        if (v != par[u]) {
            if (t == 0) {
                tx -= sz[v];
                paint(v, tx, ty + 1, nt);
                ty += sz[v];
            }
            else if (t == 1) {
                ty += sz[v];
                paint(v, tx + 1, ty, nt);
                tx += sz[v];
            }
            else if (t == 2) {
                tx += sz[v];
                paint(v, tx, ty - 1, nt);
                ty -= sz[v];
            }
            else {
                ty -= sz[v];
                paint(v, tx - 1, ty, nt);
                tx -= sz[v];
            }
        }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n;
        robots.clear();
        for(int i = 1; i <= n; i++) robots.push_back({0, 0, 0});
        for (int i = 1; i <= n; i++) e[i].clear();
        for (int i = 1; i <= n; i++) deg[i] = par[i] = 0;
        for (int i = 1; i <= n + 1; i++)
            for (int j = 1; j <= n + 1; j++)
                a[i][j] = 0;
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            deg[u]++, deg[v]++;
            e[u].push_back(v); e[v].push_back(u);
        }
        root = 1;
        for (int i = 1; i <= n; i++) if (deg[i] > 1) {root = i; break;}
        dfs(root);
        paint(root);
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= n + 1; j++)
                if (a[i][j] == 1) cout << '#'; else cout << '.';
            cout << endl;
        }
        for (auto [x, y, c] : robots)
            cout << x << " " << y << " " << c << endl;
    }
}