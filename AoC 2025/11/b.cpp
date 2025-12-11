#include "template.cpp"

int N, m, tot, src, goal, f1, f2;
ll ans;
map<string, int> nameid;
map<int, string> idname;
map<int, ll> F[4];
map<int, ll> vis[4];
vector<vector<ll>> e = {};

ll dp(int u, int msk) {
    if (u == goal) {
        if (msk == 3) return 1;
        else return 0;
    }
    // if (u == f1 && msk & 1 == 1) return 0;
    // if (u == f2 && msk & 2 > 0) return 0;
    // cerr << u << " " << msk << endl;
    if (vis[msk][u]) return F[msk][u]; 
    int nmsk = msk;
    if (u == f1) nmsk |= 1;
    if (u == f2) nmsk |= 2;
    F[msk][u] = 0;
    for (auto v : e[u])
        F[msk][u] += dp(v, nmsk);
    vis[msk][u] = 1;
    return F[msk][u];
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
    src = nameid["svr"];
    goal = nameid["out"];
    f1 = nameid["dac"];
    f2 = nameid["fft"];
    // vector<int> loopid = {536,595,524,143,509,143,144};
    // for (auto id : loopid) cerr << idname[id] << " "; cerr << endl;
    ans = dp(src, 0);
    
    cout << "answer = " << ans << endl;
}
/*
536 595 524 143 509 143 144

*/