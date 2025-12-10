#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, m, n_fake;
int a[39][3], isleft[39], n_votes[39], winner_ok[39];
vector<int> ans = {};
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> m >> n_fake;
    for (int i = 1; i <= m; i++)
        for (int j = 0; j < 3; j++)
            cin >> a[i][j];
    for (int A = 1; A <= n; A++)
        for (int B = 1; B <= n; B++)
            for (int C = 1; C <= n; C++) {
                vector<int> me(3);
                me[0] = A, me[1] = B, me[2] = C;
                if (A == B || A == C || B == C) continue;
                for (int i = 1; i <= n; i++) n_votes[i] = 0, isleft[i] = 1;
                for (int round = 1; round < n; round++) {
                    for (int i = 1; i <= n; i++) n_votes[i] = 0;
                    for (int i = 1; i <= m; i++) {
                        for (int j = 0; j < 3; j++) {
                            auto v = a[i][j];
                            if (isleft[v]) {
                                n_votes[v]++;
                                break;
                            }
                        }
                    }
                    for (int j =0; j < 3; j++) {
                        auto v = me[j];
                        if (isleft[v]) {
                            n_votes[v] += n_fake;
                            break;
                        }
                    }
                    pii min_v = {1000, 0};
                    for (int i = 1; i <= n;i++)
                        if (isleft[i])
                            min_v = min(min_v, make_pair(n_votes[i], -i));
                    isleft[-min_v.second] = 0;
                }
                for (int i = 1; i <= n; i++)
                    if (isleft[i])
                        winner_ok[i] = 1;
            }
    for (int u = 1; u <= n; u++) {
        if (winner_ok[u])
            ans.push_back(u);
    }
    for (auto t : ans) cout << t << " "; cout << endl;
}
/*
4 3 1
3 4 1
2 3 4
2 4 3

*/