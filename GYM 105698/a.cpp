#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, k;
int b[509][509];
vector<int> e[250009];
ll f[250009];
int din[250009];
const ll mod = 998244353;
char a[509][509];
vector<string> targets = {"ge", "en", "nshini", "im", "mp", "pa", "ac", "ct"};
void addedge(int u, int v) {
    din[v]++;
    e[u].push_back(v);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string str; cin >> str;
        for (int j = 1; j <= m; j++)
            a[i][j] = str[j - 1];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            k++;
            b[i][j] = k;
            if (a[i][j] == 'g') f[k] = 1;
        }
    }
    int dx[4] = {0,0,-1,1}; int dy[4] = {-1,1,0,0};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            for (auto target : targets) {
                if (a[i][j] != target[0]) continue;

            }
    }
    queue<int> q = {};
    for (int u = 1; u <= k; u++) if (f[u]) q.push(u);
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (auto v : e[u]) {
            f[v] += f[u]; f[v] %= mod;
            din[v]--; if (din[v] == 0) q.push(v);
        }
    }

    return 0;
}