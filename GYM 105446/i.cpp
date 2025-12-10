#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cout << "1 1 3 4" << endl;
    }
    int a = m - n + 2;
    int b = m - 4 * (n - 1);
    int x = (a + b - 1) / b;
    cout << x << " " << m - n + 1 << " " << 1 << " " << m - 4 * (n - 1) << endl;
}