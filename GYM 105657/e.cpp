#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, f, p;
int g[100009];
tuple<int, int, int> a[100009];
ll cost1, ans;
vi order;
int main() {
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> f;
        ans = 0;
        for (int i = 1; i <= n; i++) {
            int L, R;
            cin >> L >> R;
            a[i] = {L, R, i};
            g[i] = 0;
            ans += R - L;
        }
        sort(a + 1, a + n + 1);
        p = 1;
        cost1 = 0;
        order.clear();
        while (1) {
            auto [L, R, id] = a[p];
            while (p <= n && L <= f) {
                if (R > f) {
                    f = R;
                    order.push_back(id);
                    g[id] = 1;
                }
                p++;
                tie(L, R, id) = a[p];
            }
            if (p > n) break;
            tie(L, R, id) = a[p];
            cost1 += L - f; f = R; 
            order.push_back(id); g[id] = 1;
            p++;
        }
        // cout << cost1 << "  ws z= " << sz(order) << endl;
        for (int i = n; i >= 1; i--) {
            auto [L, R, id] = a[i];
            if (!g[id]) {
                order.push_back(id);
                g[id] = 1;
            }
        }
        cout << ans + cost1 << endl;
        for (auto o : order) cout << o << " "; cout << endl;
    }

    return 0;
}