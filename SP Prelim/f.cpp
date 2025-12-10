#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        int pos, len;
        cin >> pos >> len;
        a[i] = make_pair(pos + len, pos - len);
        x[i] = pos;
    }
    sort(x.begin(), x.end());
    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0, j = 0; i < n; ) {
        while (j + 1 < n && x[j + 1] <= a[i].first) {
            j++;
        }
        while (i < n && a[i].second <= x[j] && x[j] <= a[i].first) {
            i++;
        }
//        cerr << x[j] << ' ' << i << endl;
        ans++;
    }
    cout << ans << "\n";
}
/*
4
1 10
3 1
5 2
10 5

*/