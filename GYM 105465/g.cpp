#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 5;
const ll inf = 1e18;

int n, m, a[N], b[N], dis[N];
ll val[N][2], ans[N];
vector<int> e[N], d[N];
void bfs(int S) {
  memset(dis, -1, sizeof(dis));
  queue<int> q;
  q.emplace(S);
  dis[S] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : e[u]) {
      if (dis[v] < 0) {
        dis[v] = dis[u] + 1;
        q.emplace(v);
      }
    }
  }
}
void work() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    e[u].emplace_back(v);
    e[v].emplace_back(u);
  }
  bfs(1);
  ll mx[3] = {-inf, -inf, -inf};
  for (int i = 1; i <= n; i++) {
    mx[2] = a[i] - 1LL * (dis[i] + 1) * b[i];
    sort(mx, mx + 3, greater<ll>());
    d[dis[i]].emplace_back(i);
  }
  for (int i = n; i >= 0; i--) {
    for (int u : d[i]) {
      for (int j = 0; j <= 1; j++) {
        val[u][j] = a[u] - 1LL * (dis[u] - j) * b[u];
        for (int v : e[u]) {
          if (dis[v] == dis[u] + 1) {
            val[u][j] = max(val[u][j], val[v][j]);
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans[i] = -inf;
  }
  for (int u : e[1]) {
    ll now = -inf;
    if (a[u] - 1LL * (dis[u] + 1) * b[u] == mx[0]) {
      now = mx[1];
    } else {
      now = mx[0];
    }
    for (int v : e[u]) {
      if (dis[v] - dis[u] == 0) {
        now = max(now, val[v][0]);
      }
      if (dis[v] - dis[u] == 1) {
        now = max(now, val[v][1]);
      }
    }
    ans[u] = now;
  }
  for (int i = 1; i <= n; i++) {
    if (ans[i] != -inf) {
      cout << ans[i] << "\n";
    }
  }
}

signed main() {
	ios :: sync_with_stdio(false), cin.tie(0);
	cout.precision(10), cout.setf(ios :: fixed);
	
  int T = 1;
//  cin >> T;
  while (T--) {
    work();
  }
	
	return 0;
}