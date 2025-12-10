#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size() 
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> pii; 
typedef vector<int> vi;
signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;
    vector<int> v(n * 2);
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        v[i] = x;
        v[i + n] = x;
    }
    int ans = -1e18;
    int l = 0;
    int sum = 0;
    for(int i = 0; i < 2 * n; i++){
        if(i < q) {
            sum += v[i];
        }else{
            ans = max(ans, sum);
            sum += v[i];
            sum -= v[l];
            l ++;
        }
    }
    ans = max(ans, sum);
    cout << ans << endl;
}