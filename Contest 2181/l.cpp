#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int tottoken;
map<string, int> tokenmp;
int n, m, maxm, k;
vector<int> s, kid;
vi sa, lcp;
struct SuffixArray {
    vi sa, lcp;
    SuffixArray(vi s, int lim=600009) {
        s.push_back(0); int n = sz(s), k = 0, a, b;
        vi x(all(s)), y(n), ws(max(n, lim));
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i, 0, n) ws[x[i]]++;
            rep(i, 1, lim) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = 
                (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
            for (k && k--, j = sa[x[i] - 1]; s[i + k] == s[j + k]; k++);
    }
};
template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T> &V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
RMQ lcprmq = RMQ({1});
vector<vector<int>> enxt = {};
vector<int> lcplen = {};
vector<int> leafval = {};
int totnode = 0;
int getmin(int l, int r) {
    if (l == r) {
        return m - 1 - sa[l] + 1;
    }
    return lcprmq.query(l + 1, r + 1);
}
pair<int, int> findnxt(int lcplim, int l) {
    int L = l, R = m - 1;
    while (L < R) {
        int mid = (L + R + 1) >> 1;
        if (getmin(l, mid) >= lcplim)
            L = mid;
        else
            R = mid - 1;
    }
    return {getmin(l, L), L};
}
void addrange(int l, int r, int curlcp) {
    if (l == r) {
        totnode++;
        lcplen.push_back(curlcp);
        enxt.push_back({});
        leafval.push_back(sa[l] - 1 >= 0 ? s[sa[l] - 1] : -1);
        return;
    }
    totnode++;
    lcplen.push_back(curlcp);
    leafval.push_back(0);
    vector<int> sons = {};
    int pl = l; int pr;
    while (pl <= r) {
        auto [nxtlcp, pr] = findnxt(curlcp + 1, pl);
        sons.push_back(totnode);
        addrange(pl, pr, nxtlcp);
    }
    enxt.push_back(sons);
}
vector<int>* A; // subtree all vals
void additem(int val) {

}
void removeitem(int val) {

}
void calccontr(int t) {
    
}
vector<int> tsz;
void dfscalcsz(int t) {
    tsz[t] = 1;
    for (auto v : enxt[t]) {
        dfscalsz(v);
        tsz[t] += tsz[v];
    }
}
void dfs(int t, int keep = 0) {
    if (enxt[t].empty()) { // leaf
        A[t] = new vector<int>();
        if (keep && leafval[t] != -1) {
            additem(leafval[t]);
            A[t]->push_back(leafval[t]);
        }
        return;
    }
    int bigChild = -1, mxSz = 0;
    if (bigChild == -1)
    for (auto v : enxt[t]) {
        if (tsz[v] > mxSz) {
            mxSz = tsz[v];
            bigChild = v;
        }
    }
    // merge from children
    for (auto v : enxt[t]) 
        if (v != bigChild)
            dfs(v, 0);
    dfs(bigChild, 1);
    A[t] = A[bigChild];
    for (auto v : enxt[t])
        if (v != bigChild) {
            for (auto x : A[v]) {
                additem(x);
                A[t]->push_back(x);
            }
        }
    calccontr(t);
    if (!keep) {
        for (auto val : A[t])
            removeitem(val);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m; maxm = max(maxm, m);
        vector<int> tokarr = {}, statusarr = {};
        for (int j = 1; j <= m; j++) {
            string token;
            cin >> token;
            if (!tokenmp.count(token)) tokenmp[token] = ++tottoken;
            tokarr.push_back(tokenmp[token]);
        }
        string statusstr; cin >> statusstr;
        for (int j = 0; j < m; j++) if (statusstr[j] == 'U') statusarr.push_back(0); else statusarr.push_back(1);
        for (int j = m - 1; j >= 0; j--) {
            s.push_back(tokarr[j]);
            if (statusarr[j] == 1) kid.push_back(sz(s) - 1);
        }
        s.push_back(++tottoken);
    }
    k = sz(kid); m = sz(s);
    SuffixArray SA = SuffixArray(s);
    sa = SA.sa;
    lcp = SA.lcp;
    lcprmq = RMQ(lcp);
    solve(0, m - 1, 0);
    tsz = vi(totnode, 0);
    dfscalcsz(0);
    dfs(0);
}
/*
For each
  unique substring, calc entropy of (first letter)
1. calc k = 0
2. calc k = 1
3. for k > 1, calc updates as suffix

caaa
caaaa
caaaaaaaaaaaab
caaaaaaaaaabb
caaaaaac
caabbbb
cb

caaxxxx



x, caab
x, cab
y, cac
x, cbc
y, ccc

x, c
x, c
y, c
x, c
y, c // [3, 2]

x, ca
x, ca
y, ca
x, cb
y, cc // [2, 1] + [[1, 0] + [0, 1]]

x, caa
x, cab
y, cac
x, cbc
y, ccc // [1] + [1] + [1] + [1] + [1]



*/