#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
string s1, s2, s3;
int m = 0;
int f[39];
int findf(int x) {return x==f[x]?x:f[x] = findf(f[x]);}
int main() {
    int Tt;
    cin >> Tt;
    while (Tt--) {
        for (int i = 1; i <= 26; i++) f[i] = i;
        cin >> s1;
        cin >> s2 >> s3;
        if (sz(s1) != sz(s2))
            cout << "NO" << endl;
        else if (sz(s1) != sz(s3))
            cout << "YES" << endl;
        else {
            for (int i = 0; i < sz(s1); i++) {
                int u = s1[i], v = s2[i];
                u = u - 'a' + 1;
                v = v - 'a' + 1;
                u = findf(u); v = findf(v);
                f[u] = v;
            }
            for (int i = 0; i < sz(s1); i++)
                s1[i] = findf(s1[i] - 'a' + 1);
            for (int i = 0; i < sz(s3); i++)
                s3[i] = findf(s3[i] - 'a' + 1);
            int ok = 0;
            for (int i = 0; i < sz(s3); i++)
                if (s1[i] != s3[i])
                    ok = 1;
            if (ok) cout << "YES" << endl; else cout << "NO" << endl;
        }
    }

    return 0;
}