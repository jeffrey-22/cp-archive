#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int a, b, m, ans;
int f[1000009];
const int inf = 1e9;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> a >> b >> m;
        for (int i = 0; i <= m; i++) f[i] = -inf;
        f[0] = 2;
        ans = 2 + m / a;
        for (int i = b; i <= m; i++) {
            f[i] = max(f[i], f[i - b] + b / a + 1);
            int k = (b + a - 1) / a;
            if (i - k * a >= 0)
                f[i] = max(f[i], f[i - k * a] + k + 1);
            ans = max(ans, f[i] + (m - i) / a);
        }
        cout << ans * 160 << endl;
    }
}