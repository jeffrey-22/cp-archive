#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ff first
#define ss second
typedef long long ll;
typedef vector<int> vi;
int p, t, sum, ans = 0;
int f[29], a[29], b[29];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> p >> t;
    int LIM = (1 << p) - 1;
    for (int i = 0; i < t; i++) {
        string str; cin >> str;
        for (auto ch : str) {
            if ((ch - 'A' + 1) > p || a[i] & ( 1 << (ch - 'A'))) b[i] = 1;
            a[i] |= 1 << (ch - 'A');
        }
        // a[i] = LIM - a[i];
        // cout << b[i] << endl;
    }
    for (int s = 0; s < (1 << t); s++) {
        sum = 0;
        for (int i = 0; i < t; i++) {
            f[i] = s & (1 << i);
            if (f[i]) f[i] = 1,sum++;
            if (b[i] && f[i]) sum = -100000;
        }
        if (sum < ans) continue;
        int R = 0, ok = 1;
        for (int i = 0; i < t; i++)
            if (f[i]) {
                if (R & a[i]) {ok = 0; break;}
                R |= a[i];
            }
        if (ok) {
            // if (sum == 4) for (int i = 0; i < t; i++) cout << f[i]; cout << " " << R << endl;
            ans = sum;
        }
    }
    cout << ans << endl;
    return 0;
}