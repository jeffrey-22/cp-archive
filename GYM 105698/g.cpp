#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, q;
int s[2000009], a[500009];
void push(int o) {
    s[o] = min(s[o<<1], s[o<<1|1]);
}
void modify(int pos, int value, int l=1, int r=n, int o=1) {
    if (l == r) {
        s[o] = max(s[o], value);
        a[l] = 1;
        return;
    }
    int m = (l + r) >> 1;
    if (pos <= m) modify(pos, value, l, m, o<<1); else modify(pos, value, m + 1, r, o<<1|1);
    push(o);
}
void query(int qr, int& res, int& acc, int l=1, int r=n, int o=1) {
    if (l > qr) return;
    if (r < 1) {res = 0; return;}
    if (1 <= l && r <= qr && min(acc, s[o]) >= qr) {
        acc = min(acc, s[o]);
        return;
    }
    // cout << "searching " << l << " " << r << endl;
    // cout << "acc = " << acc << endl;
    if (l == r) {res = l; return;}
    int m = (l + r) >> 1;
    query(qr, res, acc, m + 1, r, o<<1|1);
    if (res != -1) return;
    query(qr, res, acc, l, m, o<<1);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            cin >> l >> r;
            modify(l, r);
        } else {
            int x; cin >> x;
            if (!a[x]) {
                cout << 1 << endl;
                continue;
            }
            int res = -1;
            int acc = n + 1;
            query(x, res, acc);
            if (res == -1) res = 0;
            res++;
            cout << x - res + 2 << endl;
        }
    }
    return 0;
}