#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int ask(int a, int b, int c) {
    cout << a << " " << b << " " << c << endl;
    cout.flush();
    int r;
    cin >> r;
    return r;
}
int m = 5, k = 0;
int a[5][3], b[5], x[10][3], f[5];
int p[2][3], q[2];
map<tuple<int,int,int>, int> CNT;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    a[0][0] = 1;
    a[1][1] = 1;
    a[2][2] = 1;
    a[3][0] = a[3][1] = a[3][2] = 1;
    a[4][0] = 1, a[4][1] = 2, a[4][2] = 3;
    for (int i = 0; i < m; i++) {
        b[i] = ask(a[i][0], a[i][1], a[i][2]);
    }
    int ans = 0;
    for (int S = 0; S < (1 << m); S++) {
        int cnt = 0;
        for (int i = 0; i < m; i++)
            if (S & (1 << i)) cnt++, f[i] = 1; else f[i] = 0;
        if (cnt != 3) continue;
        int t = 0;
        for (int i = 0; i < 3; i++)
            if (f[i]) {
                t = i;
                break;
            }
        memset(p, 0, sizeof(p)); memset(q, 0, sizeof(q));
        int xx = 0;
        for (int i = t + 1; i < m; i++)
            if (f[i]) {
                for (int j = 0; j < 3; j++) p[xx][j] = a[i][j]; q[xx] = b[i];
                q[xx] -= b[t] * p[xx][t]; p[xx][t] = 0;
                xx++;
            }
        int A = -1, B, C, D = -1, E, F, X, Y;
        for (int j = 0; j < 3; j++) if (j != t) {
            if (A == -1)
                A = p[0][j];
            else
                B = p[0][j];
        }
        C = q[0];
        for (int j = 0; j < 3; j++) if (j != t) {
            if (D == -1)
                D = p[1][j];
            else
                E = p[1][j];
        }
        F = q[1];
        Y = (C * D - A * F) / (B * D - A * E);
        X = (C * E - B * F) / (A * E - B * D);
        x[k][t] = b[t];
        for (int i = 0; i < 3; i++) if (i != t) {
            if (X != -1)
                x[k][i] = X, X = -1;
            else
                x[k][i] = Y;
        }
        // cout << A << " " << B << " " << C << " " << D << " " << E << " " << F << endl;
        // cout << x[k][0] << "   " << x[k][1] << " " << x[k][2] << endl;
        ans = max(ans, ++CNT[{x[k][0], x[k][1], x[k][2]}]);
        k++;
    }
    for (int i = 0; i < k; i++)
        if (CNT[{x[i][0], x[i][1], x[i][2]}] >= ans) {
            cout << x[i][0] << " " << x[i][1] << " " << x[i][2] << endl;
            return 0;
        }
}