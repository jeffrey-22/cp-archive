#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
ll a, b, x, y;
vector<pair<ll, ll>> vx, vy;
vector<pair<ll, ll>> solve(ll a, ll x) {
    if (x == 0 || x == a) return {};
    ll g = __gcd(a, x);
    a /= g, x /= g;
    int ok = 0;
    for (ll t = 0; t <= 33; t++)
        if (1ll << t == a) {
            ok = 1;
            break;
        }
    if (!ok) {
        cout << -1 << endl;
        exit(0);
    }
    ll l = 0, r = a, m;
    vector<pair<ll, ll>> res = {};
    while (l < r) {
        m = (l + r) >> 1;
        res.push_back({l * g, r * g});
        if (a == m)
            return res;
        if (a < m) r = m; else l = m;
    }
    assert(false);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> a >> b;
    cin >> x >> y;
    vx = solve(a, x);
    vy = solve(b, y);
    int k = max(sz(vx), sz(vy));
    int sw = 0;
    if (sz(vx) > sz(vy)) {swap(vx, vy); swap(x, y); swap(a, b); sw = 1;}
    int svx = sz(vx);
    cout << k << endl;
    rep(i, 0, k - sz(vx)) {
        if (svx == 0)
            vx.push_back({x, x});
        else
            vx.push_back();
    }
}