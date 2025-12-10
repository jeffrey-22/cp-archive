#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int N = 55;
const int inf = 1e9 + 7;

int add(int x, int y) {
    return min(x + y, inf);
}
struct Matrix {
    int n, m;
    vector<vector<int>> a;
    Matrix() {}
    Matrix(int _n, int _m) {
        n = _n, m = _m;
        a.assign(n, vector<int>(m, -1));
    }
    friend Matrix operator *(const Matrix &a, const Matrix &b) {
        Matrix res(a.n, b.m);
        assert(a.m == b.n);
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < a.m; j++) {
                if (a.a[i][j] < 0) {
                    continue;
                }
                for (int k = 0; k < b.m; k++) {
                    if (b.a[j][k] < 0) {
                        continue;
                    }
                    res.a[i][k] = max(res.a[i][k], add(a.a[i][j], b.a[j][k]));
                }
            }
        }
        return res;
    }
    int getMax() {
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res = max(res, a[i][j]);
            }
        }
        return res;
    }
}pw[40];
int n, m, S;

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n >> m >> S;
    Matrix zero(n, n), one(n, n);
    for (int i = 0; i < n; i++) {
        zero.a[i][i] = 0;
        one.a[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int u, v, p, r;
        cin >> u >> v >> p >> r;
        u--, v--;
        if (r == 0) {
            zero.a[u][v] = p;
        } else {
            one.a[u][v] = p;
        }
    }
    for (int i = 0; i < 40; i++) {
        zero = zero * zero;
    }
    Matrix ans(1, n);
    for (int i = 0; i < n; i++) {
        ans.a[0][i] = 0;
    }
    ans = ans * zero;
    if (ans.getMax() >= S) {
        cout << "0\n";
        return 0;
    }

    one = one * zero;
    pw[0] = one;
    for (int i = 1; i < 40; i++) {
        pw[i] = pw[i - 1] * pw[i - 1];
    }
    if ((ans * pw[39]).getMax() < S) {
        cout << "-1\n";
        return 0;
    }

    ll res = 0;
    for (int i = 39; i >= 0; i--) {
        Matrix tmp = ans * pw[i];
        if (tmp.getMax() < S) {
            ans = tmp;
            res += 1LL << i;
        }
    }
    cout << res + 1 << "\n";
    
    return 0;
}