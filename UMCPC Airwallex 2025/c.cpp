#include <bits/stdc++.h>

#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
#pragma GCC optimize ("trapv")

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
int n;
int l[100009], a[100009], b[100009];
ll A = 0, B = 0, C = 0;
tuple<int, int, int> v[100009];
ll ans = LLONG_MAX;
ll f(int x) {
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        int d = abs(x - l[i]);
        sum += 1ll * a[i] * d + 1ll * b[i] * d * d;
    }
    return sum;
}
ll g(int x) {
    return A * x * x + B * x + C;
}
void solve(int l, int r) {
    if (l > r) return;
    ans = min(ans, g(l));
    ans = min(ans, g(r));
    ll t = -B / A / 2ll;
    for (int s = t - 1; s <= t + 1; s++)
        if (l <= s && s <= r)
            ans = min(ans, g(s));
}
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> l[i];
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) {
        v[i] = {l[i], a[i], b[i]};
    }
    sort(v + 1, v + n + 1);
    auto [l, a, b] = v[1];
    ans = min(ans, f(l - 1));
    auto [l2, aa, bb] = v[n];
    ans = min(ans, f(l2 + 1));
    for (int i = 1; i <= n; i++) {
        auto [l, a, b] = v[i];
        A += b;
        B += - 1ll * a - 2ll * b * l;
        C += 1ll * b * l * l + 1ll * a * l;
    }
    for (int i = 1; i < n; i++) {
        auto [l, a, b] = v[i];
        auto [l2, aa, bb] = v[i + 1];
        B += 2ll * a;
        C -= 2ll * a * l;
        solve(l + 1, l2 - 1);
    }
    cout << ans << endl;
    return 0;
}