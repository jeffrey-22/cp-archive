#include <bits/stdc++.h>
#define ll long long
#define double long double
using namespace std;
const int N = 505;
const int NN = N + N;
const double inf = 1e18;

struct point {
	ll x, y;
	point operator - (const point &a) const {
		return (point){x - a.x, y - a.y};
	}
	double length() {
		return sqrt(x * x + y * y);
	}
	ll operator * (const point &a) const {
		return x * a.y - a.x * y;
	}
}a[NN], A, B;
int n;
double f[NN][NN][3];
int calc_sign(point a, point b, point c) {
	ll tmp = (c - a) * (c - b);
	if (tmp == 0) {
		return 0;
	}
	if (tmp > 0) {
		return 1;
	}
	if (tmp < 0) {
		return -1;
	}
	return 0;
}
int check(point A, point B, point a, point b) {
	int x = calc_sign(A, a, b); 
	int y = calc_sign(B, a, b);
	if (x == 0 || y == 0) {
		return -1;
	}
	return x != y;
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cout.precision(10), cout.setf(ios :: fixed);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y;
		a[i + n] = a[i];
	}
	cin >> A.x >> A.y;
	cin >> B.x >> B.y;
	double ans = inf;
	for (int i = 2; i <= 3; i++) {
		for (int j = 1; j + i - 1 <= n + n; j++) {
			int l = j, r = j + i - 1;
			for (int p = 1; p <= 2; p++) {
				f[l][r][p] = inf;
			}
		}
	}
	for (int i = 4; i <= n; i++) {
		for (int j = 1; j + i - 1 <= n + n; j++) {
			int l = j, r = j + i - 1;
			for (int p = 0; p <= 2; p++) {
				f[l][r][p] = inf;
			}
			for (int k = l + 1; k < r; k++) {
				for (int p = 0; p <= 2; p++) {
					if (f[l][k][p] > inf / 2) {
						continue;
					}
					int t = p;
					t += check(A, B, a[l], a[k]);
					if (t > 2 || check(A, B, a[l], a[k]) == -1) {
						continue;
					}
					double ans = f[l][k][p];
					if (k > l + 1) {
						ans += (a[l] - a[k]).length();
					}
					int tt = t;
					double tans = ans;
					for (int q = 0; tt + q <= 2; q++) {
						if (f[k][r][q] > inf / 2) {
							continue;
						}
						ans = tans;
						t = tt;
						t += q;
						t += check(A, B, a[r], a[k]);
						if (t > 2 || check(A, B, a[r], a[k]) == -1) {
							continue;
						}
						ans += f[k][r][q];
						if (k < r - 1) {
							ans += (a[r] - a[k]).length();
						}
						f[l][r][t] = min(f[l][r][t], ans);
					}
				}
			}
//			for (int p = 0; p <= 2; p++) {
//				cerr << l << ' ' << r << ',' << p << ':' << f[l][r][p] << endl;
//			} 
			if (i == n) {
				ans = min(ans, f[l][r][2]);
			}
		}
	}
	if (ans < inf / 2) {
		cout << ans << "\n";
	} else {
		cout << "IMPOSSIBLE\n";
	}

	return 0;
}
/*
6
0 -50
-30 0
0 50
90 50
120 0
90 -50

0 40
90 -20

should be 410.000000

*/
