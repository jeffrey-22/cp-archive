#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

void work() {
    ll L, R;
    cin >> L >> R;
    ll l = 0, k = 62;
    while (k) {
        bool flag = 0;
        for (int i = 0; i < 4; i++) {
            ll lo = l + i * (1LL << (k - 2)), hi = l + (i + 1) * (1LL << (k - 2));
            if (lo <= L && R < hi) {
                l = lo;
                k -= 2;
                flag = 1;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    ll ans = L - l;
    if (ans >= (1LL << (k - 1))) {
        ans -= 1LL << (k - 1);
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    int T;
    cin >> T;
    while (T--) {
        work();
    }

    return 0;
}