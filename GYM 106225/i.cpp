#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
void test() {
  double ans = 0;
  for (int i = 100; i >= 1; i--) {
    double sum = (101. - i) / i;
    cout << "len: " << i << ": " << sum << " | prefix: " << ans << "\n";
    ans += sum;
  }
  cout << "sum: " << ans << endl;
  ans = 0;
  for (int i = 100; i >= 1; i--) {
    ans += 1. / i;
  }
  cout << ans << endl;
}
void work() {
  double sum = 0;
  int n;
  cin >> n;
 
  // vector<int> a(n + 1);
  // mt19937 rnd(114514);
  // for (int i = 1; i <= n; i++) {
  //   a[i] = rnd() % (1 << 30);
  // }
  auto qry = [&](int l, int r) {
    sum += 1. / (r - l + 1);
 
    // int res = 0;
    // for (int i = l; i <= r; i++) {
    //   res ^= a[i];
    // }
    // int ans = -1;
    // while (res) {
    //   ans++;
    //   res /= 2;
    // }
    // return ans;
 
    cout << "? " << l << ' ' << r << endl;
    int x;
    cin >> x;
    return x;
  };
 
  vector<vector<int>> vis(n + 1, vector<int>(n + 1, 0));
  vector<vector<int>> ans(n + 1, vector<int>(n + 1, -1));
  auto dfs = [&](auto &self, int l, int r, int val) -> void {
    if (vis[l][r]) {
      return;
    }
    vis[l][r] = 1;
    ans[l][r] = val;
    for (int i = 1; i <= n; i++) {
      if (i < l && vis[i][r] && ans[i][r] != ans[l][r]) {
        self(self, i, l - 1, max(ans[i][r], ans[l][r]));
      }
      if (i > r && vis[l][i] && ans[l][i] != ans[l][r]) {
        self(self, r + 1, i, max(ans[l][i], ans[l][r]));
      }
      if (l <= i && i < r && vis[l][i] && ans[l][i] != ans[l][r]) {
        self(self, i + 1, r, max(ans[l][i], ans[l][r]));
      }
      if (l <= i && i < r && vis[i + 1][r] && ans[i + 1][r] != ans[l][r]) {
        self(self, l, i, max(ans[i + 1][r], ans[l][r]));
      }
    }
  };
  for (int i = n; i >= 1; i--) {
    for (int j = 1; i + j - 1 <= n; j++) {
      int l = j, r = i + j - 1;
      if (!vis[l][r]) {
        dfs(dfs, l, r, qry(l, r));
      }
    }
  }
  cout << "!\n";
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      cout << ans[i][j] << " \n"[j == n];
    }
  }
  fflush(stdout);
  // cerr << sum << endl;
}
 
signed main() {
	ios :: sync_with_stdio(false), cin.tie(0);
	cout.precision(10), cout.setf(ios :: fixed);
	
  // test();
  int T = 1;
  cin >> T;
  while (T--) {
    work();
  }
	
	return 0;
}