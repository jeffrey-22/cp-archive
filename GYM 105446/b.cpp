#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, m;
double qx[1000009], qy[1000009], xy[1000009], sx[1000009], sy[1000009];
double K, B;
int main() {
    // cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        qx[i] = qx[i - 1] + x * x;
        qy[i] = qy[i - 1] + y * y;
        xy[i] = xy[i - 1] + x * y;
        sx[i] = sx[i - 1] + x;
        sy[i] = sy[i - 1] + y;
    }
    scanf("%d", &m);
    while (m--) {
        int l, r;
        double L, X;
        scanf("%d%d%lf%lf", &l, &r, &L, &X);
        double QX, QY, XY, SX, SY;
        SX = sx[r] - sx[l - 1];
        SY = sy[r] - sy[l - 1];
        XY = xy[r] - xy[l - 1];
        QX = qx[r] - qx[l - 1];
        QY = qy[r] - qy[l - 1];
        if (L + QX < 1e-9) {
            K = 0;
            B = SY / (L + 1);
        } else {
            double t = r - l + 1;
            K = -(-XY * 2 + SX * SY * 2 / (L + t)) / (-SX*SX/(L+t) + L + QX) / 2;
            B = (-SX * K + SY) / (L + t);
        }
        // cout << K << " " << B << endl;
        double ans = K * X + B;
        printf("%.7lf\n", ans);
    }
}