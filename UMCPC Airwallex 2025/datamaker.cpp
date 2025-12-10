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
const int N = 100010;
int n, m, A, B, F;
int a[100009], b[100009], perm[100009];
vector<int> vb;
int gen(int l, int r) {
    return (rand() ^ (rand() << 15)) % (r - l + 1) + l;
}
int main() {
    srand(time(0));
    n = 5; m = 5;
    A = 3; B = 3; F = 1;
    for (int i = 0; i < n; i++) vb.pb(i);
    while (F--) {
        int idx = gen(0, sz(vb) - 1);
        swap(vb[idx], vb[sz(vb) - 1]);
        b[vb.back()] = -1;
        vb.pop_back();
    }
    vb.clear();
    for (int i = 0; i < n; i++) vb.pb(i);
    while (A--) {
        int idx = gen(0, sz(vb) - 1);
        a[vb[idx]]++;
    }
    vb.clear();
    for (int i = 0; i < n; i++) if (!b[i]) vb.pb(i);
    while (B--) {
        int idx = gen(0, sz(vb) - 1);
        b[vb[idx]]++;
    }
    // for (int i = 0; i < n; i++) perm[i] = i;
    // for (int i = 1; i < n; i++) swap(perm[i], perm[gen(0, i)]);
    cout << n << " " << m << endl;
    for (int i = 0; i < n; i++) cout << a[i] << " "; cout << endl;
    for (int i = 0; i < n; i++) cout << b[i] << " "; cout << endl;
    while (m--) {
        int u = gen(0, n - 1), v = gen(0, n - 1);
        cout << u << " " << v << endl;
    }
    return 0;
}