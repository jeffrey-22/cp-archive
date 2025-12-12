#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < b; i++)
int n, m;
int h[5009], rk[5009], f[5009];
pair<int, int> hi[5009];
vector<int> e[5009];
int findf(int x) {return x == f[x] ? x : f[x] = findf(f[x]);}
int join(int x, int y) {
    x = findf(x);
    y = findf(y);
    if (x != y) {f[x] = y; return 1;}
    return 0;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        hi[i] = {h[i], i};
    }
    sort(hi + 1, hi + n + 1);
    for (int i = 1; i <= n; i++) rk[hi[i].second] = i;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int ans = INT_MAX;
    for (int x = 1; x <= n; x++) {
        if (h[x] > h[1] || h[x] > h[2]) continue;
        for (int y = 1; y <= n; y++) f[y] = y;
        int currk = rk[x];
        for (int y = currk + 1; y <= n; y++) {
            int newid = hi[y].second;
            for (auto t : e[newid]) {
                if (rk[t] >= currk && rk[t] <= y)
                    join(t, newid);
            }
            int A = findf(1);
            int B = findf(2);
            if (A == B) {
                // cerr << "start from " << x << " new id " << newid << endl;
                ans = min(ans, h[newid] - h[x]);
                break;
            }
        }
    }
    cout << ans << endl;
}