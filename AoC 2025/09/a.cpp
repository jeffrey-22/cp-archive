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
        for (int j = i + 1; j < n; j++)
            ans = max(ans, (a[i][0] - a[j][0] + 1) * (a[i][1] - a[j][1] + 1));
    cout << "answer = " << ans << endl;
}