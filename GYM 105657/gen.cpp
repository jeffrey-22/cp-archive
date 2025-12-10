#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int T, n, m,c;
ll a[1000009];
ll genll() {
    ll a = rand();
    ll b = rand();
    ll c = rand();
    ll d = rand();
    return a ^ (b<<16) ^ (c<<16) ^ (d<<15);
}
int gen(int l, int r) {
    return (rand() ^ (rand()<<14)) % (r-l+1) +l;
}
int main(int argc, char** argv) {
    srand(time(0));
    int T = 10;
    cout << T << endl;
    while(T--) {
        n = gen(5, 8), m = gen(1, 5), c = gen(0, 5);
        cout << n << " " << m << " " << c << endl;
        for (int i = 1; i <= n; i++) {
            cout << gen(0, 1000) << " ";
        }
        cout << endl;
        for (int i = 1; i <= m; i++) {
            a[i] = a[i - 1] + gen(0, 1000);
            cout << a[i] << " ";
        }
        cout << endl;
        cout << endl;
    }

    return 0;
}

// b2+x = t(b1+x), t >= 1
// b2 + x = tb1 + tx
// x = (b2 - tb1) / (t - 1), b2 >= 2b1