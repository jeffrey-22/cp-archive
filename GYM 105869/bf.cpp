#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int n, q, c;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int T = 2;
    cout << T << endl;
    while (T--) {
        n = 2e5; q = 2e5; c = 1e9;
        cout << n << " " << q << " " << c << endl;
        for (int i = 1; i < n; i++) {
            cout << i << " " << i + 1 << " " << c << endl;
        }
        for (int i = 1; i <= q; i++) {
            cout << 1 << " " << i % n + 1 << endl;
        }
    }
    return 0;
}