#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int N = 1e6 + 5;

struct bit {
    int n;
    int t[N];
    void init(int _n) {
        n = _n + 1;
        memset(t, 0x3f, sizeof(t));
    }
    void add(int x, int y) {
        x++;
        for (; x <= n; x += x & -x) {
            t[x] = min(t[x], y);
        }
    }
    int query(int x) {
        x++;
        int res = 1e9 + 7;
        for (; x; x &= x - 1) {
            res = min(res, t[x]);
        }
        return res;
    }
}t;
int a[N];
ll sum[N], b[N];

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;
    t.init(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] -= k;
        b[i] = sum[i] = sum[i - 1] + a[i];
    }
    sort(b, b + n + 1);
    int m = unique(b, b + n + 1) - b;
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        sum[i] = lower_bound(b, b + m + 1, sum[i]) - b;
        ans = max(ans, i - t.query(sum[i]));
        t.add(sum[i], i);
    }
    cout << ans << "\n";

    return 0;
}