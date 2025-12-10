#include "template.cpp"

int n;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    vector<string> tokens;
    vector<string> a;
    vector<ll> L, R;
    ll sum = 0;

    while (1) {
        tokens = readTokens();
        if (tokens.empty()) break;
        // a.push_back(tokens[0]);
        ll x = stoll(tokens[0]);
        ll y = stoll(tokens[1]);
        L.push_back(x);
        R.push_back(y);
        sum += y - x;
    }

    n = sz(L);
    cerr << "n = " <<  n << endl;
    cerr << "sum = " << sum << endl;

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll x = L[i], y = R[i];
        // cerr << x << " " << y << endl;
        for (ll val = x; val <= y; val++) {
            string str = to_string(val);
            if (sz(str) % 2 != 0) continue;
            int ok = 1;
            for (int j = 0; j < sz(str) / 2; j++)
                if (str[j] != str[sz(str) / 2 + j]) {
                    ok = 0;
                    break;
                }
            // cerr << str << " " << ok << endl;
            if (ok)
                ans += val;
        }
    }
    

    cout << ans << endl;

}