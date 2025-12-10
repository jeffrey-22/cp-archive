#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, k, histmax;
int a[200009], b[200009];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        set<pair<int, int>> S = {};
        histmax = 0;
        for (int i = 1; i <= k; i++)
            S.insert({0, i});
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1) {
                auto it = S.begin();
                auto [x, y] = *it; S.erase(it);
                x++;
                b[i] = y;
                S.insert({x, y});
            } else {
                auto it = S.end(); it--;
                auto [x, y] = *it; S.erase(it);
                x--; x = max(x, 0);
                b[i] = y;
                S.insert({x, y});
            }
        }
        for (int i = 1; i <= n; i++)
            cout << b[i] << " ";
        cout << endl;
    }
}