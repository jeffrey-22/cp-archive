#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const ll lim = 1ll<<23;
ll n;
ll a[19];
ll isp[lim + 9];
int flag[lim + 9];
vector<ll> primes = {};
vector<ll> vals;
vector<ll> ps;
int main() {
    for (int i = 0; i <= lim; i++) isp[i] = 1;
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    for (int i = 2; i <= lim; i++) {
        if (!isp[i]) continue;
        primes.push_back(i);
        for (int j = 2; i * j <= lim; j++)
            isp[i * j] = 0;
    }

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int s = 0; s < (1 << n); s++) {
        ll t1 = 1, t2 = 1;
        for (int i = 1; i <= n; i++)
            if (s & (1 << (i - 1))) {
                t1 *= a[i];
            } else 
                t2 *= a[i];
        vals.push_back(t1 + t2);
    }
    for (auto v : vals) {
        for (int i = 0; i < sz(primes); i++) {
            ll q = primes[i];
            if (v % q == 0) {
                while ((v % q == 0)) v /= q;
                flag[i] = 1;
            }
        }
        if (v > 1)
            ps.push_back(v);
    }
    sort(all(ps));
    vector<ll> A = {};
    for (int i = 0; i < sz(primes); i++) 
        if (flag[i])
            A.push_back(primes[i]);
    for (int i = 0; i < sz(ps); i++)
        if (i == 0 || ps[i] > ps[i - 1])
            A.push_back(ps[i]);
    cout << sz(A) << " ";
    for (auto t : A) cout << t << " ";
    cout << endl;
}