#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    int n;
    cin >> n;
    vector<pair<string, int>> a;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        a.emplace_back(s, i);
        reverse(s.begin(), s.end());
        a.emplace_back(s, i);
    }
    sort(a.begin(), a.end());
    vector<int> cnt(n), ans1(n, n), ans2(n, 0);
    int sum1 = 0, sum2 = 0;
    for (auto [x, i] : a) {
        ans1[i] = min(ans1[i], sum1);
        ans2[i] = max(ans2[i], sum2 - 1);
        cnt[i]++;
        if (cnt[i] == 1) {
            sum2++;
        } else if (cnt[i] == 2) {
            sum1++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans1[i] << ' ' << ans2[i] << "\n";
    }

    return 0;
}