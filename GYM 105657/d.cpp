#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int nlim = 5000;
int m = 3;
const int M = 4;
const ll B[M] = {0, 100001, 100007, 998244353};
ll Bpow[M][5009];
const ll P[M] = {0, 998244353, 1000000007, 1000000009};
ll modpow(ll b, ll e, ll mod) {
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1) ans = ans * b % mod;
    return ans;
}
int n, p, x, y;
int a[5009];
ll Ha[M][5009];
vector<int> C;
vector<ll> HC[M];
set<pair<int, int>> CV;
int findy(int v) {
    auto it = CV.upper_bound(make_pair(v, nlim));
    if (it == CV.begin()) {
        return sz(C);
    }
    --it;
    return it->second;
}
int findmatch() {
    int L = 0; int R = min(y - x, n - p + 2);
    int M;
    while (L < R) {
        M = (L + R + 1) >> 1;
        int is_match = 1;
        for (int t = 1; t <= m; t++) {
            // x, len = M; p, len = M
            ll hash_A_val = Ha[t][p + M - 1] - Ha[t][p - 1];
            ll hash_C_val = HC[t][x + M - 1] - (x == 0 ? 0 : HC[t][x - 1]);
            hash_A_val *= Bpow[t][x];
            hash_C_val *= Bpow[t][p - 1];
            hash_A_val %= P[t]; hash_A_val += P[t]; hash_A_val %= P[t];
            hash_C_val %= P[t]; hash_C_val += P[t]; hash_C_val %= P[t];
            if (hash_A_val != hash_C_val) {is_match = 0; break;}
        }
        if (is_match)
            L = M;
        else
            R = M - 1;
    }
    return L;
}
int main() {
    for (int t = 1; t <= m; t++) {
        for (int i = 0; i <= nlim; i++) {
            Bpow[t][i] = modpow(B[t], i, P[t]);
        }
    }
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        a[n + 1] = 0;
        for (int i = 1; i <= n + 1; i++) {
            for (int t = 1; t <= m; t++) {
                ll prevsum = 0; if (i >= 2) prevsum = Ha[t][i - 1];
                ll cursum = prevsum + Bpow[t][i - 1] * a[i];
                Ha[t][i] = cursum % P[t];
            }
        }
        C.clear(); CV.clear();
        for (int t = 1; t <= m; t++) HC[t].clear();
        p = 1; x = 0;
        while (1) {
            int L = 0; int R = 100000; int M;
            while (L < R) {
                M = (L + R) >> 1;
                int is_M_ok = 0;
                y = findy(M);
                int len_match = findmatch();
                if (a[p + len_match] <= M || (x + len_match < sz(C) && C[x + len_match] > a[p + len_match]))
                    is_M_ok = 1;
                if (p == 4 && !is_M_ok && M >= 1 && M <= 3) {
                    cout << x << " " << y << " " << len_match << endl;
                }
                if (is_M_ok)
                    R = M;
                else
                    L = M + 1;
            }
            if (R == 0)
                break;
            y = findy(R);
            int len_match = findmatch();
            C.push_back(a[p + len_match]);
            for (int i = x; i < x + len_match; i++)
                CV.erase({C[i], i});
            CV.insert({C.back(), sz(C) - 1});
            x += len_match;
            p += len_match + 1;
            for (int t = 1; t <= m; t++) {
                ll prevsum = 0; if (sz(HC[t]) >= 1) prevsum = HC[t].back();
                ll cursum = prevsum + Bpow[t][sz(C) - 1] * C.back();
                HC[t].push_back(cursum % P[t]);
            }
        }
        cout << sz(C) << endl;
        for (auto v : C) cout << v << " "; cout << endl;
    }

    return 0;
}