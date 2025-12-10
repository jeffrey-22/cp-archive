#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ff first
#define ss second
typedef long long ll;
typedef vector<int> vi;
int n, x, y, d;
ll f[109][109][109], ans = 0;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> x >> y >> d;
    f[0][x][y] = 1;
    for (int t = 0; t < d; t++) {
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                for (int dx = -1; dx <= 1; dx+= 2) {
                    for (int dy = -1; dy <= 1; dy += 2) {
                        int ax = x + dx;
                        ax = max(ax, 1); ax = min(ax, n);
                        int ay = y + dy;
                        ay = max(ay, 1); ay = min(ay ,n);
                        f[t + 1][ax][ay] += f[t][x][y];
                    }
                }
            }
        }
        int tt = t + 1;
        
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                if (x == y) {
                    ans += f[tt][x][y] * (1ll << ((d - tt) * 2));
                    f[tt][x][y] = 0;
                }
            }
        }
    }
    ll rans = (1ll << (d * 2));
    ll g = __gcd(ans, rans);
    ans /= g, rans /= g;
    cout << ans << '/' << rans << endl;
    return 0;
}