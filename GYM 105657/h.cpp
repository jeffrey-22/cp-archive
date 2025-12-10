#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, k;
int l[100009], r[100009], p[100009];
int main() {
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> k;
        vector<int> Ls = {};
        for (int i = 1; i <= k; i++) {
            cin >> l[i] >> r[i];
            Ls.push_back(r[i] - l[i] + 1);
        }
        sort(all(Ls));
        int L = Ls.back();
        int a = 0, b = 0;
        for (auto v : Ls)
            if (v == L) a++;
            else if (v == L - 1) b++;
        if (a >= 2 && a + b == sz(Ls))
            cout << "IMPOSSIBLE" << endl;
        else {
            for (int i = 1; i <= k; i++)
                if (r[i] - l[i] + 1 == L) {
                    swap(l[1], l[i]);
                    swap(r[1], r[i]);
                    break;
                }
            p[l[1]] = 0; for (int i = l[1] + 1; i <= r[1]; i++) p[i] = i - 1;
            for (int i = 2; i <= k; i++) {
                if (r[i] - l[i] + 1 >= L - 1) {
                    p[l[i]] = l[1]; for (int j = l[i] + 1; j <= r[i]; j++) p[j] = j - 1;
                }
                else {
                    int len = r[i] - l[i] + 1;
                    int delta = L - len;
                    p[l[i]] = l[1] + delta - 1; for (int j = l[i] + 1; j <= r[i]; j++) p[j] = j - 1;
                }
            }
            for (int i = 1; i <= n; i++) cout << p[i] << " "; cout << endl;
        }
    }

    return 0;
}