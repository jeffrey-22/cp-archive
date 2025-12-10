#include "template.cpp"

int n;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    vector<string> tokens;
    vector<vector<string>> allTokens;
    while (1) {
        tokens = readTokens();
        if (tokens.empty()) break;
        n++;
        allTokens.push_back(tokens);
    }
    cerr << "n = " << n << endl;

    int m = 0;
    vector<ll> query = {};
    vector<pair<ll, ll>> a;
    for (int i = 0; i < n; i++) {
        if (sz(allTokens[i]) > 1) {
            m++;
            a.push_back({stoll(allTokens[i][0]), stoll(allTokens[i][1])});
        } else {
            ll val = stoll(allTokens[i][0]);
            query.push_back(val);
        }
    }
    cerr << "m = " << m << endl;
    
    ll ans = 0;
    vector<pair<ll, int>> q;
    for (int i = 0; i < m; i++) {
        auto [l, r] = a[i];
        q.push_back({l, 1});
        q.push_back({r + 1, -1});
    }
    sort(all(q));
    ll curcnt = 0, lastcnt = 0;
    for (int i = 0; i < sz(q); i++) {
        auto [v, op] = q[i];
        curcnt += op;
        if (lastcnt > 0 && i > 0 && q[i].first > q[i - 1].first) {
            ans += q[i].first - q[i - 1].first;
            cerr << q[i - 1].first << " - " << q[i].first - 1 << endl;
        }
        if (i < sz(q) - 1 && q[i + 1].first == v) continue;
        lastcnt = curcnt;
    }

    cout << "ans = " <<  ans << endl;

}