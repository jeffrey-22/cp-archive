#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < b; i++)
const double pi = acos(-1);
ll M, T;
double calc(ll n, ll C) {
    double t = 1.0 * C / n / 2 / sin(pi / n);
    return sin(pi * 2 / n) * (1.0 * n / 2) * t * t;
}
template<class F>
ll ternSearch(ll a, ll b, F f) {
    assert(a <= b);
    while (b - a >= 5) {
        ll mid = (a + b) / 2;
        if (f(mid) < f(mid + 1)) a = mid;
        else b=  mid + 1;
    }
    rep(i, a + 1, b + 1) if (f(a) < f(i)) a = i;
    return a;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    cout << fixed << setprecision(13);
    cerr << fixed << setprecision(13);
    while (Tt--) {
        cin >> M >> T;
        int nmax = T / M;
        if (nmax <= 2) {
            cout << 0 << endl;
            continue;
        }
        int ind = ternSearch(3, nmax, [&](int i){return calc(i, T - 1ll * M * i);});
        double ans = calc(ind, T - M * ind);
        cout << ans << endl;
    }
}