#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const ll LIM = 1ll * 200001 * 1000000000ll;
ll n, m;
ll x, y, space;
pair<ll, ll> item[200009];
const ll mod = 998244353;
ll qpow(ll x, ll y = mod - 2) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return r;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt; cin >> Tt;
    while (Tt--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> item[i].second >> item[i].first;
        sort(item + 1, item + n + 1);
        reverse(item + 1, item + n + 1);
        for (int i = 1; i <= n; i++)
            swap(item[i].first, item[i].second);
        x = 0, y = item[1].second;
        space = 0;
        for (int i = 1; i <= n; i++) {
            auto [a, b] = item[i];
            int done = 0;
            if (x > 0) {
                while (y > b) {
                    y--;
                    x <<= 1ll;
                    if (x >= LIM) {
                        done = 1;
                        break;
                    }
                }
                if (done) break;
                if (x >= a) {
                    x -= a;
            // cout << a << " " << b << ": " << space << " ex=" << x << "*2^" << y << endl;
                    continue;
                }
            }
            a -= x;
            space += ((a + m - 1) / m) * qpow(2, b);
            space %= mod;
            x = m - a % m; y = b;
            if (x == m) x = 0;
            // cout << a << " " << b << ": " << space << " ex=" << x << "*2^" << y << endl;
        }
        cout << space << endl;
    }
}