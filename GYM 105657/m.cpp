#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, k, fail;
int b[50009];
vector<pii> q;
set<int> x;
void add(int v) {
    if (v >= 1 && v <= k) {
        assert(!x.count(v));
        x.insert(v);
    }
}
void solve(int l, int r) {
    if (l >= r) return;
    int val = INT_MAX;
    rep(i, l, r + 1)
        if (b[i] < val)
            val = b[i];
    rep(i, l, r + 1)
        if (b[i] > val && b[i] <= val * 2) {
            fail = 1;
            return;
        }
        else if (b[i] > val) {
            q.push_back({val, b[i]});
        }
    vector<int> pos = {};
    rep(i, l, r + 1)
        if (b[i] == val)
            pos.push_back(i);
    solve(l, pos[0] - 1); if (fail) return;
    solve(pos.back() + 1, r); if (fail) return;
    for (int i = 0; i + 1 < sz(pos); i++) {
        solve(pos[i] + 1, pos[i + 1] - 1);
        if (fail) return;
    }
}
map<pii, int> vis;
int main() {
    int Tt; cin >> Tt;
    while (Tt--) {
        cin >> n >> k;
        assert(n <= 50000);
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        // n = rand() % 4 + 1; k = 2e4; for (int i = 1; i <= n; i++) b[i] = (rand() ^ (rand() << 14)) % (10000) + 1;
        q.clear(); x.clear(); vis.clear();
        fail = 0;
        solve(1, n);
        if (fail)
            cout << "0 0" << endl;
        else if ( sz(q) == 0) {
            cout << k << " " << 1ll * k * (k + 1) / 2 << endl;
        } else {
            auto [u, v] = q.back(); // q.pop_back();
            int delta = v - u;
            for (int d = 1; d * d <= delta; d++) {
                if (delta % d == 0) {
                    add(d - u);
                    if (d * d < delta)
                        add(delta / d - u);
                }
            }
            for (auto val : x) assert(val >= 1 && val <= k);
            // cout << "DONE " << endl;
            for (auto [u, v] : q) {
                auto it = x.begin();
                while (it != x.end()) {
                    int val = *it;
                    if ((v + val) % (u + val) != 0)
                        x.erase(val);
                    it = x.upper_bound(val);
                }
            }
            // for (auto val : x) for (auto [u, v] : q) assert((v + val) % (u + val) == 0);
            // for (int t=1;t<=min(k, 100000);t++)if (!x.count(t)){int ok = 1;for (auto [u, v] : q) if((v + t) % (u + t) != 0){ok=0;break;}assert(!ok);}
            // cout << "DONE 2 " << endl;
            ll sum = 0;
            for (auto val : x) sum += val;
            cout << sz(x) << " " << sum << endl;
        }
    }

    return 0;
}

// b2+x = t(b1+x), t >= 1
// b2 + x = tb1 + tx
// x = (b2 - tb1) / (t - 1), b2 >= 2b1
// A B C 2 6 3