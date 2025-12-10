#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size() 
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> pii; 
typedef vector<int> vi;
int n, k, ht;
int a[2000009], f[2000009];
int get() {
    int x = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    n = get(); k = get();
    ht = (n + k) / 2;
    for (int i = 1; i <= n; i++){
        a[i] = get();
        f[a[i]]++;
    }
    int s = 0;
    for (int i = 0; i <= 2000000; i++) {
        s += f[i];
        if (s > ht) {
            cout << i - 1 << endl;
            return 0;
        }
    }
    return 0;
}