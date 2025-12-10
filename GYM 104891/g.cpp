#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, t;
int a[509];
void update() {
    cout.flush();
    int x; string op;
    cin >> x >> op;
    if (op[0] == '+')
        a[x] ^= a[x + 1];
    else
        a[x] &= a[x + 1];
    for (int i =x + 1; i < n; i++)
        a[i] = a[i + 1];
    n--;
}
void solve1() {
    cout << "Alice" << endl;
    while (1) {
        if (n % 2 == 0) {

        } else {
            update();
        }
    }
}
void solve2() {

}
void solve3() {

}
void solve4() {

}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int cnte = 0;
    for (int i = 1; i <= n; i++) {
        if (i == n || a[i] != a[i + 1]) {
            if (a[i] != 1) continue;
            int last = i;
            for (int j = i; j >= 1; j--)
                if (a[j] != a[i]) {
                    break;
                } else 
                    last = j;
            int cnt = i - last + 1;
            cnte += (cnt + 1) / 2;
        }
    }
    if (t == 0 && n % 2 == 0)
        solve1();
    else if (t == 1 && n % 2 == 1)
        solve2();
    else if (t == 0 && n % 2 == 1)
        solve3();
    else
        solve4();
}