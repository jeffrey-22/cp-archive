#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
struct FT {
vector<ll> s;
FT(int n) : s(n) {}
void update(int pos, ll dif) { // a [ pos ] += d i f
for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
}
ll query(int pos) { // sum of values in [0 , pos)
ll res = 0;
for (; pos > 0; pos &= pos - 1) res += s[pos-1];
return res;
}
int lower_bound(ll sum) {// min pos s t sum of [0 , pos ] >= sum
// Returns n i f no sum is >= sum, or =1 i f empty sum is .
if (sum <= 0) return -1;
int pos = 0;
for (int pw = 1 << 25; pw; pw >>= 1) {
if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
pos += pw, sum -= s[pos-1];
}
return pos;
}
};
int n, m, uv;
int a[100009], b[100009], ca[100009], cb[100009];
map<int, int> compressor;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n; for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m; for (int i = 1; i <= m; i++) cin >> b[i];
    vector<int> uvals = {};
    for (int i = 1; i <= n; i++)
        uvals.push_back(a[i]);
    for (int i = 1; i <= m; i++)
        uvals.push_back(b[i]);
    sort(all(uvals));
    for (auto uval : uvals) {
        if (!compressor[uval])
            compressor[uval] = ++uv;
    }
    for (int i = 1; i <= n; i++) a[i] = compressor[a[i]];
    for (int i = 1; i <= m; i++) b[i] = compressor[b[i]];
    FT fa(uv + 2), fb(uv + 2);
    
}