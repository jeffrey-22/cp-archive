#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
const int B = 256;

void work() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        scanf("%d", &a[i]);
    }
    if (k == 1) {
        for (int i = 1; i <= n; i++)
            printf("%d ", i);
        printf("\n");
        return;
    }
    int mx = 0;
    vector<int> b(n + 1);
    vector<int> nxt(n + 1), tmp(n + 1);
    vector<pair<int, int>> to(n + 1);
    for (int L = 0; L < n; L+=B) {
        int R = min(L + B, n);
//        cerr << L << ":" << R << endl;

        vector<int> p;
        for (int i = L; i < R; i++) {
            p.emplace_back(a[i]);
        }
        int m = p.size();
        sort(p.begin(), p.end());
        p.emplace_back(n);
        
        for (int i = n - 1; i >= 0; i--) {
            nxt[i] = nxt[i + 1] + 1;
            if (b[i + 1]) {
                nxt[i] = 1;
            }
            tmp[i] = i + nxt[i];
        }
        for (int i = n - 1; i >= 0; i--) {
            nxt[i] = min(i + max(nxt[i], k), n);
        }

        to[n] = make_pair(n, 0);
        for (int i = n - 1, j = m; i >= 0; i--) {
            if (j && i < p[j - 1]) {
                j--;
            }
            if (i >= mx || nxt[i] > p[j]) {
                to[i] = make_pair(i, 0);
            } else {
                to[i] = make_pair(to[nxt[i]].first, to[nxt[i]].second + 1);
            }
        }
        /*
        for (int i = 0; i < n; i++) {
            cerr << nxt[i] << " \n"[i + 1 == n];
        }
        for (int i = 0; i < n; i++) {
            cerr << to[i].first << " \n"[i + 1 == n];
        }
        */
        
        for (int i = L; i < R; i++) {
            b[a[i]] = 1;
            mx = max(mx, a[i]);

            int x = 0, j = 0, ans = 0;
            while (x < mx) {
//                cerr << i << ' ' << b[p[j]] << ',' << x << endl;
                ans += to[x].second;
                x = to[x].first;
                // if (i == 6)
                // cerr << x << ":" << ans << endl;
                if (x >= mx) {
                    break;
                }
                while (j < m && p[j] <= x) {
                    j++;
                }
                while (j < m && !b[p[j]]) {
                    j++;
                }
                x = max(x + k, min(tmp[x], p[j]));
                ans++;
                // if (i == 6)
                // cerr << x << ":" << ans << endl;
            }
            printf("%d ", ans);
            // cout << ans << ' ';
        }
    }
    printf("\n");
    // cout << "\n";
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    int T;
    scanf("%d", &T);
    // cin >> T;
    while (T--) {
        work();
    }

    return 0;
}
/*
5
100000 2
100000 2
100000 2
100000 2
100000 2
*/