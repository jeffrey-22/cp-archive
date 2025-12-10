#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n;
int h[1000009];
ll f[1000009];
const ll inf = 3000000000000ll;
ll ans = inf;
vector<int> p = {};
ll sqr(ll x) {return x * x;}
vector<pair<ll, ll>> q;
int ql, qr, debugflag;
ll eval(pair<ll, ll> line, ll x) {
    return line.first * x + line.second;
}
void cleards() {
    q.clear();
    ql = qr = 0;
}
void insertds(ll k, ll b) {
    while (qr - ql >= 2) {
        ll A = (b - q[qr - 1].second) * (q[qr - 2].first - q[qr - 1].first);
        ll B = (q[qr - 1].second - q[qr - 2].second) * (q[qr - 1].first - k);
        if (A > B) break;
        qr--; q.pop_back();
    }
    q.push_back({k, b}); qr++;
    assert(qr == sz(q));
}
ll queryds(ll x) {
    while (qr - ql >= 2 && (eval(q[ql], x) >= eval(q[ql + 1], x))) {
        ql++;
    }
    if (qr - ql >= 1)
        return eval(q[ql], x);
    return inf;
}
void solve(int hl, int hr, vector<int>& p) {
    if (sz(p) <= 1) return;
    if (hl == hr) {
        for (int i = 1; i < sz(p); i++) {
            f[p[i]] = min(f[p[i]], f[p[i - 1]] + sqr(p[i] - p[i - 1] - 1));
        }
        return;
    }
    vector<int> pleft = {};
    vector<int> pright = {};
    int hm = (hl + hr) >> 1;
    for (auto x : p)
        if (h[x] <= hm)
            pleft.push_back(x);
        else
            pright.push_back(x);
    solve(hl, hm, pleft);
    // cout << "solving for " << hl << " " << hm << " " << hr << endl;
    // cout << "with: "; for (auto x : p) cout << x << " "; cout << endl;
    cleards();
    for (auto x : p) {
        if (h[x] <= hm) {
            insertds(-x*2, f[x] + sqr(x));
        } else {
            ll best = queryds(x - 1) + sqr(x - 1);
            f[x] = min(f[x], best);
        }
    }
    // cout << "got f: "; for (auto x : p) cout << f[x] << " "; cout << endl;
    solve(hm + 1, hr, pright);
}
int main() {
    // cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    scanf("%d", &n);
    int hmin = 1000000, hmax = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        hmin = min(hmin, h[i]);
        hmax = max(hmax, h[i]);
    }
    for (int i = 1; i <= n; i++)
        p.push_back(i);
    f[1] = 0;
    for (int i = 2; i <= n; i++)
        f[i] = 1ll * (i - 1) * (i - 1);
    solve(hmin, hmax, p);
    for (int i = 1; i <= n; i++) {
        ans = min(ans, f[i] + 1ll * (n - i) * (n - i));
    }
    cout << ans << endl;
}