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
    for (auto q : query) {
        int found = 0;
        for (auto [l, r] : a) {
            if (l <= q && q <= r) {
                found++;
            }
        }
        if (found) ans++;
    }

    cout << "ans = " <<  ans << endl;

}