#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, l, k;
string name[10009];
int a[10009][109], bo[10009], md[10009];
int D(int x, int y) {
    int r = 0;
    for (int i = 1; i <= l; i++)
        r += abs(a[x][i] - a[y][i]);
    return r;
}
int f(int x, int upd = 1) {
    int best = -1, bestx = 0;
    for (int i = 1; i <= n; i++)
        if (!bo[i]) {
            int dist = D(i, x);
            if (upd)
                md[i] = min(md[i], dist);
            if (upd) {

                if (md[i] > best) {
                    best = md[i];
                    bestx = i;
                }
            } else {

                if (dist > best) {
                    best = dist;
                    bestx = i;
                }
            }
        }
    return bestx;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    scanf("%d%d%d", &n, &l, &k);
    for (int i = 1; i <= n; i++) {
        char tmp[21];
        scanf("%20s", tmp);
        name[i] = tmp;
        for (int j = 1; j <= l; j++)
            scanf("%d", &a[i][j]);
    }
    int p1 = f(1, 0);
    bo[p1] = 1;
    vector<int> P = {}; P.push_back(p1);
    for (int i = 1; i <= n; i++) md[i] = 1000;
    for (int i = 2; i <= k; i++) {
        int p2 = f(p1, 1);
        bo[p2] = i;
        P.push_back(p2);
        p1 = p2;
    }
    for (auto t : P)
        cout << name[t] << endl;
}