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
        vector<int> A = a[i];
        vector<vector<ll>> f(m, vector<ll>(13, 0)); // f[i][j] = max num at i with j used
        f[0][0] = 0;
        f[0][1] = A[0];
        for (int j = 1; j < m; j++) {
            f[j][0] = f[j - 1][0];
            for (int k = 1; k <= 12; k++) {
                f[j][k] = max(f[j - 1][k - 1] * 10 + A[j], f[j - 1][k]);
            }
        }
        cerr << f[m - 1][12] << endl;
        ans += f[m - 1][12];
    }

    cout << "ans = " <<  ans << endl;

}