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

    int m = 0, sx, sy;
    vector<vector<ll>> a = {};
    for (int i = 0; i < n; i++) {
        m = sz(allTokens[i]);
        vector<ll> line(m, 0);
        for (int j = 0; j < m; j++) {
            line[j] = stoll(allTokens[i][j]);
        }
        a.push_back(line);
    }
    cerr << "m = " << m << endl;

    ll ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            ll yl = min(a[i][1], a[j][1]);
            ll yr = max(a[i][1], a[j][1]);
            ll xl = min(a[i][0], a[j][0]);
            ll xr = max(a[i][0], a[j][0]);
            int ok = 1;
            for (int k = 0; k < n; k++) {
                int previdx = k - 1; if (previdx < 0) previdx = n - 1;
                ll prev = a[previdx][1], succ = a[k][1];
                if (a[k][0] > xl && a[k][0] < xr && (prev >= yr && succ < yr || prev <= yl && succ > yl))
                    ok = 0;
                prev = a[previdx][0], succ = a[k][0];
                if (a[k][1] > yl && a[k][1] < yr && (prev >= xr && succ < xr || prev <= xl && succ > xl))
                    ok = 0;
            }
            if (!ok) continue;
            // cerr << xl << " " << xr << " " << yl << " " << yr << " " << 1ll * (yr - yl + 1) * (xr - xl + 1) <<  endl;
            ans = max(ans, 1ll * (yr - yl + 1) * (xr - xl + 1));
        }
    cout << "answer = " << ans << endl;
}