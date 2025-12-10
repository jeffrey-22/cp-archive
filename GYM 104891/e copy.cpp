#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;

int st[N];
int n, mn[N], mx[N];
int nxtmn[N], nxtmx[N];
void getnxt(int *a, int *nxt, int f) {
    for (int i = 1; i <= n; i++) {
        a[i] *= f;
    }
    int top = 0;
    nxt[n + 1] = st[top] = n + 1;
    for (int i = n; i >= 1; i--) {
        while (top && a[st[top]] > a[i]) {
            top--;
        }
        nxt[i] = min(nxt[i + 1], st[top]);
        st[++top] = i;
    }
    for (int i = 1; i <= n; i++) {
        a[i] *= f;
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> mn[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> mx[i];
    }
    getnext(mn, nxtmn, 1);
    getnext(mx, nxtmx, -1);
    for (int i = 1; i <= n; i++) {
        for (int j = nxt[i]; j < nxt[i + 1]; j++) {

        }
    }

    return 0;
}