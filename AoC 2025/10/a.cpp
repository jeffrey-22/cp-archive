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
    ll ans = 0;
    // vector<vector<ll>> a = {};
    for (int i = 0; i < n; i++) {
        vector<string> tokens = allTokens[i];

        // m = sz(tokens);
        
        string initConfig = tokens[0];
        initConfig.pop_back(); reverse(all(initConfig)); initConfig.pop_back(); reverse(all(initConfig));
        m = sz(initConfig);
        vector<int> a(m, 0);
        for (int j = 0; j < m; j++) if (initConfig[j] == '#') a[j] = 1; else a[j] = 0;
        vector<vector<int>> b = {};
        for (int j = 1; j < sz(tokens) - 1; j++) {
            string seq = tokens[j];
            vector<int> c = {};
            int val = 0;
            for (int k = 0; k < sz(seq); k++)
                if (seq[k] >= '0' && seq[k] <= '9') val = val * 10 + seq[k] - '0';
                else if (seq[k] == ',' || seq[k] == ')') {
                    c.push_back(val);
                    val = 0;
                }
            b.push_back(c);
        }
        vector<int> aa = a;
        ll minuse = INT_MAX;
        for (int S = 0; S < (1 << sz(b)); S++) {
            aa = a;
            ll cntuse = 0;
            for (int j = 0; j < sz(b); j++)
                if (S & (1 << j)) {
                    for (auto t : b[j]) aa[t] ^= 1;
                    cntuse++;
                }
            int ok = 1;
            // cerr << S << ": "; for (int j = 0; j < m; j++)  cerr << aa[j] << " "; cerr << endl;
            for (int j = 0; j < m; j++) if (aa[j]) {ok = 0; break;}
            if (ok) {
                minuse = min(minuse, cntuse);
                // cerr << cntuse << " " << S << endl;
            }
        }
        cerr << minuse << endl;
        ans += minuse;
    }
    
    cout << "answer = " << ans << endl;
}