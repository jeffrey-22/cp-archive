#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int N = 2e5 + 5;

ll ans = 0;
vector<int> son[N];
int n, fa[N];
ll a[N];
ll calc(int x) {
    if (x < 0) {
        return 0;
    }
    ll res = 0;
    map<ll, int> mp;
    for (int to : son[x]) {
        if (mp.count(a[x] - a[to])) {
            res += mp[a[x] - a[to]];
        }
        mp[a[to]]++;
    }
    return res;
}
ll update(int x, int f) {
    return (calc(x) + calc(fa[x])) * f;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> fa[i] >> a[i];
        if (fa[i] > 0) {
            son[fa[i]].emplace_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        ans += calc(i);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;
        ans += update(x, -1);
        a[x] += y;
        ans += update(x, 1);
        cout << ans << "\n";
    }

    return 0;
}