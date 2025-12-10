#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const ll F = 9223372036854775807ll;
int n, q, op, l, r;
ll a[1000009], x;
int sz[4000009];
ll tag[4000009], sum[4000009], qsum[4000009];
ll read() {
    ll x = 0;
    char ch = ' ';
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
    return x;
}
void put(int o) {
    if (tag[o] == F) return;
    tag[o<<1] &= tag[o];
    sum[o<<1] &= tag[o];
    if (sz[o<<1] == 1) qsum[o<<1] = F; else qsum[o<<1] &= tag[o];
    tag[o<<1|1] &= tag[o];
    sum[o<<1|1] &= tag[o];
    if (sz[o<<1|1] == 1) qsum[o<<1|1] = F; else qsum[o<<1|1] &= tag[o];
    tag[o] = F;
}
pair<ll, ll> combine(pair<ll, ll> a, pair<ll, ll> b) {
    return make_pair(
        a.first & b.first,
        (a.first & b.second) | (a.second & b.first)
    );
}
void push(int o) {
    sum[o] = sum[o<<1] & sum[o<<1|1];
    qsum[o] = (sum[o<<1] & qsum[o<<1|1]) | (qsum[o<<1] & sum[o<<1|1]);
}
void build(int o, int l, int r) {
    sz[o] = r - l + 1;
    if (l == r) {
        sum[o] = a[l]; tag[o] = F; qsum[o] = F;
        return;
    }
    tag[o] = F;
    int m = (l + r) >> 1;
    build(o<<1, l, m);
    build(o<<1|1, m + 1, r);
    // cout << sum[o<<1] << " x " << sum[o<<1|1] << endl;
    push(o);
    // if (sum[o] == 0) cout << o << " " << sum[o] << endl;
}
void add(int o, int ql, int qr, int l, int r, ll val) {
    // cout << o << " !" << ql << "vs" << l << "   " << qr << " vs" << r << endl;
    if (qr < l || r < ql)
        return;
    if (ql <= l && r <= qr) {
        sum[o] &= val; tag[o] &= val;
        if (sz[o] == 1) qsum[o] = F; else qsum[o] &= val;
        return;
    }
    int m = (l + r) >> 1;
    put(o);
    add(o << 1, ql, qr, l, m, val);
    add(o << 1|1, ql, qr, m + 1, r, val);
    push(o);
}
void modify(int o, int pos, ll val, int l, int r) {
    if (l == r) {sum[o] = val; qsum[o] = F; return;}
    int m = (l + r) >> 1;
    put(o);
    if (pos <= m)
        modify(o << 1, pos, val, l, m);
    else
        modify(o << 1|1, pos, val, m + 1, r);
    push(o);
}
void findseg(int o, int ql, int qr, int l, int r, vector<tuple<int, int, int>>& segs) {
    if (ql <= l && r <= qr) {
        segs.push_back({o, l, r});
        return;
    }
    put(o);
    int m = (l + r) >> 1;
    if (qr <= m) {findseg(o << 1, ql, qr, l, m, segs); return;}
    if (ql >= m + 1) {findseg(o << 1 | 1, ql, qr, m + 1, r, segs); return;}
    findseg(o << 1, ql, qr, l, m, segs);
    findseg(o << 1 | 1, ql, qr, m + 1, r, segs);
}
ll query(int o, int l, int r, ll nval = F) {
    if (l == r) return nval;
    int m = (l + r) >> 1;
    // cout << l << " - " << r << endl;
    // cout << tag[o] << " " << sum[o<<1] << " " << sum[o<<1|1] << "!1" << endl;
    put(o);
    // cout << sum[o<<1] << " " << sum[o<<1|1] << "!2" << endl;
    ll gl = qsum[o<<1] & sum[o<<1|1] & nval;
    ll gr = qsum[o<<1|1] & sum[o<<1] & nval;
    if (gl > gr)
        return query(o<<1, l, m, nval & sum[o<<1|1]);
    else
        return query(o<<1|1, m + 1, r, nval & sum[o<<1]);
}
int main() {
    n = read(); q= read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    build(1, 1, n);
    while (q--) {
        op = read();
        if (op == 1) {
            l = read(); r = read(); x = read();
            add(1, l, r, 1, n, x);
        } else if (op == 2) {
            int pos;
            pos = read(); x = read();
            modify(1, pos, x, 1, n);
        } else {
            l = read(); r = read();
            vector<tuple<int, int, int>> segs = {};
            findseg(1, l, r, 1, n, segs);
            ll ans = -1;
            if (sz(segs) == 1) {
                auto [o, ool, oor] = segs[0];
                ans = query(o, ool, oor);
            } else {
                int m = sz(segs);
                vector<pair<ll,ll>> F(m);
                vector<int> s(m); for (int i = 0; i < m; i++) {auto [o,l,r] = segs[i]; s[i] = o;}
                F[0] = {sum[s[0]], qsum[s[0]]};
                for (int i = 1; i < m; i++)
                    F[i] = combine(F[i - 1], {sum[s[i]], qsum[s[i]]});
                vector<pair<ll,ll>> G(m);
                G[m - 1] = {sum[s[m - 1]], qsum[s[m - 1]]};
                for (int i = m - 2; i >= 0; i--)
                    G[i] = combine(G[i + 1], {sum[s[i]], qsum[s[i]]});
                ll best = -1; int bestid;
                for (int i = 0; i < m; i++) {
                    pair<ll, ll> O;
                    if (i == 0) O = G[i + 1]; else if (i == m - 1) O = F[i - 1]; else O = combine(F[i - 1], G[i + 1]);
                    ll gthis = qsum[s[i]] & O.first;
                    if (gthis > best) {best = gthis, bestid = i;}
                }
                auto [o, l, r] = segs[bestid];
                pair<ll, ll> O;
                if (bestid == 0) O = G[bestid + 1]; else if (bestid == m - 1) O = F[bestid - 1]; 
                else O = combine(F[bestid - 1], G[bestid + 1]);
                ans = query(o, l, r, O.first);
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}