#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
vector<vector<pair<int, int>>> roundops;
int totallen = 0, failed = 0;
void addact(int roundid, int x, int l) {
    // at round roundid, add l to x
    if (l == 0) return;
    totallen += l;
    roundops[roundid].push_back({x, l});
}
int intpow(int x, int y) {
    int r = 1;
    while (y--) r *= x;
    return r;
}
// block of k is of size 2^k, guarantees putting everything at the end
void addblock(int start, int end, int k) {
    if (start >= end) return;
    int sz = end - start + 1;
    if (k + 1 >= sz) {
        for (int i = 1; i <= sz - 1; i++)
            addact(i, start + i - 1, 1);
        return;
    }
    if (k <= 1) {failed = 1; return;}
    int curend = end - 1;
    int curstart;
    int cursize = 0;
    int finished = 0;
    for (int t = 1; 1 ; t++) {
        cursize = 1;
        if (k >= 80)
            cursize = intpow(70, t);
        else if (k >= 50)
            cursize = intpow(65, t);
        else if (k >= 35)
            cursize = intpow(30, t);
        else 
            cursize = intpow(10, t);
        cursize = max(cursize, 1);
        curstart = curend - cursize + 1;
        if (curstart <= start) {curstart = start; finished = 1;}
        addblock(curstart, curend, k - 1);
        addact(k, curend, end - curend);
        curend = curstart - 1;
        if (finished) break;
    }
}
int checks[250009];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int K = 130;
    roundops = vector<vector<pair<int, int>>>(K + 1, vector<pair<int, int>>());
    addblock(1, 250000, K);
    // cout << totallen + K * 1000 << endl;
    // cout << failed << endl;
    int totops = 0;
    for (int t = 1; t <= K; t++) {sort(all(roundops[t])); reverse(all(roundops[t])); totops += sz(roundops[t]);}
    printf("%d\n", totops);
    for (int i = 1; i < 250000; i++) checks[i] = 1;
    for (int t = 1; t <= K; t++) {
        for (auto [x, y] : roundops[t]) {
            printf("%d %d\n", x, y);
            // if (x + y < 250000) checks[x + y] += checks[x], checks[x] = 0; else checks[x] = 0;
        }
    }
    // for (int i = 1; i < 250000; i++) if (checks[i] != 0) cerr << i << endl;
}

/*

[1, n]
each block:
smaller (earlier) block uses less rounds
block k with size s, allowed to do k rounds
c(k) = c(k - 1) + c(k - 2) + ... + c(1) + 2^k
s(k) = s(k - 1) + s(k - 1)
c(k) = 4 * 2^k
s(k) = 2^k
c(k) = 2c(k-1) + 2^(k-1) = 2(2c(k-2) + 2^(k-2))

s(0) = 1
s(1) = 2
s(2) = 3
s(3) = 6
s(4) = 12
s(5) = 24
c(5) = c(0) + ... + c(4) + 22
+blksz at final round

2^1 * k + 2^2 * (k-1) + 2^k * 1
*/