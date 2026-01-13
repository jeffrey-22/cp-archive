#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int)((x).size())
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int m;
vector<vector<int>> ans;
int matchTime[29][29];
template<class T> T edmondsKarp(vector<unordered_map<int, T>>&graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vi par(sz(graph)), q = par;
    for (;;) {
        fill(all(par), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;
        rep(i,0,ptr) {
            int x = q[i];
            for (auto e : graph[x]) {
                if (par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if (e.first == sink) goto out;
                }
            }
        }
        return flow;
        out:
        T inc = numeric_limits<T>::max();
        for (int y = sink; y != source; y = par[y])
            inc = min(inc, graph[par[y]][y]);
        flow += inc;
        int time = 0;
        for (int y = sink; y != source; y = par[y]) {
            int p = par[y];
            if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
            graph[y][p] += inc;
            // graph[p][y] flow
            if (y != sink && p != source) {
            // 0, 1, i+1(2~m+1), m+2+a
                time++;
                if (time % 2 == 1) {
                    assert(2 <= p && p <= m + 1 && m + 2 <= y);
                    if (par[p] != source) {
                        // modify
                        int t = matchTime[p - 2][par[p] - m - 2];
                        matchTime[p - 2][y - m - 2] = t;
                        ans[t][p - 2] = y - m - 2;
                        // matchTime of p ~ par[p]
                        // altar p~y at time t
                        // matchTime of p ~ y 
                        cout << "modified " << p - 2 << " to " << (char)(y-m-2 + 'a') << endl;
                    } else {
                        // add to latest
                        ans[sz(ans) - 1][p - 2] = y - m - 2;
                        matchTime[p - 2][y - m - 2] = sz(ans) - 1;
                        cout << "at time " << sz(ans) - 1 << endl;
                        cout << "added " << p - 2 << " to " << (char)(y-m-2 + 'a') << endl;
                    }
                } else {
                    // cout << "! backwards!" << endl;
                }
            }
        }
    }
}
string s[29];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> m;
        for (int i = 1; i <= m; i++) {
            cin >> s[i];
        }
        int T = 0;
        vector<pii> e1s = {}, e2s = {}, e3s = {};
        int Q1[29][29], Q2[29][29];
        ans.clear();
        vector<vi> anstmp = {};
        vector<unordered_map<int, int>> G(2 + m + 26);
        // for (int i = 1; i <= m; i++) {
        //     G[0][i+1] = 1;
        // }
        for (int i = 1; i <= m; i++) {
            vi acnt(26, 0);
            for (auto t : s[i]) acnt[t - 'a']++;
            for (int j = 0; j < 26; j++)
                if (acnt[j] > 0)
                    G[i+1][m+2+j] = acnt[j];
        }
        // for (int i = 0; i < 26; i++) {
        //     G[m+2+i][1] = 1;
        // }
        while (1) {
            T++;
            for (int i = 1; i <= m; i++) {
                G[0][i+1]++;
            }
            for (int i = 0; i < 26; i++) {
                G[m+2+i][1]++;
            }
            // 0, 1, i+1(2~m+1), m+2+a
            e1s.clear(); e2s.clear(); e3s.clear();
            anstmp = ans;
            ans.push_back(vi(m, 0));
            int totflow = edmondsKarp<int>(G, 0, 1);
            if (totflow < m) {ans = anstmp; break;}
            // cout << T << endl;
        }
        T--;
        cout << T << endl;
        for (auto str : ans) {
            for (int i = 0; i < m; i++)
                cout << (char)('a' + str[i]);
            cout << endl;
        }
    }
}