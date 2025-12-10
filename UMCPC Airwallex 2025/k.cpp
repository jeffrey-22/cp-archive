#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size() 
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> pii; 
typedef vector<int> vi;

template<class T>
struct RMQ {
vector<vector<T>> jmp;
RMQ(const vector<T>& V) : jmp(1, V) {
for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
    jmp.emplace_back(sz(V) - pw * 2 + 1);
    rep(j,0,sz(jmp[k]))
    jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
    }
    T query(int a, int b) {
    b++;
    assert(a < b); // or return in f i f a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
    
int n;
int a[100009], nxt[100009];
set<pair<int, int>> S[2];
int check() {
    if (S[0].empty() || S[1].empty())
        return 1;
    auto it = S[0].begin();
    int l0 = it -> first;
    it = S[0].end(); it--;
    int r0 = it -> first;

    it = S[1].begin();
    int l1 = it -> first;
    it = S[1].end(); it--;
    int r1 = it -> first;
    if (r0 < l1 || r1 < l0)
        return 1;
    return 0;
}
void add(int x) {
    S[x & 1].insert({a[x], x});
}
void remove(int x) {
    S[x & 1].erase({a[x], x});
}
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        int q;
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        S[0].clear(); S[1].clear();
        int r = 0;
        for (int l = 1; l <= n; l++) {
            if (l > 1)
                remove(l - 1);
            while (r < n) {
                r++;
                add(r);
                if (!check()) {r--; break;}
            }
            nxt[l] = r;
        }
        vector<int> fnxt = {};
        for (int i = 1; i <= n; i++) {
            fnxt.pb(-(nxt[i] - i + 1));
        }
        RMQ frmq(fnxt);
        for (int i = 1; i <= q; i++) {
            int ql, qr;
            cin >> ql >> qr;
            int sl = ql, mid, sr = qr, pivot;
            // ql - pivot <=; pivot + 1 - qr >
            while (sl < sr) {
                mid = (sl + sr + 1) >> 1;
                if (nxt[mid] <= qr)
                    sl = mid;
                else
                    sr = mid - 1;
            }
            pivot = sl;
            if (nxt[pivot] > qr)
                pivot--;
            int ans1 = 0, ans2 = 0;
            if (ql <= pivot) {
                ans1 = -frmq.query(ql-1, pivot-1);
            }
            if (pivot + 1 <= qr) {
                ans2 = qr - (pivot + 1) + 1;
            }
            cout << max(ans1, ans2) << endl;
        }
    }

    return 0;
}