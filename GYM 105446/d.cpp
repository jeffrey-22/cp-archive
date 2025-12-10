#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int q;
double p, r, y, n, e, s, w;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> q;
    cout << fixed << setprecision(8);
    while (q--) {
        cin >> p >> r >> y;
        double A, B, C, D;
        A = 0;
        B = (y + p + r) / 2;
        C = (y - p + r) / 2;
        D = r;
        vector<double> v = {A, B, C, D};
        sort(all(v));
        n = (v[0] + v[3]) / 2;
        e = (y + p + r - n * 2) / 2;
        w = (y - p + r - n * 2) / 2;
        s = n - r;
        // cout << n << " " << e << " " << s << " "<< w << endl;
        printf("%.8lf %.8lf %.8lf %.8lf\n", n, e, s, w);
    }
}