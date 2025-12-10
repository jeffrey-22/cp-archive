#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int N = 1e3 + 5;
const int M = 15;
const int S = 28;

int n, m, D, De, Dk, s;
long double g[M][S][M][M][M], h[M][M][M][M], f[N][N], fac[M], pw[M + M];

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cout.precision(16), cout.setf(ios :: fixed);

    cin >> n >> m >> De >> Dk >> s;
    D = min(De, Dk);

    for (int i = fac[0] = 1; i < M; i++) {
        fac[i] = fac[i - 1] * i;
    }
    for (int i = pw[0] = 1; i < M + M; i++) {
        pw[i] = pw[i - 1] * s;
    }
    for (int mn = 1; mn <= D; mn++) {
        g[mn][0][0][0][0] = 1;
        for (int p = 1; p <= s; p++) {
            for (int i = 0; i <= De; i++) {
                for (int j = 0; j <= Dk; j++) {
                    int d = min({i, j, mn});
                    for (int u = 0; u <= d; u++) {
                        for (int x = 0; x <= i; x++) {
                            for (int y = 0; y <= j; y++) {
                                int tmp = min({i - x, j, mn});
                                int A = max(tmp - (j - y), 0);
                                g[mn][p][i][j][u] += g[mn][p - 1][i - x][j - y][u - A] / fac[x] / fac[y];
                                // if (mn == 1 && i == 1 && j == 1 && u == 0)
                                // cerr << x << ',' << y << "|" << A << ":" << g[mn][p - 1][i - x][j - y][u - A] / fac[x] / fac[y] << endl;
                            }
                        }

                        // if (mn == 1 && i <= 1 && j <= 1)
                        // cerr << mn << ":" << p << ' ' << i << ' ' << j << '|' << u << ":" << g[mn][p][i][j][u] << endl;

                        if (p == s && i >= mn && j >= mn && min(i, j) == mn) {
                            int v = d - u;
                            h[i][j][u][v] += g[mn][p][i][j][u] * fac[i] * fac[j] / pw[i + j];
                            // if (i == 1 && j == 1 && u == 0 && v == 1) {
                            //     cerr << mn << ":" << g[mn][p][i][j][u] * fac[i] * fac[j] << endl;
                            // }
                        }
                    }
                }
            }
        }
    }
    // cerr << h[1][1][0][1] << endl;
    f[n][m] = 1;
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            int mn = min({i, j, De, Dk});
            for (int x = 0; x <= i && x <= De && x <= mn; x++) {
                for (int y = 0; y <= j && y <= Dk && y <= mn; y++) {
                    f[i - y][j - x] += f[i][j] * h[min(i, De)][min(j, Dk)][x][y];
                }
            }
        }
    }
    long double ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += f[i][0];
    }
    cout << ans << "\n";

    return 0;
}