#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, m, tot, X;
int a[300009];
ll ans = 0;
vector<int> b[500009];
void calcbucket(int x) {
    int y = tot - x;
    int msk = (1 << x) - 1; msk <<= y;
    for (int i = 0; i < (1 << x); i++)
        b[i].clear();
    for (int i = 1; i <= n; i++)
        b[(msk & a[i]) >> y].push_back(i);
    for (int i = 0; i < (1 << x); i++)
        sort(all(b[i]));
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    int tmp = n; while (tmp != 1) {tmp /= 2, tot++;}
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    X = 0;
    for (int x = 1; x <= tot; x++) {
        calcbucket(x);
        ll sum0 = 0, sum1 = 0;
        for (int pre = 0; pre < (1 << (x - 1)); pre++) {
            int m0 = (pre << 1) | 0, m1 = (pre << 1) | 1;
            int sz = n / (1 << x);
            ll SUM = 1ll * sz(b[m0]) * sz(b[m1]);
            int p0 = 0, p1 = 0;
            ll CNT = 0;
            while (p0 < sz(b[m0]) && p1 < sz(b[m1])) {
                if (b[m0][p0] < b[m1][p1])
                    p0++;
                else {
                    CNT += sz(b[m0]) - p0;
                    p1++;
                }
            }
            // cout << "x = " << x << " pre = " << pre << endl;
            // cout << "0:"; for (auto v : b[m0]) cout << v << " "; cout << endl;
            // cout << "1:"; for (auto v : b[m1]) cout << v << " "; cout << endl;
            // cout << "normal cnt = " << CNT << " otherwise = " << SUM - CNT << endl;
            sum0 += CNT;
            sum1 += SUM - CNT;
        }
        if (sum0 <= sum1) {
            ans += sum0;
        } else {
            ans += sum1;
            X++;
        }
    }
    if (X != 0) ans++;
    cout << ans << endl;
}
/*
8
0 1 3 2 5 4 7 6

*/