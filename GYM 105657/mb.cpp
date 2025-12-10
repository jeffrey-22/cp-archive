#include <bits/stdc++.h>
#define int long long
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, k;
int b[50009];
vector<pii> q;
set<int> x;
void add(int v) {
    if (v >= 1 && v <= k)
        x.insert(v);
}
map<pii, int> vis;
signed main() {
    int Tt; cin >> Tt;
    while (Tt--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        ll a = 0, s = 0;
        for (int i = 1; i <= k; i++) {
            int ok = 1;
            for (int j = 1; j + 1 <= n; j++) {
                ll maxv = max(b[j], b[j + 1]);
                ll minv = min(b[j], b[j + 1]);
                maxv += i, minv += i;
                if (maxv % minv > 0) {ok = 0; break;}
            }
            if (ok) a++, s+=i;
        }
        cout << a << " " << s << endl;
    }

    return 0;
}

// b2+x = t(b1+x), t >= 1
// b2 + x = tb1 + tx
// x = (b2 - tb1) / (t - 1), b2 >= 2b1