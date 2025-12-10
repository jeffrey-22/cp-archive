#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, m, r, c;
const int q = 2;
const ll B[q] = {59, 89}, P[q] = {998244353, 1000000000+7};
ll OS[q], POW[4000009][q];
ll a[2009][2009][2], s[2009][2009][2], mch[2009][2009], smch[2009][2009];
char oc[2009][2009];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    const int LIM = 4000001;
    for (int t = 0; t < q; t++) {
        POW[0][t] = 1;
        for (int i = 1; i <= LIM; i++)
            POW[i][t] = POW[i - 1][t] * B[t] % P[t];
    }
    cin >> r >> c;
    ll buf[q] = {1, 1};
    for (int i = 0; i < r; i++) {
        string str; cin >> str;
        for (int j = 0; j < c; j++) {
            for (int t = 0; t < q; t++) {
                OS[t] = (OS[t] + buf[t] * (str[j] - 'a' + 1)) % P[t];
                buf[t] = buf[t] * B[t] % P[t];
            }
        }
    }
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string str; cin >> str;
        for (int t = 0; t < q; t++)
            buf[t] = POW[c * i][t];
        for (int j = 0; j < m; j++) {
            oc[i][j] = str[j];
            for (int t = 0; t < q; t++) {
                a[i][j][t] = (buf[t] * (str[j] - 'a' + 1)) % P[t];
                buf[t] = buf[t] * B[t] % P[t];
            }
        }
    }
    for (int t = 0; t < q; t++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                ll up = i == 0 ? 0 : s[i - 1][j][t];
                ll left = j == 0 ? 0 : s[i][j - 1][t];
                ll corner = (i == 0 || j == 0) ? 0 : s[i - 1][j - 1][t];
                s[i][j][t] = (a[i][j][t] + up + left - corner + P[t]) % P[t];
            }
    }
    for (int i = 0; i + r - 1 < n; i++)
        for (int j = 0; j + c - 1 < m; j++) {
            int ok = 1;
            for (int t = 0; t < q; t++) {
                ll extra = POW[c * i + j][t];
                
                ll up = i == 0 ? 0 : s[i - 1][j + c - 1][t];
                ll left = j == 0 ? 0 : s[i + r - 1][j - 1][t];
                ll corner = (i == 0 || j == 0) ? 0 : s[i - 1][j - 1][t];
                ll current = s[i + r - 1][j + c - 1][t];
                ll tot = current - up - left + corner;
                tot = (tot % P[t] + P[t]) % P[t];
                // cout << i << " " << j << " " << t << endl;
                // cout << "og sum = " << OS[t] << endl;
                // cout << "extra = " << extra << endl;
                // cout << "cur sum = " << tot << endl;
                if (tot != extra * OS[t] % P[t]) {
                    ok = 0;
                    break;
                }
            }
            mch[i][j] = ok;
            
        }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int up = i == 0 ? 0 : smch[i - 1][j];
            int left = j == 0 ? 0 : smch[i][j - 1];
            int corner = (i == 0 || j == 0) ? 0 : smch[i - 1][j - 1];
            smch[i][j] = (mch[i][j] + up + left - corner);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = max(i - r + 1, 0);
            int y = max(j - c + 1, 0);
            int up = x == 0 ? 0 : smch[x - 1][j];
            int left = y == 0 ? 0 : smch[i][y - 1];
            int corner = (x == 0 || y == 0) ? 0 : smch[x - 1][y - 1];
            int totmatch = smch[i][j] - up - left + corner;
            if (totmatch > 0)
                cout << oc[i][j];
            else
                cout << '.';
        }
        cout << endl;
    }
}