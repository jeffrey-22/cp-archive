#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
ll a, b, x;
const ll P = 998244353;
map<ll, int> p2;
ll modpow(ll x, ll y = P - 2) {
    ll r = 1;
    while (y) {
        if (y & 1ll) r = r * x % P;
        x = x * x % P; y >>= 1ll;
    }
    return r;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    for (int i = 0; i <= 62; i++) p2[1ll << (1ll * i)] = i;
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> a >> b;
        ll g = __gcd(a, b); a /= g, b /= g;
        ll s = a + b;
        x = -1;
        ll y = 0;
        if (p2.count(s) > 0) {
            ll t = s / 2ll;
            x = p2[s] - 1;
        }
        
        ll ans = 0;
        if (x == -1)
            ans = 2;
        else
            ans = 2 - modpow(modpow(2, x));
        ans = (ans % P + P) % P;
        cout << ans << endl;
    }
    return 0;
}