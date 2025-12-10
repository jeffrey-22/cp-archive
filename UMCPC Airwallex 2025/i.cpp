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
int n;
int c[109];
double ans = 0, discount = 0, fee;
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    double sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        sum += c[i];
    }
    if (sum <= 20)
        fee = 5;
    else if (sum < 50)
        fee = 3;
    else
        fee = 0;
    sort(c + 1, c + n + 1);
    if (n >= 3) {
        c[1] = 0;
    }
    if (n >= 5 && n <= 6) {
        discount = 0.1;
    }
    else if (n >= 7)
        discount = 0.15;
    
    sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += c[i];
    }
    sum *= (1.0 - discount);
    sum += fee;
    printf("%.2lf\n", sum);
    return 0;
}