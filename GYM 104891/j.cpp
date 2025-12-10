#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int inf = 1e9;
int n, x;
int a[200009];
int dis[200009];
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;
vector<pair<int, int>> e[200009]; // to, sz
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> x;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n * 2; i++)
        dis[i] = inf;
    for (int i = 0; i < n; i++)
        e[i + n].push_back({i, 0});
    for (int i = 0; i < n; i++)
        e[i + n].push_back({(i + 1) % n + n, 1});
    for (int i = 0; i < n; i++)
        e[i].push_back({(i + a[i]) % n + n, 1});
    pq.push({0, 0});
    dis[0] = 0;
    while (!pq.empty()) {
        auto [dis_u, u] = pq.top();
        int D = dis_u;
        pq.pop();
        if (dis[u] < dis_u) continue;
        for (auto [v, e_b] : e[u]) {
            int n_b = D + e_b;
            if (n_b < dis[v]) {
                // cerr << u << ">" << v << " " << D << endl;
                dis[v] = n_b;
                pq.push({n_b, v});
            }
        }
    }
    auto A = dis[x];
    cout << A << endl;
}