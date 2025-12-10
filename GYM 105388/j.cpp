#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define endl '\n'
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
ll m = 62;
int n;
ll a[100009], oa[100009];
vector<pair<int, ll>> ops;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i], oa[i] = a[i];
        // if (n > 128) {
        //     printf("-1\n");
        //     continue;
        // }
        ops.clear();
        int isvalid = 1;

        for (ll b = m; b >= 0; b--) {
            vector<int> x; x.clear();
            for (int i = 1; i <= n; i++)
                if (a[i] & (1ll << b)) {
                    x.push_back(i);
                }
            if (sz(x) == 0) continue;
            if (sz(x) != 2) {
                isvalid = 0;
                break;
            }
            int i1 = x[0], i2 = x[1], ii;
            ll taken = 0;
            if (a[i1] > a[i2]) ii = i1, taken = a[i1]; else ii = i2, taken = a[i2];
            a[i1] ^= taken, a[i2] ^= taken;
            ops.push_back({ii, taken});
        }

        if (!isvalid) {
            printf("-1\n");
            continue;
        }
        printf("%d\n", sz(ops));
        for (auto [ID, val] : ops) {
            printf("%d %lld\n", ID, val);
        }

        assert(sz(ops) <= 100);
        for (int i = 1; i <= n; i++) a[i] = oa[i];
        for (auto [ID, val] : ops) {
            assert(val <= a[ID]);
            a[ID] -= val;
            int cnt = 0;
            for (int i = 1; i <= n; i++)
                if ((a[i] ^ val) <= a[i]) {
                    cnt++;
                    a[i] ^= val;
                }
            assert(cnt == 1);
        }
        for (int i = 1; i <= n; i++) assert(a[i] == 0);
    }
}