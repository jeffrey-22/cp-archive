#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int mod = 998244353;

int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1LL * res * a % mod;
        }
        a = 1LL * a * a % mod;
        b /= 2;
    }
    return res;
}
int n, dep[N], fac[N], inv[N];
void init(int n) {
    for (int i = fac[0] = 1; i <= n; i++) {
        fac[i] = 1LL * fac[i - 1] * i % mod;
    }
    inv[n] = power(fac[n], mod - 2);
    for (int i = n; i >= 1; i--) {
        inv[i - 1] = 1LL * inv[i] * i % mod;
    }
}
vector<int> e[N], f[N];
void dfs(int u) {
    f[u].assign(dep[u] + 2, 0);
    for (int i = 0; i <= dep[u] + 1; i++) {
        f[u][i] = inv[i];
    }
    for (int v : e[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
        vector<int>g(dep[u] + 2);
        for (int i = 0; i <= dep[u] + 1; i++) {
            for (int j = 0; j <= dep[v] && i + j <= dep[u] + 1; j++) {
                g[i + j] = (g[i + j] + 1LL * f[u][i] * f[v][j]) % mod;
            }
        }
        f[u].swap(g);
    }
//    cerr << u << ":";
    for (int i = 0; i <= dep[u]; i++) {
        f[u][i] = f[u][i + 1];
//        cerr << f[u][i] << " \n"[i == dep[u]]; 
    }
    f[u].pop_back();
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n;
    init(n);
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        e[fa].emplace_back(i);
    }
    dfs(1);
    int ans = 1LL * f[1][0] * fac[n] % mod;
    cout << ans << "\n";

    return 0;
}