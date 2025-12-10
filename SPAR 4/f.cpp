#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e3 + 5;

struct node {
	int prev, next;
}l[N];
void del(int x) {
	l[l[x].prev].next = l[x].next;
	l[l[x].next].prev = l[x].prev;
}
char c;
string s, a, ans;
int n, p[N], np[N], vis[N];

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cout.precision(10), cout.setf(ios :: fixed);


	cin >> c >> s;
	char x;
	while (cin >> x) {
		if ('a' <= x && x <= 'z') {
			a += x;
			ans += ' ';
		}
		if ('A' <= x && x <= 'Z') {
			a += x - 'A' + 'a';
			ans += ' ';
		}
	}
    // cout << c << " " << s << " " << a << endl;
	int n = a.size(), f = 0, cnt = 0;
	s += 'a' - 1;
	for (int i = 0; i < n; i++) {
		l[i].prev = i - 1;
		l[i].next = i + 1;
	}
	int len = n;
	l[0].prev = n;
	l[n].prev = n - 1;
	l[n].next = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		int k = s[i] - 'a' + 2;
		if (len < k) {
			f ^= 1;
			continue;
		}
		if (f == 0) {
			int j = n, flag = 0;
			while (1) {
				for (int tmp = k; tmp >= 1; tmp--) {
					j = l[j].next;
					if (j == n) {
						flag = 1;
						break;
					}
				}
				if (flag) {
					break;
				}
//				cerr << j << endl;
				vis[j] = 1;
				p[cnt] = j;
				np[j] = cnt++;
				len--;
				del(j);
			}
		} else {
			int j = n, flag = 0;
			while (1) {
				for (int tmp = k; tmp >= 1; tmp--) {
					j = l[j].prev;
					if (j == n) {
						flag = 1;
						break;
					}
				}
				if (flag) {
					break;
				}
//				cerr << ":" << j << endl;
				vis[j] = 1;
				p[cnt] = j;
				np[j] = cnt++;
				len--;
				del(j);
			}
		}
		f ^= 1;
	}
	if (c == 'E') {
		for (int i = 0; i < n; i++) {
			ans[p[i]] = a[i];
		}
	} else {
		for (int i = 0; i < n; i++) {
			ans[np[i]] = a[i];
		}
	}
	cout << ans << "\n";

	return 0;
}
