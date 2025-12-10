#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e3 + 5;

int n, sum[2][N], a[N][N], ans[N][N];

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            if (s[j - 1] == '-') {
                sum[0][i]--;
                sum[1][j]--;
                a[i][j] = 1;
            }
        }
    }
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            sum[i][j] = x - sum[i][j];
            if (sum[i][j] > n) {
                cout << "No\n";
                return 0;
            }
        }
    }
    vector<pair<int, int>> v;
    for (int i = 1; i <= n; i++) {
        v.emplace_back(sum[0][i], i);
    }
    for (int i = 1; i <= n; i++) {
        sort(v.begin(), v.end(), greater<pair<int, int>>());
        for (int j = 0; j < sum[1][i]; j++) {
            if (v[j].first == 0) {
                cout << "No\n";
                return 0;
            }
            v[j].first--;
            ans[v[j].second][i] = 1;
        }
    }
    sort(v.begin(), v.end(), greater<pair<int, int>>());
    if (v[0].first > 0) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << (a[i][j] ^ ans[i][j]);
        }
        cout << "\n";
    }

    return 0;
}