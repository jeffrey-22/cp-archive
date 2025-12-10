#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int m = 1000, qm = 600;
int n, sum;
int a[10009];
int fa[1009], g[1009];
set<pair<int, int>> tab;
// add an item of value val
void add(int val) {
    for (int i = m; i >= val; i--) {
        fa[i] += fa[i - val];


    }
}
void rem(int val) {
    for (int i = val; i <= m; i++)
        fa[i] -= fa[i - val];
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n;
        for (int j = m; j >= 0; j--) fa[j] = 0;
        tab.clear(); sum = 0;
        fa[0] = 1;
        int isdone = 0;
        for (int i = 1; i <= n; i++) {
            if (!(cin >> a[i])) exit(0);
            if (isdone) {
                cout << 0 << "\n" << "IGNORE" << endl;
                continue;
            }
            // check for win
            add(a[i]);
            int winatval = 0;
            for (int j = qm; j <= m; j++)
                if (fa[j]) {
                    winatval = j;
                    break;
                }
            if (winatval) {
                // print win discards
                isdone = 1;
                continue;
            }
            rem(a[i]);
            // otherwise, if sum+x < 600, add
            if (sum + a[i] < qm) {
                sum += a[i];
                add(a[i]);
                tab.insert({a[i], i});
                continue;
            }
            // if sum+x > 1000, add min(x, tab max)
            assert(sum + a[i] > m);
            auto it = tab.end(); it--;
            auto [maxval, maxid] = *it; tab.erase(it);
            sum -= maxval; rem(maxval);
            int betterval = 0, addid = 0;
            if (maxval < a[i]) {
                cout << 0 << "\n" << "IGNORE" << endl;
                betterval = maxval, addid = maxid;
            } else {
                cout << "1 " << maxid << "\n" << "TAKE" << endl;
                betterval = a[i], addid = i;
            }
            tab.insert({betterval, addid}); sum += betterval;
            add(betterval);
        }
    }
}