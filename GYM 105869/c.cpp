#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int n, m;
ll f[3009][3009], g[3009][3009], d[3009][3009] , ans = 0;
const ll inf = 1e11;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> d[i][j];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                f[i][j] = max(f[i - 1][j], f[i][j - 1]) + d[i][j];
        for (int i = 1; i <= n; i++)
            g[i][m + 1] = 0;
        for (int j = 1; j <= m; j++)
            g[n + 1][j] = 0;
        for (int i = n; i >= 1; i--)
            for (int j = m; j >= 1; j--)
                g[i][j] = max(g[i + 1][j], g[i][j + 1]) + d[i][j];
        ans = 0;
        for (int i = 1; i < n; i++)
            for (int j = 2; j <= m; j++) {
                ll q = -inf;
                // down, left
                // i = 1, j = 2
                q = max(q, g[i + 1][j] - d[i + 1][j]);
                if (i + 2 <= n)
                    q = max(q, g[i + 2][j - 1]);
                ans = max(ans, f[i][j] + d[i + 1][j] + d[i + 1][j - 1] + q);
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < m; j++) {
                ll q = -inf;
                // right, left
                q = max(q, g[i][j + 1] - d[i][j + 1]);
                if (i + 1 <= n)
                    q = max(q, g[i + 1][j]);
                ans = max(ans, f[i][j] + d[i][j + 1] + q);
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                ans = max(ans, f[i][j] + g[i][j] - d[i][j]);
        cout << ans << endl;
    }
    return 0;
}