#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int a[7009], p[7009][7009];
int f[7009][7009], s[7009][7009];
const int mod = 998244353;
int ans = 0;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
        // a[i] = i;
    sort(a+1,a+n+1);
    int ans = n;
    for (int i = 1; i <= n; i++) {
        int q = i - 2;
        for (int j = 1; j < i; j++) {
            while (q > 0 && a[q] > a[i] - a[j]) q--;
            f[i][j] = 1 + s[j][min(q, j - 1)];
            if (f[i][j] >= mod) f[i][j] -= mod;
            s[i][j] = (s[i][j - 1] + f[i][j]);
            if (s[i][j] >= mod) s[i][j] -= mod;
            ans = (ans + f[i][j]);
            if (ans >= mod) ans -= mod;
        }
    }
    cout << ans << endl;
    return 0;
}