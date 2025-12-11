#include "template.cpp"

int N, m, tot, src, goal;
ll ans;
map<string, int> nameid;
map<int, string> idname;
map<int, ll> F;
vector<vector<ll>> e = {};

ll dp(int u) {
    if (u == goal) return 1;
    if (F[u]) return F[u];
    F[u] = 0;
    for (auto v : e[u])
        F[u] += dp(v);
    return F[u];
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    vector<string> tokens;
    vector<vector<string>> allTokens;
    while (1) {
        tokens = readTokens();
        if (tokens.empty()) break;
        N++;
        allTokens.push_back(tokens);
    }
    cerr << "N = " << N << endl;

    for (int Tt = 0; Tt < N; Tt++) {
        for (string t : allTokens[Tt]) {
            string tt = t; if (tt[sz(tt) - 1] == ':') tt.pop_back();
            if (!nameid[tt]) nameid[tt] = ++tot, idname[tot] = tt;
        }
    }
    e = vector<vector<ll>>(tot + 1, vector<ll>());
    for (int Tt = 0; Tt < N; Tt++) {
        vector<string> tokens = allTokens[Tt];

        string src = tokens[0]; if (src[sz(src) - 1]==':') src.pop_back(); int u = nameid[src];
        for (int i = 1; i < sz(tokens); i++) {
            int v = nameid[tokens[i]];
            e[u].push_back(v);
        }
    }
    src = nameid["you"];
    goal = nameid["out"];
    ans = dp(src);
    
    cout << "answer = " << ans << endl;
}