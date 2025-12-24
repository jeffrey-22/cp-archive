#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, Tt;
string s1, s2;
int a[1000009], b[1000009], ib[1000009], f[1000009][2];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> Tt;
    while (Tt--) {
        cin >> s1;
        cin >> s2;
        n = sz(s1);
        for (int i = 0; i < n; i++)
            a[i + 1] = s1[i] - '0';
        for (int i = 0; i < n; i++)
            b[i + 1] = s2[i] - '0';
        ib[1] = a[1];
        for (int i = 2; i <= n; i++)
            ib[i] = ib[i - 1] ^ a[i];
        for (int i = 1; i <= n; i++)
            b[i] ^= ib[i];
        for (int i = n; i >= 1; i--)
            for (int x = 0; x <= 1; x++) {
                int curval = b[i] ^ x;
                if (i == n) {
                    if (curval) f[i][x] = 1;
                    else f[i][x] = 0;
                } else {
                    if (curval) {
                        f[i][x] = min(f[i + 1][x ^ 1] + 1, f[i + 1][x] + 1);
                    } else {
                        f[i][x] = min(f[i + 1][x], f[i + 1][x ^ 1] + 2);
                    }
                }
            }
        cout << min(f[1][0], f[1][1] + 1) << endl;
    }
}

/*
y(i) = y(i-1) ^ x(i)

x1 x2 x3  x4   x5
x1 12 123 1234 12345

xor a suffix of y(i) 
f[i][x] = min(f[i + 1][x ^ 1] + 1, f[i + 1][x]) if a[i] ^ x = 1


*/