#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ff first
#define ss second
typedef long long ll;
typedef vector<int> vi;
int n, x, y;
string str, ops;
int lim = 1e6;
ll fac[1000009], infac[1000009], sum[1000009];
ll get(ll x, ll y) {
    if (x > y) return 0;
    if (x <= 1 && y <= 1) {
        return 1;
    }
    ll xx = x / 2, yy = y / 2;
    ll tx = x % 2, ty = y % 2;
    if (tx > ty) return 0;
    return get(xx, yy);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fac[0] = 1; for (int i = 1; i<=lim; i++) fac[i] = fac[i - 1] * i % 2;
    sum[0] = 1;
    for (int i = 1; i <= lim; i++) sum[i] = sum[i - 1] + (1ll << (__builtin_popcount(i)));
    for (int i = 0; i <= lim; i++) infac[i] = 1;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> str >> ops;
        if (ops[0] == 'B') {
            cin >> x >> y;
            x--, y--;
            if (y == 0 || y == x) {
                cout << 1 << endl;
                continue;
            }
            if (str[3] == '1') {
                cout << 1 << endl;
                continue;
            }
            if (str[1] == '0' && str[2] == '1') {
                cout << (x + y + 1) % 2 << endl;
                continue;
            }
            if (str[1] == '1' && str[2] == '0') {
                cout << (y + 1) % 2 << endl;
                continue;
            }
            if (str[0] == '0' && str[1] == '0' && str[2] == '0') {
                cout << 0 << endl;
                continue;
            }
            if (str[0] == '1' && str[1] == '0' && str[2] == '0') {
                if (y == 1 || y == x - 1) cout << 0 << endl;
                else {
                    cout << (x + 1) % 2 << endl;
                }
                continue;
            }
            if (str[0] == '1' && str[1] == '1' && str[2] == '1') {
                cout << x % 2 << endl;
                continue;
            }
            cout << get(y, x) << endl;
        } else {
            cin >> x;
            x--;
            if (x <= 1) {cout << x * 2 + 1 << endl; continue;}
            if (str[3] == '1') {
                cout << 1ll * (x + 1) * (x + 2) / 2ll << endl;
                continue;
            }
            if (str[1] == '0' && str[2] == '1' || str[1] == '1' && str[2] == '0') {
                int xx = (x + 1) / 2;
                int t = 0; if (x % 2 == 0) t = xx + 1;
                ll res = 1ll * xx * xx + 2ll * xx;
                res += t;
                cout << res << endl;
                continue;
            }
            
            if (str[0] == '0' && str[1] == '0' && str[2] == '0') {
                cout << x * 2 + 1 << endl;
                continue;
            }
            if (str[0] == '1' && str[1] == '0' && str[2] == '0') {
                ll F = x * 2 + 1;
                ll S = (x - 2) / 2; S = S * S;
                cout << F + S << endl;
                continue;
            }
            if (str[0] == '1' && str[1] == '1' && str[2] == '1') {
                ll F = x * 2 + 1;
                ll S = (x - 1) / 2; S = S * (S + 1);
                cout << F + S << endl;
                continue;
            }
            cout << sum[x] << endl;
        }
    }
    return 0;
}