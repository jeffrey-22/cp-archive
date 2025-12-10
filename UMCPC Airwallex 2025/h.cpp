#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size() 
#define pb push_back
// #define ff first
// #define ss second
typedef long long ll;
typedef pair<int, int> pii; 
typedef vector<int> vi;
int n, m, lim;
int a[500009], s[500009], b[500009];
ll ss[500009];
int get() {
    int x = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}
int getcount(int pivot, int m) {
    if (pivot >= m)
        return 0;
    int cnt = 0;
    for (int l = 0; l <= lim; l += m) {
        int r = l + m - 1;
        r = min(r, lim);
        cnt += s[r];
        int l2 = l + pivot;
        l2 = min(l2, r + 1);
        // cout << "pivot " << pivot << " adding " << l2 << " to " << r << endl;
        if (l2 >= 1)
            cnt -= s[l2 - 1];
    }
    return cnt;
}
ll getsum(int pivot, int m) {
    int left = m - getcount(pivot, m);
    ll ret = 1ll * left * (pivot - 1);
    // cout << "GETSUM pivot = " << pivot << " w ret = " << ret << " m = " << m << endl;
    for (int l = 0; l <= lim; l += m) {
        int r = l + m - 1;
        r = min(r, lim);
        int l2 = l + pivot;
        l2 = min(l2, r + 1);
        ll s1 = ss[r] - ss[l2 - 1];
        ll s2 = s[r] - s[l2 - 1];
        ll sum = s1 - 1ll * l * s2;
        // cout << "!adding " << l2 << " to " << r << endl;
        // cout << sum << endl;
        ret += sum;
    }
    return ret;
}
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    Tt = get();
    while (Tt--) {
        n = get();
        lim = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = get();
            lim = max(lim, a[i]);
        }
        for (int i = 1; i <= lim; i++) b[i] = 0; s[0] = 0;
        for (int i = 1; i <= n; i++) b[a[i]]++;
        for (int i = 1; i <= lim; i++) s[i] = s[i - 1] + b[i];
        for (int i = 1; i <= lim; i++) ss[i] = ss[i - 1] + 1ll * b[i] * i;
        ll ans = 0;
        for (int m = max(1, n / 100000); m <= n; m++) {
            int l = 0, r = m, mid;
            while (l < r) {
                mid = (l + r) >> 1;
                if (getcount(mid, m) <= m)
                    r = mid;
                else
                    l = mid + 1;
            }
            // cout << "M " << m << endl;
            // cout << "PIVOT " << l << endl;
            ans = max(ans, getsum(l, m));
        }
        cout << ans << endl;
    }

    return 0;
}
/*
3
5
1 2 3 4 5
5
1 3 3 3 10
5
7 7 7 7 7


1
5
1 2 3 4 5

*/