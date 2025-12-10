#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int gcd(int x, int y) {
    return !y ? x : gcd(y, x % y);
}
int A, B, x, y;
vector<tuple<int, int, int, int>> ans;
void get(int x, int y) {
    if ((x == 0 || x == A) && (y == 0 || y == B)) {
        return;
    }
    int lx, rx, ly, ry;
    if (x <= A / 2) {
        lx = 0, rx = x * 2;
    } else {
        lx = A, rx = x * 2 - A;
    }
    if (y <= B / 2) {
        ly = 0, ry = y * 2;
    } else {
        ly = B, ry = y * 2 - B;
    }
    get(rx, ry);
    ans.emplace_back(lx, ly, rx, ry);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    
    cin >> A >> B >> x >> y;
    int g = gcd(x, A), nA = A, nB = B;
    if (g) {
        nA /= g;
    }
    g = gcd(y, B);
    if (g) {
        nB /= g;
    }
    if (__builtin_popcount(nA) > 1 || __builtin_popcount(nB) > 1) {
        cout << "-1\n";
        return 0;
    }
    get(x, y);
    cout << ans.size() << "\n";
    for (auto [x, y, u, v] : ans) {
        cout << x << ' ' << y << ' ' << u << ' ' << v << "\n";
    }

    return 0;
}