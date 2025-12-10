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
int n, m, k;
int tot = 0;
map<string, int> namemp;
double x;
double R[109][109], S[109][109];
void mult(double a[109][109], double b[109][109], double c[109][109]) {
    double aa[109][109], bb[109][109];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            aa[i][j] = a[i][j], bb[i][j] = b[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            c[i][j] = 0;
            for (int t = 1; t <= n; t++)
                c[i][j] = max(c[i][j], aa[i][t] * bb[t][j]);
        }
}
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n >> m;
    cin >> x >> k;
    for (int i = 1; i <= m; i++) {
        string S1, S2;
        double r;
        cin >> S1 >> S2 >> r;
        if (!namemp[S1]) {
            namemp[S1] = ++tot;
        }
        if (!namemp[S2]) {
            namemp[S2] = ++tot;
        }
        int u, v;
        u = namemp[S1];
        v = namemp[S2];
        R[u][v] = r;
    }
    for (int i = 1; i <= n; i++) R[i][i] = 1.0;
    int rt = namemp["AUD"];
    for (int i = 1; i <= n; i++) S[i][i] = 1.0;
    k++;
    while (k) {
        if (k & 1)
            mult(S, R, S);
        k >>= 1;
        mult(R, R, R);
    }
    cout << S[rt][rt] * x << endl;
    return 0;
}