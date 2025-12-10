#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int lim = 1 << 10;
int n, k;
vector<int> dice[109];
int totLB[1029];
pair<int, int> hasOptionsWithAtLeast[1029][19];
vector<int> curAns, bestAns;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6; j++) {
            int val; cin >> val;
            dice[i].push_back(val);
        }
    }
    for (int w = 0; w < lim; w++) {
        totLB[w] = 1;
        totW[w] = 0;
        for (int i = 1; i <= n; i++) {
            int isDiceOK = 0;
            for (auto val : dice[i])
                if (w & (1 << val)) {
                    isDiceOK = 1;
                    break;
                }
            if (isDiceOK) totLB[w]++;
        }
    }
    for (int w = 0; w < lim; w++) {
        for (int j = 0; j <= 10; j++) {
            hasOptionsWithAtLeast[w][j] = {0, 0};
            for (int k = j; k <= 9; k++)
                if (w & (1 << k)) {
                    hasOptionsWithAtLeast[w][j] = {1, k};
                    break;
                }
        }
    }
    curAns.clear(); for (int w = 0; w < lim; w++) digits[w].clear();
    curAns.push_back(0);
    for (int i = 1; i <= k; i++) {
        bestAns.clear(); bestAns.push_back(0);
        for (int w = 1; w < lim; w++) {
            int p = 0;
            int totW = 0;
            for (auto v : curAns)
                if ((1 << v) & w)
                    totW++;
            if ((1 << curAns[p]) & w)
                totW--;
            while (p < sz(curAns) && (p + hasOptionsWithAtLeast[w][p].first + totW)) {
                p++;
                if (p < sz(curAns) && ((1 << curAns[p]) & w))
                    totW--;
            }
        }
    }
}