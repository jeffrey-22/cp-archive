#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;

int n, m;
vector<int>e[N];
void work(vector<int>a, int f) {
    for (int i = 0; i < n; i++) {
        a[i] *= f;
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = n - 1; i >= 0; i--) {
        while (!q.empty() && q.top() < a[i]) {
            m++;
            e[a[i] * f].emplace_back(q.top() * f);
            q.pop();
        }
        q.emplace(a[i]);
    }
}
vector<int>get(int f) {
    vector<int>deg(n + 1);
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; i++) {
        for (int j : e[i]) {
            deg[j]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!deg[i]) {
            q.emplace(i * f);
        }
    }
    vector<int> res;
    while (!q.empty()) {
        int u = q.top() * f;
        q.pop();
        res.emplace_back(u);
        for (int v : e[u]) {
            if (!--deg[v]) {
                q.emplace(v * f);
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n;
    vector<int> mn(n), mx(n);
    for (int i = 0; i < n; i++) {
        cin >> mn[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> mx[i];
    }
    work(mn, 1);
    work(mx, -1);
    if (get(1) != mn || get(-1) != mx) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    cout << m << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j : e[i]) {
            cout << i << " " << j << "\n";
        }
    }

    return 0;
}