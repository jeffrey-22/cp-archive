#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

struct SuffixArray {
    vi sa, lcp;
    SuffixArray(string s, int lim = 256) {
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
typedef RMQ<int> RMQI;
int n, q;
string str;
int li, ri;
int ql[200009], qr[200009];
int qx[200009], rk[200009];
int qf[200009], qfa[200009];
int len[200009];
int findf(int x) {
    return qfa[x] == x ? x : qfa[x] = findf(qfa[x]);
}
int findleft(int x, int vmin, RMQI& rmq) {
    int L = 0, R = x, M;
    while (L < R) {
        M = (L + R) >> 1;
        if (M == x || rmq.query(M, x) >= vmin)
            R = M;
        else
            L = M + 1;
    }
    return R;
}
int findright(int x, int vmin, RMQI& rmq) {
    int L = x, R = n - 1, M;
    while (L < R) {
        M = (L + R + 1) >> 1;
        if (M == x || rmq.query(x, M) >= vmin)
            L = M;
        else
            R = M - 1;
    }
    return L;
}
vector<ll> answers;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> str;
        n = sz(str);
        SuffixArray sa = SuffixArray(str);
        vector<int> shiftlcp(n - 1, 0);
        for (int i = 0; i < n - 1; i++) shiftlcp[i] = sa.lcp[i + 2];
        RMQI rmq(shiftlcp);
        for (int i = 1; i <= n; i++)
            rk[sa.sa[i]] = i - 1;
        cin >> q;
        for (int i = 0; i <= n; i++) qf[i] = 0, len[i] = n - 1 - sa.sa[i + 1] + 1;
        for (int i = 1; i <= q; i++) qfa[i] = i;
        answers.clear();
        set<int> added; added.clear();
        set<int> ready; ready.clear(); for (int i = 0; i < n; i++) ready.insert(i);
        ll curans = 0;
        // for (int i = 0; i < n; i++) cerr << rk[i] << " "; cerr << endl;
        for (int iq = 1; iq <= q; iq++) {
            cin >> li >> ri;
            qx[iq] = ri - li + 1;
            int midrk = rk[li - 1];
            // cerr << "word at " << li << " " << ri << " midrk = " << midrk << endl;
            int L = findleft(midrk, qx[iq], rmq);
            int R = findright(midrk, qx[iq], rmq);
            ql[iq] = L, qr[iq] = R;
            if (qf[L] && qx[findf(qf[L])] <= qx[iq]) {
                answers.push_back(curans);
                continue;
            }
            int p = L;
            // cerr << L << " -> " << R << endl;
            while (1) {
                if (p > R) break;
                auto itr = ready.lower_bound(p);
                auto ita = added.lower_bound(p);
                if (itr == ready.end() && ita == added.end()) break;
                int pn = 0;
                if (itr == ready.end())
                    pn = *ita;
                else if (ita == added.end())
                    pn = *itr;
                else
                    pn = min(*ita, *itr);
                if (pn > R) break;
                p = pn;
                if (qf[p]) {
                    int u = findf(qf[p]);
                    curans -= len[p] - qx[u] + 1;
                    if (p == L) {
                        curans += len[p] - qx[iq] + 1;
                    } else {
                        curans += len[p] - shiftlcp[p - 1];
                    }
                    // cerr << "upd at " << p << " og at query " << u << " curans now = " << curans<< endl;
                    qfa[u] = iq;
                    added.erase(p);
                } else {
                    ready.erase(p);
                    qf[p] = iq;
                    if (p == L) {
                        curans += len[p] - qx[iq] + 1;
                    } else {
                        curans += len[p] - shiftlcp[p - 1];
                    }
                    // cerr << "add at " << p << " curans now = " << curans << endl;
                }
                p++;
            }
            added.insert(L);
            answers.push_back(curans);
        }
        for (auto t : answers) cout << t << " "; cout << endl;
    }
}