#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int N = 1e6;
int n;
const ll P = 998244353;
ll modpow(ll x, ll y = P - 2) {
    ll r = 1;
    while (y) {
        if (y & 1ll) r = r * x % P;
        x = x * x % P; y >>= 1ll;
    }
    return r;
}
ll a[1000009], fac[1000009];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fac[0] = 1; for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % P;
    a[0] = 0;
    for (int i = 1; i <= N; i++) a[i] = ((1ll * i + 2ll) * a[i - 1] + 1ll * i * fac[i]) % P;
    int Tt; cin >> Tt;
    while (Tt--) {
        cin >> n;
        ll A = 1ll * n * n % P * fac[n] % P;
        ll B = a[n - 1];
        ll C = 1ll * n * fac[n] % P;
        A -= B; A %= P; A += P; A %= P;
        A *= modpow(C); A %= P;
        cout << A << endl;
    }
    return 0;
}