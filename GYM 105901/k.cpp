#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;


int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    
    
}
/*
Top:

I am z,
3 Choices:
(Ai < Bi)
0 > ai wins
Ai > bi wins
Bi > z wins

Say I aim for a total win of W wins,
everyone else has <= W wins.

Start with putting all 0.
*/1