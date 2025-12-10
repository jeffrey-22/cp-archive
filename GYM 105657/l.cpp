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
    return c-ll;
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
        vector<pair<int, int>> os = {};
        os.push_back({0, 0});
        for (int x = 1; x < n; x++) {
            auto it = upper_bound(all(os), make_pair(x, INT_MAX)); it--;
            auto [y, oldopt] = *it;
            f[x] = f[oldopt] + cost(oldopt + 1, x);
            while (!os.empty()) {
                tie(y, oldopt) = os.back();
                if (x < y && f[x] + cost(x + 1, y) < f[oldopt] + cost(oldopt + 1, y))
                    os.pop_back();
                else
                    break;
            }
            int L = x + 1;
            int R = n + 1;
            while (L < R) {
                int M = (L + R) >> 1;
                if (M == n + 1) {L = R = M; break;}
                if (f[x] + cost(x + 1, M) < f[oldopt] + cost(oldopt + 1, M))
                    R = M;
                else
                    L = M + 1;
            }
            if (L == n + 1) continue;
            os.push_back({R, x});
        }
        auto [y, oldopt] = os.back();
        f[n] = f[oldopt] + cost(oldopt + 1, n);
        cout << -f[n] << endl;
    }

    return 0;
}