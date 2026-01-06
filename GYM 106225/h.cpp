#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int f[1009][1009];
int check(int n, int m) {
    for (int i = 0; i <= m; i++)
        f[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        vi banpos = {};
        for (int j = 0; j <= m; j++) {
            int findloss = 0;
            for (int k = 1; k <= m; k++)
                if (k != j && (i - k < 0 || f[i - k][k] == 0)) {
                    findloss = 1;
                    break;
                }
            f[i][j] = findloss ? 1 : 0;
            if (f[i][j] == 0) banpos.push_back(j);
        }
        if (banpos.empty()) continue;
        cout << "L:" << i << " ban ";
        if (!banpos.empty() && banpos[0] == 0) cout << "X" << endl;
        else {for (auto v : banpos) cout << v <<" "; cout << endl;}
    }
    return f[n][0];
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    vi a(1000, 0);
    for (int m = 7; m <= 7; m += 2) {
        int n = 100;
        a[n] = check(n, m);
    }
}
/*

f[n] =
    exists f[n - i][i] == 0 ? 1 : 0
f[n][x] =
    exists f[n - y][y] == 0 ? 1 : 0 (x != y)

if m >= n, win in 1 turn
if m even, can guarantee -(m+1) each time, lose if n % (m + 1) == 0
if m odd, say m = 3: x + y in {1+2, 1+3, 2+3} = {3, 4, 5}
(m-1)/2 % 4 == 1: % (m + 1) == 0
% 4 == 2: done
% 4 == 3:
1,2,3,4,5
at 6  ban X: L
at 12 ban 3: L
at 13 ban X: L
at 19 ban 3: L

1,2,3,4,5,6,7
at 8  ban X: L
at 16 ban 4: L
at 17 ban X: L
at 25 ban X: L
at 2
m=3/1  : 3*
m=5/2  : 5 6
m=7/3  : 7 8 7
m=9/4  : 9 10 10
m=11/5 : 11*
m=13/6 : 13 14
m=15/7 : 15
m=17/8 : 17 18 18
m=19/9 : 19*
n=21/10: 21 22
m=23/11: 23 24 24
m=25/12: 25 26
m=27/13: 27*
m=29/14: 29 30
m=31/15: 31 32 31
m=33/16: 33 34 34 34 33 34 34
m=35/17: 35*
m=37/18: 37 38
m=39/19: 39 40
m=41/20: 41 42 42 42 41 42
m=43/21: 43*
*/