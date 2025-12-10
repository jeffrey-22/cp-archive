#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, m;
int opt[500009];
ll c, a[500009], b[500009], f[500009], sumb[500009], suma[500009];
ll cost(int l, int r) {
    assert(l <= r && l >= 1 && r <= n);
    ll exp = suma[r] - suma[l - 1];
    int ll = 0, rr = m;
    while (ll < rr) {
        int mid = (ll + rr + 1) >> 1;
        if (exp >= sumb[mid])
            ll = mid;
        else
            rr = mid - 1;
    }
    return ll-c;
}
int main() {
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> m >> c;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) cin >> b[i];
        for (int i = 1; i <= n; i++) suma[i] = suma[i - 1] + a[i];
        for (int i = 1; i <= m; i++) sumb[i] = sumb[i - 1] + b[i];
        f[0] = 0;
        for (int l = 1; l <= n; l++) for (int r = l+1; r < n; r++)
        if (cost(l,r+1)-cost(l,r)>cost(l+1,r+1)-cost(l+1,r)) cout << l << " " << r << endl;
        for (int i = 1; i <= n; i++) {
            f[i] = LLONG_MAX;
            for (int j = 0; j < i; j++) {
                ll t = f[j] + cost(j + 1, i);
                if (t <= f[i]) {
                    f[i] = t;
                    opt[i] = j;
                }
            }
            // cout << i << ":" << endl;
            // cout <<"opt=" << opt[i] << " f=" << f[i] << endl;
            // assert(opt[i] >= opt[i - 1]);
        }
        cout << -f[n] << endl;
    }

    return 0;
}