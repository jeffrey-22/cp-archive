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
        m = sz(allTokens[i][0]);
        vector<ll> line(m, 0);
        for (int j = 0; j < m; j++) {
            if (allTokens[i][0][j] == 'S') {sx = i, sy = j;} else if (allTokens[i][0][j] == '^') line[j] = -1;
        }
        a.push_back(line);
    }
    cerr << "m = " << m << endl;

    ll ans = 0;
    a[sx][sy] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == -1 && a[i - 1][j] >= 1) {
                int jj = j - 1;
                if (jj >= 0 && jj < m) {
                    assert(a[i][jj] != -1);
                    a[i][jj] += a[i - 1][j];
                    // a[i][jj] = 1;
                }
                jj = j + 1;
                if (jj >= 0 && jj < m) {
                    assert(a[i][jj] != -1);
                    a[i][jj] += a[i - 1][j];
                    // a[i][jj] = 1;
                }
                // ans++;
            } else if (a[i][j] >= 0 && a[i - 1][j] >= 1) {
                a[i][j] += a[i - 1][j];
            }
        }
        if (i == n - 1) {
            for (int j = 0; j < m; j++) ans += a[i][j];
        }
        for (int j = 0; j < m; j++) cerr << a[i][j] << " "; cerr << endl;
    }
    cout << "ans = " <<  ans << endl;

}