#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ff first
#define ss second
typedef long long ll;
typedef vector<int> vi;
int mp[59][59];
int n, m;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    string str;
    for (int i = 1; i <= n; i++) {
        cin >> str;
        for (int j = 1; j <= m; j++)
            if (str[j - 1] == '0')
                mp[i][j] = 1;
            else
                mp[i][j] = 0;
    }
    int ans =0 , ansx, ansy;
    for (int i = 2; i < n; i++)
        for (int j = 2; j < m; j++) {
                if (mp[i][j] != 1) continue;
                int C = 0;
                for (int x = -1; x <= 1; x++)
                    for (int y = -1; y<= 1; y++) {
                        int xx = i + x;
                        int yy= j + y;
                        if (mp[xx][yy] == 0)
                            C++;
                    }
                if (C == 8) {
                    ans++;
                    ansx=i;
                    ansy=j;
                }
            }
    if (ans == 1)
            cout << ansx << " " << ansy<< endl;
    else if (ans == 0)
        cout << "Oh no!" << endl;
    else
        cout << "Oh no! " << ans << " locations" << endl;
    return 0;
}