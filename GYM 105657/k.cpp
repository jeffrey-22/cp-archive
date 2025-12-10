#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, m, k;
int p[100009], q[100009];
int main() {
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> m >> k;
        int ans = n * m;
        for (int i = 1; i <= n * m; i++) {
            cin >> p[i];
            q[p[i]] = i;
        }
        if (k >= m) {
            cout << m << endl;
            continue;
        }
        for (int i = 1; i <= n; i++) {
            vector<int> t = {};
            for (int j = 1; j <= m; j++) {
                t.push_back(q[(i - 1) * m + j]);
            }
            sort(all(t));
            int tt = t[sz(t) - k - 1];
            ans = min(ans, max(m, tt));
        }
        cout << ans << endl;
    }

    return 0;
}