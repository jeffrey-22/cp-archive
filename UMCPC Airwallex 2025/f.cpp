#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size() 
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> pii; 
typedef vector<int> vi;
int n, m;
int a[2009][2009];
pair<int, int>pos[4000009];
void F() {
    puts("DEAD");
    exit(0);
}
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++)
        cin >> pos[i].ff >> pos[i].ss;
    int p = 0;
    for (int i = 1; i <= q; i++) {
        auto [x, y] = pos[i];
        if (a[x + 1][y + 1] == 1 - p)
            F();
        p ^= 1;
    }
    // for (int i = 1; i < q; i++) {
    //     auto [x, y] = pos[i];
    //     auto [xx, yy] = pos[i + 1];
    //     if (abs(x - xx) + abs(y - yy) != 1)
    //         F();
    // }
    puts("Air-Wall-Exit");
    return 0;
}