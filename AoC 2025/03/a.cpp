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
            a[i][j] = (str[j]) - '0';
    }
    cerr << "m = " << m << endl;
    
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll best = 0;
        for (int j = 0; j < m; j++)
            for (int k = j + 1; k < m; k++) {
                ll val = a[i][j] * 10 + a[i][k];
                best = max(best, val);
            }
        ans += best;
    }

    cout << "ans = " <<  ans << endl;

}