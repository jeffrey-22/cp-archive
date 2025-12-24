#include <bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;

void work() {
  int n, last = 0;
  cin >> n;
  vector<int> a(n), c(n);
  int max1 = 0, max0 = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i + 1 < n; i++) {
    c[i] = a[i] - last;
    last = c[i];
    if (i & 1) {
      max1 = max(max1, c[i]);
    } else {
      max0 = max(max0, c[i]);
    }
  }
  int ans = 0;
  if (n & 1) {
    int b0 = (a[n - 1] - c[n - 2]) / 2, mx = b0, sum = b0;
    for (int i = 0; i + 1 < n; i++) {
      if (i & 1) {
        c[i] += b0;
      } else {
        c[i] -= b0;
      }
      mx = max(mx, c[i]);
      sum += c[i];
    }
    ans = max(mx, (sum + n - 2) / (n - 1));
  } else {
    int mx = max(max0, max1), sum = 0;
    if (max0 > max1) {
      mx = min(mx, (max0 + max1 + 1) / 2);
    }
    for (int i = 0; i + 1 < n; i++) {
      sum += c[i];
    }
    ans = max(mx, (sum + n - 2) / (n - 1));
  }
  cout << ans << endl;
}

signed main() {
	ios :: sync_with_stdio(false), cin.tie(0);
	cout.precision(10), cout.setf(ios :: fixed);
	
  int T = 1;
  cin >> T;
  while (T--) {
    work();
  }
	
	return 0;
}
/*
n = 2: [v, v]
n = 3:
[011]/[112], cycled
1 2 3 [101]
1 3 2 [112]
2 1 3 [211]
2 3 1 [011]
3 1 2 [110]
3 2 1 [121]
b[i] = a[i] - a[i - 1]
[-1 +1 0]
[-1 0 +1]
[1210]
[+1 +1 -1 -1]

0 0 0 1 1 1 1 1 1 0 0 0

can facilitate any pairs of +1, except all +2`

for G: answer (guess) = take max of:
ceiling[sum / (2n - 2)]
ceiling[max (a) / 2]
max (difference array)
1 3 -5 7 4 -10


4 4 4 0 4 4 4 0
2 1 1
1 2 1
1 1 2

at n, perform v operations
a1 - v, a2, a3, ... , an-1, an - v
a1: perf a1 - v
0, a2 - a1 + v, a3, ..., an-1, an - v
a2: perf a2 - a1 + v
0, 0, a3 - a2 + a1 - v
ai: perf ai - a(i-1) + a(i-2) +... +/- v

e.g. 2 2 2
2-v, 2, 2
perf 2-v
perf v
perf 
an - a(n-1) + a(n-2) + ... +/- v = 0
10 10 5 : takes 15 rounds
n even:

*/