#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G &g, F &f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for (auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ? : dfs(e, g, f));
    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G &g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if (comp[i] < 0) dfs(i, g, f);
}
int n, k, q;
vector<vi> G = {}, a = {}, fl = {}, fr = {}, b = {}, c = {};
vector<vector<ll>> gsum;
ll ans = 0;
int main() {
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> k >> q;
        G = vector<vi>(n + 2, vi());
        fl = vector<vi>(k + 1, vi(n + 2, 0));
        fr = vector<vi>(k + 1, vi(n + 2, 0));
        a = vector<vi>(k + 1, vi(n + 2, 0));
        b = vector<vi>(k + 1, vi(n + 2, 0));
        c = vector<vi>(k + 1, vi(n + 2, 0));
        for (int i = 1; i <= n; i++) G[i].clear();
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                int id;
                cin >> id;
                a[i][j] = id;
            }
            for (int j = 1; j < n; j++)
                G[a[i][j]].push_back(a[i][j + 1]);
        }
        scc(G, [&](vi &v){});
        gsum = vector<vector<ll>>(k + 1, vector<ll>(n + 2, 0));

        for (int i = 1; i <= k; i++) {
            
            for (int j = 1; j <= n; j++) {
                b[i][j] = comp[a[i][j]];
                c[i][j] = b[i][j];
            }
            int T = 0;
            for (int j = 1; j <= n; j++) {
                if (j == 1 || b[i][j] != b[i][j - 1])
                    c[i][j] = ++T, fl[i][j] = j;
                else
                    c[i][j] = T, fl[i][j] = fl[i][j - 1];
                gsum[i][T]++;
            }
            for (int j = n; j >= 1; j--) {
                if (j == n || b[i][j] != b[i][j + 1])
                    fr[i][j] = j;
                else
                    fr[i][j] = fr[i][j + 1];
            }
            for (int j = 1; j <= T; j++)
                gsum[i][j] = gsum[i][j - 1] + gsum[i][j] * (gsum[i][j] - 1) / 2;
        }
        ans = 0;
        while (q--) {
            int id, L, R;
            cin >> id >> L >> R;
            id = (ans + id) % k + 1;
            L = (ans + L) % n + 1;
            R = (ans + R) % n + 1;
            assert(L <= R);
            if (c[id][L] == c[id][R])
                ans = 1ll * (R - L + 1) * (R - L) / 2;
            else {
                ans = 0;
                int v;
                v = fr[id][L] - L + 1;
                // cout << "Case 2" << endl;
                // cout << b[id][L] << " " << b[id][R] << endl;
                // cout << v << " ";
                ans += 1ll * (v) * (v - 1) / 2;
                v = R - fl[id][R] + 1;
                // cout << v << " ";
                ans += 1ll * (v) * (v - 1) / 2;
                ans += gsum[id][c[id][R] - 1] - gsum[id][c[id][L]];
                // cout << gsum[id][b[id][R] - 1] - gsum[id][b[id][L]] << endl;
            }
            cout << ans << endl;
        }
    }

    return 0;
}