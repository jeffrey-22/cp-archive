#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
double D[1009], f[1009], C[1009][1009], fac[1009];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n;
    D[1] = 0, D[2] = 1;
    for (int i = 0; i <= n; i++)
        C[i][0] = C[i][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    for (int i = 3; i <= n; i++)
        D[i] = 1.0 * (i - 1) * (D[i - 1] + D[i - 2]);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
    f[0] = 0; f[1] = 0;
    for (int i = 2; i <= n; i++) {
        double B = 1.0 - D[i]/fac[i];
        double sum = 1.0;
        for (int k = 0; k < i; k++)
            sum += f[k] * C[i][k] * D[k] / fac[i];
        f[i] = sum / B;

        // cout << i << "-" << f[i] << endl;
    }
    cout << (n==1?0:n) << endl;
    for (int i = 2; i <= n; i++) cout << i << " "; cout << 1 << endl;
    return 0;
}