#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define pb push_back
const ll lim = 1000000000000ll;
const ll P = 998244353;
const ll Q = 2000000000ll;
int n;
ll a[200009];
ll ans = 0, S0, S1, S2;
vector<tuple<ll, ll, int>> C; // contribution of ai <= val, *= coeff, of power int (val, coeff, power)
void add(ll l, ll r, ll d) {
    C.pb({l - 1, - (d * d % P), 0});
    C.pb({r, d * d % P, 0});
    C.pb({l - 1, -1, 2});
    C.pb({r, 1, 2});
    C.pb({l - 1, 2ll * d % P, 1});
    C.pb({r, - 2ll * d % P, 1});
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int Tt; cin >> Tt;
    while (Tt--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a + 1, a + n + 1);
        C.clear();
        ans = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] >= Q) {
                add(1, a[i] - 1, 0);
                for (int k = 1;; k++) {
                    ll l = a[i] * k + 1;
                    ll r = a[i] * (k + 1) - 1;
                    if (l > lim) break;
                    r = min(r, lim);
                    add(l, r, 1ll * k * a[i] % P);
                }
            } else {
                for (int j = 1; j <= n; j++) {
                    ll val = a[j] % a[i] % P;
                    ans = (ans + val * val) % P;
                }
            }
        }
        sort(all(C));
        S0 = 0, S1 = 0, S2 = 0;
        int p = 0;
        for (int i = 1; i <= n; i++) {
            while (1) {
                if (p >= sz(C)) break;
                auto [val, coeff, power] = C[p];
                if (val >= a[i]) break;
                ll S = S0; if (power == 1) S = S1; if (power == 2) S = S2;
                ans = (ans + S * coeff) % P;
                p++;
            }
            S0 += 1, S1 += a[i] % P, S2 += a[i] % P * (a[i] % P) % P;
            S0 %= P, S1 %= P, S2 %= P;
        }
        while (p < sz(C)) {
            auto [val, coeff, power] = C[p];
            ll S = S0; if (power == 1) S = S1; if (power == 2) S = S2;
            ans = (ans + S * coeff) % P;
            p++;
        }
        cout << ans << endl;
    }
    return 0;
}