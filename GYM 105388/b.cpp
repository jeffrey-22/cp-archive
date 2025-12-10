#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
ll a, AA, P, Q, R;
ll SQRT(ll v) {
    ll L = 0, R = 1000000001ll;
    while (L < R) {
        ll M = (L + R + 1) >> 1ll;
        if (M * M <= v)
            L = M;
        else
            R = M - 1;
    }
    return L;
}
int chk(ll x, ll y) {
    // cout << x << " " << y << endl;
    ll PP, QQ, RR;
    PP = y * y + (a - x) * (a - x);
    QQ = x * x + (a - y) * (a - y);
    RR = (x - y) * (x - y) + (x + y - a) * (x + y - a);
    return P == PP && Q == QQ && R == RR;
}
void put(ll x, ll y) {
    cout << a << " " << -x << " " << a-y << " " << y-x << " " << a-x-y << " " << y << " " << a-x << endl;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> AA >> Q >> R >> P;
    a = SQRT(AA);
    ll D = Q - P;
    D /= 2;
    D /= a;
    ll S = SQRT(R - D * D);
    ll S1 = S + a;
    ll S2 = -S + a;
    ll X1 = (S1 + D) / 2;
    ll Y1 = (S1 - D) / 2;
    ll X2 = (S2 + D) / 2;
    ll Y2 = (S2 - D) / 2;
    if (chk(X1, Y1)) {
        put(X1, Y1);
    } else if (chk(X2, Y2)) {
        put(X2, Y2);

    } else {
        assert(false);
    }
}