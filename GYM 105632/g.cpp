#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=(a);i<(b);i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int m = 3, lim = 200001;
ll modpow(ll x, ll y, ll p) {
    ll r = 1;
    while (y) {
        if (y & 1) {r = r * x % p;}
        x = x * x % p; y >>= 1ll;
    }
    return r;
}
int n, q;
ll a[200009], bp[3][200009], bvp[3][200009];
ll b[3] = {200009, 300007, 100007}, p[3] = {998244353, 1000000000+7, 1000000000+9};
ll s[3][800009], vs[3][800009], tag[3][800009], vtag[3][800009], sum[800009], stag[800009];
void pushup(int o) {
    rep(t,0,m) {
        s[t][o] = (s[t][o<<1] + s[t][o<<1|1]) % p[t];
        vs[t][o] = (vs[t][o<<1] + vs[t][o<<1|1]) % p[t];
    }
    sum[o] = sum[o<<1] + sum[o<<1|1];
}
void oneadd(int o, int l, int r, ll val) {
    sum[o] += val * (r - l + 1);
    stag[o] += val;
}
void onemod(int o, int t, ll t1, ll t2) {
    s[t][o] *= t1; s[t][o] %= p[t];
    vs[t][o] *= t2; vs[t][o] %= p[t];
    tag[t][o] *= t1; tag[t][o] %= p[t];
    vtag[t][o] *= t2; vtag[t][o] %= p[t];
}
void pushdown(int o, int l, int r) {
    int mid = (l + r) >> 1;
    oneadd(o<<1, l, mid, stag[o]); 
    oneadd(o<<1|1, mid + 1, r, stag[o]); 
    stag[o] = 0;
    rep(t, 0, m) {
        onemod(o<<1, t, tag[t][o], vtag[t][o]);
        onemod(o<<1|1, t, tag[t][o], vtag[t][o]);
        tag[t][o] = 1, vtag[t][o] = 1;
    }
}
void add(int o, int l, int r, int ql, int qr, int val) {
    if (l > qr || r < ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        rep(t,0,m) {
            onemod(o, t, bp[t][val], bvp[t][val]);
        }
        oneadd(o, l, r, val);
        return;
    }
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    add(o<<1, l, mid, ql, qr, val);
    add(o<<1|1, mid + 1, r, ql, qr, val);
    pushup(o);
}
void build(int o, int l, int r) {
    if (l == r) {
        rep(t, 0, m) s[t][o] = bp[t][a[l]], vs[t][o] = bvp[t][a[l]]; sum[o] = a[l];
        return;
    }
    rep(t, 0, m) tag[t][o] = vtag[t][o] = 1; stag[o] = 0;
    int mid = (l + r) >> 1;
    build(o<<1, l, mid);
    build(o<<1|1, mid + 1, r);
    pushup(o);
}
void query(int o, int l, int r, int ql, int qr, ll s1[m], ll s2[m], ll &tot) {
    if (l > qr || r < ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        rep(t,0,m) {
            s1[t] = (s1[t] + s[t][o]) % p[t];
            s2[t] = (s2[t] + vs[t][o]) % p[t];
        }
        tot += sum[o];
        return;
    }
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    query(o<<1, l, mid, ql, qr, s1, s2, tot);
    query(o<<1|1, mid + 1, r, ql, qr, s1, s2, tot);
    // ll S2 = tag[0][o];
    // pushup(o); assert(tag[0][o] == S2);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    rep(t,0,m) {
        bp[t][0] = 1;
        for (int i = 1; i <= lim; i++) bp[t][i] = bp[t][i - 1] * b[t] % p[t];
        bvp[t][lim] = modpow(bp[t][lim], p[t] - 2, p[t]);
        for (int i = lim - 1; i >= 0; i--) bvp[t][i] = bvp[t][i + 1] * b[t] % p[t];
        assert(bvp[t][0] == 1);
    }
    cin >> n >> q; for (int i = 1; i <= n; i++) cin >> a[i];
    // srand(time(0)); n = 30, q = 2000; for (int i = 1; i <= n; i++) a[i] = rand() % 100 + 1;
    build(1, 1, n);
    while (q--) {
        int op; 
        cin >> op;
        // op = rand() % 2 + 1;
        if (op == 1) {
            int L, R, val;
            cin >> L >> R >> val;
            // do {L = rand() % n + 1, R = rand() % n + 1, val = rand() % 100 + 1;} while (L > R);
            // for (int i = L; i <= R; i++) a[i] += val;
            add(1, 1, n, L, R, val);
        } else {
            int L, R;
            cin >> L >> R;
            // do {L = rand() % n + 1, R = rand() % n + 1;} while (L > R || (R - L + 1) % 2 == 1);
            // int realok = 1; ll realsum = 0;
            // vector<ll> A = {}; for (int i = L; i <= R; i++) A.push_back(a[i]); sort(all(A));
            // realsum = A[0] + A.back(); for (int i = 0; i < sz(A); i++) if (A[i] + A[sz(A) - i - 1] != realsum) {realok = 0; break;}
            ll s1[m], s2[m], tot;
            memset(s1, 0, sizeof(s1));
            memset(s2, 0, sizeof(s2));
            tot = 0;
            query(1, 1, n, L, R, s1, s2, tot);
            // cout << s1[0] << " " << s2[0] << " " << tot << endl;
            ll cnt = R - L + 1; cnt /= 2;
            int ok = 1;
            if (tot % cnt) {
                ok = 0;
            }
            ll indvsum = tot / cnt;
            rep(t, 0, m) {
                ll delta = modpow(b[t], indvsum, p[t]);
                if (s2[t] * delta % p[t] != s1[t]) {ok = 0; break;}
            }
            if (!ok) {
                cout << "No" << endl;
                continue;
            }
            cout << "Yes" << endl;
            // assert(ok == realok);
        }
    }
}