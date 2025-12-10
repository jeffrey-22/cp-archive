#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const ll mod = 1e9 + 7;
int n1, n2, m, k;
int F[1100000][], A[1050009];
int main() {
    int Tt; cin >> Tt;
    while (Tt--) {

    }
    return 0;
}

// only deal with connected components, combine results afterwards
// F(SS) = ways to assign all elements in SS, no restriction (either S, T or ST), as long as all edges within SS is resolved
// A(SS) = ways to assign all elements in SS, plus all x in SS must be = S / ST, plus all edges within SS is resolved
// F(SS) = 2(A(Qi AND S') * F(S' - (Qi AND S'))) + F(S'), S' = SS - {i}
// A(SS) = 1 * A(S' - (Qi AND S')) + A(S')
// special case if (i, i) is connected. only use F(S') / A(S')
// HOW TO COUNT SIZE OF S / T? O(m^2 2^m) PIE?
// C(n1 - 1, |S| - 1) * C(n2 - 1, |T| - 1)