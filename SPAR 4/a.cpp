#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ff first
#define ss second
typedef long long ll;
typedef vector<int> vi;
ll w, s, T = 29260, G = 29370;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> w >> s;
    ll tot = 1ll * s * (s + 1) / 2ll;
    ll W = tot * T - w;
    ll ans = W / (T - G);
    cout << ans << endl;
    return 0;
}