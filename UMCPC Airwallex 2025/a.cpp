#include <bits/stdc++.h>

#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
#pragma GCC optimize ("trapv")

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
int n;
int a[100009][5], needed[5];
ll p[100009][5];
ll f[100009][19];
const ll inf = LLONG_MAX / 2;
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 4; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 4; j++)
            cin >> p[i][j];
    f[0][0] = 0;
    for (int i = 1; i <= 15; i++)
        f[0][i] = inf;
    for (int i = 1; i <= n; i++) {
        for (int S = 0; S < 15; S++) {
            f[i][S] = inf;
            for (int T = 0; T < 15; T++) {
                for (int j = 1; j <= 4; j++)
                    needed[j] = a[i][j];
                int ok = 1;
                for (int type = 1; type <= 4; type++) {
                    int needone = S & (1 << (type - 1));
                    int useone = T & (1 << (type - 1));
                    if (needone)
                        needed[type] += 1;
                    if (useone) {
                        needed[type] -= 1;
                        if (needed[type] < 0) {
                            ok = 0;
                            break;
                        }
                    }
                }
                if (!ok) continue;
                ll total = 0;
                for (int j = 1; j <= 4; j++)
                    total += 1ll * p[i][j] * needed[j];
                f[i][S] = min(f[i][S], f[i - 1][T] + total);
            }
            // cout << i << " " << S << " " << f[i][S] << endl;
        }
    }
    cout << f[n][0] << endl;
    return 0;
}