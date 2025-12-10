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

    int m;
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        string str = allTokens[i][0];
        m = sz(str);
        a[i] = vector<int>(m, 0);
        for (int j = 0; j < m; j++)
            a[i][j] = ((str[j]) == '@') ? 1 : 0;
    }
    cerr << "m = " << m << endl;
    
    ll ans = 0;
    while (1) {
        int ok = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int cnt = 0;
                for (int dx = -1; dx <= 1; dx++)
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        int x = i + dx;
                        int y = j + dy;
                        if (x < 0 || y < 0 || x >= n || y >= m) continue;
                        // if (i == 0 && j == 2 && a[x][y]) cerr << x << "-" << y << endl;
                        cnt += a[x][y];
                    }
                // cerr << i << " " << j << " " << cnt << endl;
                if (cnt < 4 && a[i][j] == 1) {
                    // ans++;
                    // cerr << i << " " << j << " " << cnt << endl;
                    a[i][j] = 0;
                    ok = 0;
                    ans++;
                }
            }
        }
        if (ok) break;
    }

    cout << "ans = " <<  ans << endl;

}