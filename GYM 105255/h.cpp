#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, rmax;
ll b[200009], e[200009];
int from[200009];
void solve(ll k, ll v, ll s, vector<pair<ll, ll>> &sleep) {
    assert(k >= 1 && v >= 1);
    if (v >= k) {
        sleep.push_back({s, s + k});

        return;
    }
    if (v >= (k + 1) / 2) {
        sleep.push_back({s, s + v});
        return;
    }
    ll d = (k - v) / 2;
    assert(d >= 1);
    ll kk = k - d * 2;
    assert(s + k - v <= s + d * 3);
    sleep.push_back({s, s + d});
    solve(v, v, s + k - v, sleep);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    rmax = 0;
    for (int i = 1; i <= n; i++)
        cin >> b[i] >> e[i];
    int p = 0;
    while (1) {
        ll rangesz = b[p + 1] - e[p];
        ll rightmost = e[p] + rangesz * 3;
        while (rmax + 1 <= n && e[rmax + 1] <= rightmost) {
            rmax++;
            from[rmax] = p;
        }
        if (rmax == n) {
            break;
        }
        p++;
        if (p > rmax) {
            cout << "impossible" << endl;
            return 0;
        }
    }
    vector<int> trace = {};
    vector<pair<ll, ll>> sleep = {};
    p = n;
    while (p) {
        p = from[p];
        trace.push_back(p);
    }
    reverse(all(trace));
    // for (int i = 0; i < sz(trace); i++) cout << trace[i] << " "; cout << endl;
    for (int i = 0; i < sz(trace); i++) {
        ll s = e[trace[i]];
        ll es = b[trace[i] + 1];
        if (i == sz(trace) - 1) {
            sleep.push_back({s, es});
            continue;
        }
        ll ee = e[trace[i + 1]];
        ll k = es - s;
        ll v = ee - es;
        assert(v <= k * 3);
        solve(k, v, s, sleep);
    }
    assert(sleep[0].first == 0);
    for (int i = 0; i + 1 < sz(sleep); i++) {
        ll dur = sleep[i].second - sleep[i].first;
        // assert(sleep[i + 1].first <= sleep[i].first + dur * 3);
    }
    cout << sz(sleep) << endl;
    for (auto [u, v] : sleep) {
        cout << u << " " << v << endl;
    }
}