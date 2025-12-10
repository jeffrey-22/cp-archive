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
int a[2009][2009], c[2009][2009];
int c_cnt = 1;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
void color_dfs(int x, int y, int color) {
    c[x][y] = color;
    for (int i = 0; i < 4; i++) {
        int ax = x + dx[i], ay = y + dy[i];
        if (ax < 0 || ay < 0 || ax > 2000 || ay > 2000)
            continue;
        if (a[ax][ay] || c[ax][ay])
            continue;
        color_dfs(ax, ay, color);
    }
}
string str;
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    int x, y; x = y = 0;
    a[1001][1001] = 1;
    int dir = 0; // 0 N 1 E 2 S 3 W
    for(int i = 0; i < n; i++){
        cin >> str;
        if (str == "F") {
            if (dir == 0)
                y++;
            else if (dir == 1)
                x++;
            else if (dir == 2)
                y--;
            else
                x--;
            a[x + 1001][y + 1001] = 1;
        }
        else if (str == "L") {
            dir--; if (dir == -1) dir = 3;
        }
        else {
            dir++; if (dir == 4) dir = 0;
        }
    }

    // cout << "C" << c_cnt << endl;
    color_dfs(0, 0, 1);
    for (int i = 0; i <= 2000; i++)
        for (int j = 0; j <= 2000; j++)
            if (!a[i][j] && !c[i][j])
                color_dfs(i, j, ++c_cnt);
    // cout << "C" << c_cnt << endl;
    int f[2009];
    memset(f, 0, sizeof(f));
    for (int i = 0; i <= 2000; i++)
        for (int j = 0; j <= 2000; j++)
            if (!a[i][j] && c[i][j])
                f[c[i][j]]++;
    int ans = 0;
    for (int i = 2; i <= c_cnt; i++)
        ans = max(ans, f[i]);
    if (ans == 0) ans = -1;
    cout << ans << endl;
    return 0;
}