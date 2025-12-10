#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, k, t;
typedef long double ld;
ld a[100009], p[100009], q[100009];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cout << fixed << setprecision(9);
    cin >> n >> k; for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) q[i] = a[i]; sort(q+1,q+n+1); t = (n + 1) / 2;
    // n = 100000, k = 1; for (int i = 1; i <= n; i++) a[i] = rand() ^ (rand() << 15) + 1;
    ld L = 0, R = 1, sp = 0;
    while (R - L > 1e-12) {
        ld M = (L + R) / 2;
        sp = 0;
        for (int i = 1; i <= n; i++)
            p[i] = (a[i] * M) / (q[t] * (1 - M) + a[i] * M), sp += p[i];
        if (sp < k) {
            L = M;
        }
        else
            R = M;
    }
    ld M = (L + R) / 2.0;
    for (int i = 1; i <= n; i++)
        p[i] = (a[i] * M) / (q[t] * (1 - M) + a[i] * M), sp += p[i];
    for (int i = 1; i <= n; i++) {
        cout << p[i] << endl;
    }
}