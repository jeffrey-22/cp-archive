#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < b; i++)
int n;
ll s[200009], sl[200009], sr[200009];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    sl[1] = 0;
    for (int i = 2; i <= n; i++) {
        sl[i] = max(sl[i - 1], s[i] - s[i - 1]);
    }
    sr[n] = 0;
    for (int i = n - 1; i >= 1; i--) {
        sr[i] = max(sr[i + 1], s[i + 1] - s[i]);
    }
    ll ans = LLONG_MAX;
    for (int i = 2; i < n; i++) {
        ll val = max(sl[i - 1], sr[i + 1]);
        // cerr << i << " " << val << endl;
        val = max(val, s[i + 1] - s[i - 1]);
        // cerr << i << " " << val << endl;
        ans = min(ans, val);
    }
    cout << ans << endl;
}