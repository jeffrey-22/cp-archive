#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < b; i++)
int n;
int e[29][29], od[29], ct[29], flag[29];
string str;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string aa, bb, cc;
        cin >> aa >> bb >> cc;
        if (bb == ">") swap(aa, cc);
        int x = aa[0] - 'a' + 1;
        int y = cc[0] - 'a' + 1;
        e[x][y] = 1;
    }
    cin >> str;
    for (int x = 1; x <= 26; x++) {
        for (auto c : str) if ((c - 'a' + 1) == x) {ct[x]++;}
        if (ct[x] > 0) continue;
        for (int y = 1; y <= 26; y++) e[x][y] = e[y][x] = 0;
    }
    for (int t = 1; t <= 26; t++) {
        int head = -1;
        for (int x = 1; x <= 26; x++) {
            if (flag[x]) continue;
            int cntin = 0;
            for (int y = 1; y <= 26; y++) cntin += e[y][x];
            if (cntin == 0) {head = x; break;}
        }
        if (head == -1) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
        od[t] = head;
        flag[head] = 1;
        for (int y = 1; y <= 26; y++)
            e[head][y] = 0;
    }
    for (int x = 1; x <= 26; x++) {
        int chr = od[x];
        int t = ct[x];
        while (t--)
            cout << (char)('a' + chr - 1);
    }
    cout << endl;
}