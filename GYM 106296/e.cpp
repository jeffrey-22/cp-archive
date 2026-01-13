#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int(x).size())
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int m = 20;
int n;
int a[1000009], ps[1000009];
int cnt[2100009][21];
int s[2100009];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        ps[i] = ps[i - 1] ^ a[i];
    for (int i = 1; i <= n - 1; i++) {
        s[ps[i]] += 1;
    }
    for (int d = 0; d <= m - 1; d++) {
        for (int msk = 0; msk < (1 << m); msk++)
            if (msk & (1 << d))
                s[msk] += s[msk ^ (1 << d)];
    }
    // 0 1 1
    // cout << s[1] << " " << s[2] << " " << s[3] << endl;
    int full = (1 << m) - 1;
    assert(s[full] == n - 1);
    for (int k = 1; k <= n; k++) {
        int left = k - 1;
        int curans = 0;
        int msk0 = 0;
        for (int d = m - 1; d >= 0; d--) {
            int val = 1 << d;
            if (val & ps[n]) {
                curans |= val;
            } else {
                // try to make 0
                int canmake0 = 0;
                // find cnt of values that have cmsk0 as 0
                int cmsk0 = msk0 | val;
                int maxsubset = full - cmsk0;
                int sum = s[maxsubset];
                if (sum >= left) {
                    canmake0 = 1;
                } else canmake0 = 0;
                if (!canmake0)
                    curans |= val; 
                else
                    msk0 |= val;
            }
        }
        cout << curans << " ";
    }
    cout << endl;
}