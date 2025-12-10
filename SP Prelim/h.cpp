#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int L;
int ax, ay, bx, by, f;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> L;
    string s;
    cin >> s;
    ax = 0, ay = 0;
    bx = 1, by = 0;
    f = 0;
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == 'B') {
            swap(ax, bx);
            swap(ay, by);
            f ^= 1;
        } else {
            if (ay == by) {
                if (ax < bx) {
                    ax += 1;
                    ay += 1;
                } else {
                    ax -= 1;
                    ay -= 1;
                }
            }
            else {
                if (ay > by) {
                    ax += 1,
                    ay -= 1;
                } else {
                    ax -= 1;
                    ay += 1;
                }
            }
        }
    }
    if (f)  {
        swap(ax, bx);
        swap(ay, by);
        f ^= 1;
    }
    cout << ax << " " << ay << endl;
}