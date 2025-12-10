#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 105;

int n, a[N][N * 2], b[N][N * 2], c[2][2][2], id[N][N * 2], cnt = 0, vis[N * N * 2], dis[N * N * 2];
vector<int> e[N * N * 2];
void add_edge(int u, int v) {
    if (u == 0 || v == 0) {
        return;
    }
    e[u].emplace_back(v);
    e[v].emplace_back(u);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    c[1][1][1] = c[0][0][0] = 4;
    c[1][1][0] = c[0][0][1] = 2;
    c[0][1][1] = c[1][0][0] = 1;
    c[0][1][0] = c[1][0][1] = 3;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i * 2 + 1; j++) {
            cin >> a[i][j];
        }
    }
    memset(id, 0 ,sizeof(id));
    memset(vis, 0 ,sizeof(vis));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i * 2 + 1; j++) {
            b[i][j] = c[i & 1][j & 1][(j >> 1) & 1];
            if (a[i][j] == b[i][j]) {
                id[i][j] = ++cnt;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i * 2 + 1; j += 2) {
            if (j) {
                add_edge(id[i][j], id[i][j - 1]);
            }
            add_edge(id[i][j], id[i][j + 1]);
            add_edge(id[i][j], id[i + 1][j + 1]);
        }
    }
    
    queue<int>q;
    q.emplace(id[0][0]);
    dis[id[0][0]] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : e[u]) {
            if (vis[v]) {
                continue;
            }
            q.emplace(v);
            vis[v] = 1;
            dis[v] = dis[u] + 1;
        }
    }

    int x, y;
    cin >> x >> y;
    x--, y--;
    if (id[x][y] && vis[id[x][y]]) {
        cout << dis[id[x][y]] << "\n";
    } else {
        cout << "-1\n";
    }

    return 0;
}