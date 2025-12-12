#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < b; i++)
int n, m, s, k;
vector<tuple<int, int>> mach[39];
bool cmp(const tuple<int, int> &L, const tuple<int, int> &R) {
    // L < R
    auto [LA, LB] = L;
    auto [RA, RB] = R;
    return 1ll * LB * RA < 1ll * LA * RB;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> m;
    cin >> s >> k;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        mach[a].push_back({b, c});
    }
    for (int i = 1; i < n; i++) {
        sort(all(mach[i]), cmp);
        vector<pair<int, int>> op = {{0, 0}};
        int cntop = 0;
        for (int j = 0; j < sz(mach[i]); j++) {
            auto [x, y] = mach[i][j];
            op.push_back({x, y});
            cntop++;
        }
        vector<int> f(k + 3, 0);
        for (int t = 1; t <= cntop; t++) {
            auto [A, B] = op[t];
            for (int x = s; x >= 0; x--) {
                int xx = x + A;
                if (xx > s) continue;
                if (k - x < B) continue;
                f[x] = max(f[x], min(f[xx] + B, k - x));
            }
        }
        s = f[0];
    }
    cout << s << endl;
}