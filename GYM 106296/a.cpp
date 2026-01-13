#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int(x).size())
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int N = 20;
void write() {
    int idx;
    int C[N + 1];
    cin >> idx; for (int i = 1; i <= N; i++) cin >> C[i];
    C[idx] = 0;
    int sum = 0;
    for (int i = 1; i <= N; i++)
        sum ^= C[i];
    int t = idx - 1;
    int val = 1 << t;
    int wrt = 0;
    if (sum & val) wrt = 1;
    if (idx == N) {
        int tot = 0;
        for (int d = 0; d <= N; d++)
            if (sum & (1 << d))
                tot ^= 1;
        wrt = tot;
    }
    cout << wrt << endl;
    fflush(stdout);
}
void answer() {
    int idx;
    int C[N + 1];
    string A;
    cin >> idx; for (int i = 1; i <= N; i++) cin >> C[i];
    C[idx] = 0;
    cin >> A;
    int sum = 0;
    for (int i = 1; i <= N; i++)
        sum ^= C[i];
    // real sum = sum ^ C[idx] = sq
    // know sq ^ C[i]
    // real sum (sq) = 0
    // for idx 1: sqc = 1
    // chr(t) = sq ^ C[t], except i=idx: sqc
    // find out sum ^ ?
    int sumq = 0;
    for (int i = 1; i <= N - 1; i++) {
        if (i == idx) continue;
        int chr = (A[i - 1] == '1') ? 1 : 0;
        int val = 1 << (i - 1);
        int sqcd = chr;
        int cd = (C[i] & val) >> (i - 1);
        int sqd = sqcd ^ cd;
        sumq |= sqd << (i - 1);
    }
    int q = sumq ^ sum;
    if (idx < N) {
        int chrn = (A[N - 1] == '1') ? 1 : 0;
        int tot = 0;
        for (int d = 0; d <= N; d++)
            if (C[N] & (1 << d))
                tot ^= 1;
        for (int d = 0; d <= N; d++)
            if (sumq & (1 << d))
                tot ^= 1;
        // cout << idx << ": " << sumq << " " << sum << " " << q << " " << tot << " " << chrn << endl;
        if (tot != chrn) q ^= (1 << (idx - 1));
    }

    cout << q << endl;

    fflush(stdout);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int T, K;
    // T = K = N;
    cin >> T;
    while (T--)
        write();
    cin >> K;
    while (K--)
        answer();
}
/*
2 3 3

3
1 0 3 3
2 2 0 3
3 2 3 0

3
1 0 3 3 001
2 2 0 3 001
3 2 3 0 001

*/