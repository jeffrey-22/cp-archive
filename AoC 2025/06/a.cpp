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
    vector<vector<ll>> a;
    vector<char> ops;
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            m = sz(allTokens[i]);
            vector<ll> numbers = {};
            for (int j = 0; j < m; j++)
                numbers.push_back(stoll(allTokens[i][j]));
            a.push_back(numbers);
        } else {
            ops.clear();
            for (int j = 0; j < m; j++)
                ops.push_back(allTokens[i][j][0]);
        }
    }
    cerr << "m = " << m << endl;
    
    ll ans = 0;
    for (int x = 0; x < m; x++) {
        ll sum = 0;
        if (ops[x] == '+') {
            for (int i = 0; i < n - 1; i++) {
                sum += a[i][x];
            }
        } else {
            sum = 1;
            for (int i = 0; i < n - 1; i++) {
                sum *= a[i][x];
            }
        }
        ans += sum;
    }

    cout << "ans = " <<  ans << endl;

}