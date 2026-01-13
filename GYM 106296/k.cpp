#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int(x).size())
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int ask(int x) {
    cout << "? " << x << endl;
    // fflush(cout);
    int v;
    cin >> v;
    return v;
}
int n;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    if (n >= 3)
        cout << "! " << 1 << endl;
    else {
        vector<int> a(n + 1, 0);
        for (int i = 1; i <= n; i++)
            a[i] = ask(i);
        int ok = 0;
        for (int l = 1; l <= n; l++)
            for (int r = l; r <= n; r++) {
                int t = 0;
                for (int i = l; i <= r; i++)
                    t = t * 10 + a[i];
                if (t % 3 == 0) {
                    ok = 1;
                }
            }
        cout << "! " << ok << endl;
    }
}