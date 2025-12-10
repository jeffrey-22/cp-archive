#include "template.cpp"

int n;

vector<int> f;
int getf(int x) {return x == f[x]? x : f[x] = getf(f[x]);}
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

    vector<tuple<ll, int, int>> cons = {};
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            ll dd = 0;
            for (int k = 0; k < m; k++) dd += (a[i][k] - a[j][k]) * (a[i][k] - a[j][k]);
            cons.push_back({dd, i, j});
        }
    f = vector<int>(n);
    for (int i = 0; i < n; i++) f[i] = i;
    sort(all(cons));
    for (int i = 0; i < min(1000, sz(cons)); i++) {
        auto [dist, u, v] = cons[i];
        u = getf(u);
        v = getf(v);
        if (u != v) f[u] = v;
    }
    vector<int> s(n, 0);
    for (int i = 0; i < n; i++) s[getf(i)]++;
    sort(all(s)); reverse(all(s));
    cout << 1ll * s[0] * s[1] * s[2] << endl;
}