#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        int n;
        cin >> n;
        vi a(109, 0);
        for (int i = 1; i <= n; i++) cin >> a[i];
        int hasDec = 0, k;
        for (int i = 2; i <= n; i++)
            if (a[i] <= a[i - 1]) {
                // decrease
                hasDec = 1;
                int x = a[i] - 1;
                k = a[i - 1] / x;
            }
        if (!hasDec) {
            k = max(a[2] - a[1], a[n] / (a[2] - a[1]));
        }
        cout << k << endl;
    }
}

/*
inc (dec or =)

for any inc: find dif = row no., 
if has [inc -> dec], rk -> (r+1), can calc k
only has dec -> inc, (r-1)k -> r, can calc k
only has inc -> max(row, final num / row)
only has dec -> n = 2, xk -> x+1
*/