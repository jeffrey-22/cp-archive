#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, c1;
int a[200009];
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a + 1, a + n + 1);
        c1 = 0;
        for (int i = 1; i <= n; i++)
            if (a[i] == 1)
                c1++;
        int og = (n % 2 == 1) ? 0 : 1;
        int diff = 0;
        if (n - 1 <= c1 && c1 <= n) diff = 0; else diff = (n - 1) - c1;
        int ans = og ^ (diff % 2);
        if (ans == 0) puts("Alice"); else puts("Bob");
    }
}
/*
no matter what can find B => A
[v]: A
[1, v]: B
[>1, >1]: A
[1, 1, v]: A
[1, >1, >1]: B
[>1, >1, >1]: A
[1, 1, 1, v]: B
[1, 1, >1, >1]: A
[1, >1, >1, >1]: 
n-1/n 1s: n % 2 == 1 ? A : B
otherwise, diff = (n-1) - (#1), xor : diff

n = 5, <A>, 
1 odd B
1 even A

*/