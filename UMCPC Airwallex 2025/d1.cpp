#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size() 
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> pii; 
typedef vector<int> vi;
int n, m, k;
double x;
double F[100009][13];
vector<tuple<int, double, double>> e[100009];
int tot = 0;
map<string, int> namemp;
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> m;
    cin >> x >> k;
    for (int i = 1; i <= m; i++) {
        string S1, S2;
        double r, f;
        cin >> S1 >> S2 >> r >> f;
        // S1 = "AUD", S2 = "AUD", r = 1e6, f = 1e6;
        if (!namemp[S1]) {
            namemp[S1] = ++tot;
        }
        if (!namemp[S2]) {
            namemp[S2] = ++tot;
        }
        int u, v;
        u = namemp[S1];
        v = namemp[S2];
        e[u].pb({v, r, f});
        // e[v].pb({u, r, f});
    }
    // assert(tot == n);
    int rt = namemp["AUD"];
    F[rt][0] = x;
    for (int i = 1; i <= k + 1; i++) {
        for (int u = 1; u <= n; u++) {
            for (auto [v, r, f] : e[u]) {
                F[v][i] = max(F[v][i], (F[u][i - 1] * r - f));
            }
        }
    }
    double ans = 0;
    for (int i = 0; i <= k + 1; i++) {
        ans = max(ans, F[rt][i]);
        // cout << "at " << i << ": " << F[rt][i] << endl;
    }
    cout << ans << endl;
    return 0;
}