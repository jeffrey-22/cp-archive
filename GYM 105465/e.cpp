#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n;
vector<int> e[200009];
int f[200009], g[200009];
void dfs(int u, int fa = 0) {
    int sumf = 0, sumg = 0;
    for (auto v : e[u])
        if (v != fa)
            dfs(v, u);
    for (auto v : e[u])
        if (v != fa)
            sumf += f[v], sumg += g[v];
    f[u] = sumf;
    if (sumg == 0) {
        g[u] = 1;
    } else {
        f[u] += (sumg - 1) * 2;
        f[u]++;
        g[u] = 0;
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1);
    if (g[1]) f[1] += 2;
    cout << f[1] << endl;
}