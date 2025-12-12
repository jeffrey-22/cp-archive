#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < b; i++)
string c1, c2;
char a[19][109];
int m = 0;
void addemp() {
    m++;
    for (int i = 1; i <= 5; i++) a[i][m] = '.';
}
void add0() {
    m++;
    for (int i = 1; i <= 5; i++) a[i][m] = 'X';
}
void add1() {
    add0();
    addemp(); a[1][m] = a[5][m] = 'X';
    add0();
}
void add2() {
    add0();
    addemp(); a[1][m] = a[3][m] = a[5][m] = 'X';
    add0();
}
void addstr(string str) {
    int x = 4, y = m;
    assert(a[x][y] == 'X');
    for (int i = 0; i < sz(str) - 1; i++) addemp();
    for (int i = 0; i < sz(str); i++)
        a[x][y + i] = str[i];
    addemp();
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> c1 >> c2;
    addemp();
    for (int i = 0; i < sz(c1); i++) {
        if (c1[i] == 'B') add2();
        else if (c1[i] == 'A' || c1[i] == 'D' || c1[i] == 'O' || c1[i] == 'P' || c1[i] == 'Q' || c1[i] == 'R') add1();
        else add0();
        if (i != sz(c1) - 1) addemp();
    }
    addstr(c2);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= m; j++)
            cout << a[i][j];
        cout << endl;
    }
}