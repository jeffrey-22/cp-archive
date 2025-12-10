#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, m;
double sum = 0;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    scanf("%d%d",&n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int x; scanf("%d",&x);
            sum += x;
        }
    sum /= (1.0 * n * m);
    cout << fixed << setprecision(10);
    cout << sum << endl;
}