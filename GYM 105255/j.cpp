#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
ll m = 63;
int n;
ll a[100009];
vector<int> c[109];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        if (n > 300) {
            cout << -1 << endl;
            continue;
        }
        for (ll j = 0; j <= m; j++) c[j].clear();
        for (int i = 1; i <= n; i++) {
            for (ll j = 0; j <= m; j++)
                if (a[i] & (1ll << j))
                    c[j].push_back(i);
        }
        int k = 0;
        int invalid = 0;
        for (ll j = 0; j <= m; j++) {
            if (sz(c[j]) == 2)
                k++;
            else if (sz(c[j]) != 0)
                invalid = 1;
        }
        if (invalid) {
            cout << -1 << endl;
            continue;
        }
        cout << k << endl;
        for (ii i = 0; i <= m; i++)
            if (sz(c[i]) == 2) {
                cout << c[i][0] << " " << (1ll << i) << endl;
            }
    }
}