#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, k;
int p[100009];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int T = 5;
    n = 100000; k = 1;
    cout << T << endl;
    while (T--) {
        cout << n << " " << k << "\n";
        for (int i = 1; i <= n; i++)
            p[i] = i;
        for (int i = 2; i <= n; i++)
            swap(p[i], p[(rand() ^ (rand() << 13) )% (i - 1) + 1]);
        for (int i = 1; i <= n; i++) cout << p[i] << " "; cout << "\n";
    }
}