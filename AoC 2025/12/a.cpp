#include "template.cpp"

int N, n, m, nn, mm, success, tot;
vector<vector<int>> a;
vector<vector<vector<vector<int>>>> var;
vector<int> invalidvar;
vector<pair<int, int>> conflict;
vector<vector<vector<vector<int>>>> pattern;
ll ans;

vector<vector<int>> fliph(vector<vector<int>> s) {
    for (int i = 0; i < 3; i++) swap(s[0][i], s[2][i]); return s;
}
vector<vector<int>> flipv(vector<vector<int>> s) {
    for (int i = 0; i < 3; i++) swap(s[i][0], s[i][2]); return s;
}
vector<vector<int>> rotateclk(vector<vector<int>> s) {
    vector<vector<int>> q(3, vector<int>(3, 0));
    q[1][1] = s[1][1], q[0][0] = s[2][0], q[0][1] = s[1][0], q[0][2] = s[0][0], q[1][2] = s[0][1], q[2][2] = s[0][2],
    q[2][1] = s[1][2], q[2][0] = s[2][2], q[1][0] = s[2][1];
    return q;
}
bool iseq(vector<vector<int>> a, vector<vector<int>> b) {
    rep(i, 0, 3) rep(j, 0, 3) if (a[i][j] != b[i][j]) return 0; return 1;
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

    vector<vector<vector<int>>> shape = {};
    vector<tuple<int, int, vector<int>>> query = {};
    for (int Tt = 0; Tt < N; Tt++) {
        vector<string> tokens = allTokens[Tt];
        if (sz(tokens) == 1 && tokens[0][sz(tokens[0]) - 1] == ':') {
            int shapeidx = sz(shape);
            vector<vector<int>> pat(3, vector<int>(3, 0));
            for (int x = Tt + 1; x <= Tt + 3; x++) {
                string nxtline = allTokens[x][0];
                for (int i = 0; i < 3; i++) if (nxtline[i] == '#') pat[x - Tt - 1][i] = 1;
            }
            shape.push_back(pat);
            Tt += 3; continue;
        } else {
            vector<int> shcnt(sz(shape), 0);
            string dimstr = tokens[0];
            for (int i = 1; i < sz(tokens); i++)
                shcnt[i - 1] = stoi(tokens[i]);
            int dimwid, dimlong;
            int val = 0; for (int i = 0; i < sz(dimstr); i++) if (dimstr[i]>='0'&&dimstr[i]<='9')val=val*10+dimstr[i]-'0';
            else if (dimstr[i]=='x')dimwid=val,val=0; else if (dimstr[i]==':')dimlong=val,val=0;
            query.push_back({dimlong, dimwid, shcnt});
        }
    }
    n = sz(shape);
    m = sz(query);
    cerr << "n = " << n << ", m = " << m << endl;
    for (int x = 0; x < n; x++) {
        vector<vector<vector<int>>> p = {};
        vector<vector<int>> s = shape[x];
        for (int i = 0; i < 4; i++) {
            int doub;
            doub=0;for (auto t : p) if (iseq(t, s)){doub=1;break;}if(!doub) p.push_back(s);
            doub=0;for (auto t : p) if (iseq(t, fliph(s))){doub=1;break;}if(!doub) p.push_back(fliph(s));
            doub=0;for (auto t : p) if (iseq(t, flipv(s))){doub=1;break;}if(!doub) p.push_back(flipv(s));
            s = rotateclk(s);
        }
        pattern.push_back(p);
    }
    int notsurecnt = 0;
    for (auto [val1, val2, shcnt] : query) {
        nn = val1, mm = val2; success = 0;
        a = vector<vector<int>>(nn + 2, vector<int>(mm + 2,0));
        for (int xx = 0; xx <= nn + 1; xx++) for (int yy = 0; yy <= mm + 1; yy++)
            if (xx == 0 || xx > nn || yy == 0 || yy > mm) a[xx][yy] = 1; else a[xx][yy] = 0;
        vector<int> gcnt(n, 0);
        int totg = 0;
        for (int i = 0; i < n; i++) {
            auto exp = pattern[i][0];
            for (auto vec : exp) for (auto t : vec) gcnt[i] += t;
            totg += gcnt[i] * shcnt[i];
        }
        int totsh = 0;
        for (auto t : shcnt) totsh += t;
        int tot3x3 = (nn / 3) * (mm / 3);
        if (totg > nn * mm) {
            success = 0;
            cerr << "impossible" << endl;
        } else if (totsh <= tot3x3) {
            success = 1;
            cerr << "won" << endl;
        } else {
            notsurecnt++;
            cerr << "not sure" << endl;
        }
        cerr << "(" << nn << "," << mm << ")" << (success?" is ok!":"is fail") << endl;
        if (success) ans++;
    }
    cerr << "not sure cnt = " << notsurecnt << endl;
    cout << "answer = " << ans << endl;
}