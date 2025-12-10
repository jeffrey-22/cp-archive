#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int lim = 500, totlim = 100000;
int n, m;
vector<int> a[100009];
vector<ll> f[100009], F[100009];
vector<pair<int, int>> pos[100009];
const ll mod = 998244353;
ll fac[100009], ifac[100009];
ll qpow(ll x, ll y = mod - 2) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return r;
}
ll C(ll n, ll m){if (n < 0 || m < 0 || m > n) return 0;return fac[n] * ifac[m] % mod * ifac[n - m] % mod;}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    fac[0] = 1;
    for (ll i = 1; i <= totlim; i++) fac[i] = fac[i - 1] * i % mod;
    for (ll i = 0; i <= totlim; i++) ifac[i] = qpow(fac[i]);
    int Tt; cin >> Tt;
    while (Tt--) {
        cin >> n >> m;
        for (int i = 0; i <= n; i++) {
            a[i] = vector<int>(m + 1, 0);
            f[i] = vector<ll>(m + 1, 0ll);
            F[i] = vector<ll>(m + 1, 0ll);
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        for (int i = 1; i <= n * m; i++)
            pos[i].clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                pos[a[i][j]].push_back({i, j});
        for (int v = 1; v <= n * m; v++)
            if (pos[v].size() > lim) {
                if (a[1][1] == v) {
                    F[1][1] = 1;
                    f[1][1] = 0;
                } else {
                    f[1][1] = 1;
                }
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= m; j++) {
                        if (i == 1 && j == 1) continue;
                        if (a[i][j] == v) {
                            F[i][j] = (f[i - 1][j] + f[i][j - 1]) % mod;
                            f[i][j] = 0;
                        } else {
                            f[i][j] = (f[i - 1][j] + f[i][j - 1]) % mod;
                        }
                    }
            } else {
                sort(all(pos[v]));
                for (int x = 0; x < sz(pos[v]); x++) {
                    auto [cx, cy] = pos[v][x];
                    ll tot = C(cx - 1 + cy - 1, cx - 1);
                    ll delta = 0;
                    for (int y = 0; y < x; y++)
                        if (pos[v][y].first <= cx && pos[v][y].second <= cy) {
                            ll dx = cx - pos[v][y].first;
                            ll dy = cy - pos[v][y].second;
                            delta += F[pos[v][y].first][pos[v][y].second] * C(dx + dy, dx);
                            delta %= mod;
                        }
                    F[cx][cy] = (tot - delta + mod) % mod;
                }
            }
        ll ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                // cerr << i << " " << j << " = " << F[i][j] << endl;
                ans += F[i][j] * C(n - i + m - j, n - i);
                ans %= mod;
            }
        cout << ans << endl;
    }
}