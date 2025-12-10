#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ff first
#define ss second
typedef long long ll;
typedef vector<int> vi;
string str, cur;
int n;
int v[29];
ll euclid(ll a, ll b, ll &x, ll &y) {
    if (!b) return x=1,y=0,a;
    ll d=euclid(b, a%b, y, x);
    return y -= a / b * x, d;
}
ll lcm(ll a, ll b) {
    ll g= __gcd(a, b);
    a /= g;
    return a * b;
}
ll crt(ll a, ll m, ll b, ll n) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = euclid(m, n, x, y);
    if((a- b) % g != 0) {
        cout << "NO" << endl;
        exit(0);
    }
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m * n / g : x;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    cur= "";
    rep(i, 0, n) {
        cur += ('A' + i);
    }
    cin >> str;
    for (auto ch : str) {
        int k;
        for (int i = 0; i < sz(cur); i++)
            if (cur[i] == ch) 
                k = i;
        v[sz(cur)] = k;
        for (int i = k; i < sz(cur) - 1; i++)
            cur[i] = cur[i + 1];
        cur.pop_back();
    }
    assert(v[1] == 0);
    ll R = crt(v[2], 2, v[3], 3);
    ll T = lcm(2, 3);
    for (ll i = 4; i <= n; i++) {
        R = crt(R, T, v[i], i);
        T = lcm(T, i);
        if (R >= 1000000000ll) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    cout << R << endl;
    return 0;
}