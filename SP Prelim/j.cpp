#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int N = 5e4 + 5;
const int M = 20;

int n, m, a[N], f[1 << M], b[N], to[M];

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            x--;
            a[x] |= 1 << i;
        }
    }

    int full = (1 << m) - 1;
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
        f[a[i]]++;
    }
    for (int i = 0; i < m; i++) {
        for (int S = 0; S < (1 << m); S++) {
            if (S >> i & 1) {
                f[S] += f[S ^ (1 << i)];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] >> j & 1) {
                to[j] |= a[i];
            }
        }
    }
    // for (int i = 0; i < m; i++) {
    //     cerr << to[i] << endl;
    // }
    for (int ans = 0; ; ans++) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (f[b[i] ^ full] == 0) {
                cnt++;
            }
        }
        if (cnt) {
            // for (int i = 0; i < n; i++) {
            //     cerr << b[i] << endl;
            // }
            cout << cnt << ' ' << ans << "\n";
            return 0;
        }
        for (int i = 0; i < n; i++) {
            int nxt = b[i];
            for (int j = 0; j < m; j++) {
                if (to[j] & b[i]) {
                    nxt |= 1 << j;
                }
            }
            b[i] = nxt;
        }
    }

    return 0;
}