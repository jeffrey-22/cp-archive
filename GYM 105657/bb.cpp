#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
ll F = 9223372036854775807ll;
int n, q, op, l, r;
ll a[1000009], x;
int sz[4000009];
ll tag[4000009], sum[4000009], qsum[4000009];
void put(int o) {
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
    if (l <= ql && qr <= r) {
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
    int m = (l + r) >> 1;
    put(o);
    if (qr <= m) {findseg(o << 1, ql, qr, l, m, segs); return;}
    if (ql >= m + 1) {findseg(o << 1 | 1, ql, qr, m + 1, r, segs); return;}
    findseg(o << 1, ql, qr, l, m, segs);
    findseg(o << 1 | 1, ql, qr, m + 1, r, segs);
}
ll query(int o, int l, int r, ll nval = F) {
    if (l == r) return nval;
    int m = (l + r) >> 1;
    put(o);
    ll gl = qsum[o<<1] & sum[o<<1|1] & nval;
    ll gr = qsum[o<<1|1] & sum[o<<1] & nval;
    if (gl > gr)
        return query(o<<1, l, m, nval & sum[o<<1|1]);
    else
        return query(o<<1|1, m + 1, r, nval & sum[o<<1]);
}
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;
            for (int i = l ; i <= r; i ++)
                a[i]&= x;
        } else if (op == 2) {
            int pos;
            cin >> pos >> x;
            a[pos] = x;
        } else {
            cin >> l >> r;
            ll best = 0;
            for (int k = l; k <= r; k++) {
                ll cur = F;
                for (int i = l ;i <= r; i++)
                    if (i != k)
                        cur &= a[i];
                best = max(best, cur);
            }
            cout << best << endl;
        }
    }
    return 0;
}