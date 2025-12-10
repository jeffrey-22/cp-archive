#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
string p;
// C - capslock, S - left shift, D - right shift
string ls1 = "`123456qwertasdfgzxcvb~!@#$%^QWERTASDFGZXCVB";
string ls2 = "1234567wertysdfghxcvbn!@#$%^&WERTYSDFGHXCVBN";
string rs1 = "7890-=yuiop[]\\hjkl;'nm,./&*()_+YUIOP{}|HJKL:\"NM<>?";
string rs2 =  "67890-tyuiop[]ghjkl;bnm,.^&*()_TYUIOP{}GHJKL:BNM<>";
int issame(string s, string t, int c);
string flipCL(string s) {
    string r = "";
    for (auto c : s) {
        if (c >= 'a' && c <= 'z') r.push_back(c - 'a' + 'A');
        else if (c >= 'A' && c <= 'Z') r.push_back(c - 'A' + 'a');
        else r.push_back(c);
    }
    return r;
}
int isLS(string s, string t, int c) {
    int n = sz(s);
    if (n != sz(t)) return 0;
    map<char, char> lsmap = {};
    for (int i = 0; i < sz(ls1); i++)
        lsmap[ls1[i]] = ls2[i];
    string q= "";
    for (int i = 0; i < n; i++) {
        char cc = s[i];
        if (lsmap.count(cc)) {
            cc = lsmap[cc];
        }
        else {
        }
        q.push_back(cc);
    }
    if (c) q = flipCL(q);
    return issame(t, q, 0);
}
int isRS(string s, string t, int c) {
    int n = sz(s);
    if (n != sz(t)) return 0;
    map<char, char> rsmap = {};
    for (int i = 0; i < sz(rs1); i++)
        rsmap[rs1[i]] = rs2[i];
    string q= "";
    for (int i = 0; i < n; i++) {
        char cc = s[i];
        if (rsmap.count(cc)) {
            cc = rsmap[cc];
        }
        else {
        }
        q.push_back(cc);
    }
    if (c) q = flipCL(q);
    return issame(t, q, 0);
}
int isEC(string s, string t, int c) {
    int n = sz(s);
    if (c) t = flipCL(t);
    if (n + 1 != sz(t)) return 0;
    int k = 0;
    for (int i = 0; i < n + 1; i++)
        if (s[i] != t[i] || i == n) {
            k = i;
            break;
        }
    for (int i = 0; i < k; i++)
        if (s[i] != t[i])
            return 0;
    for (int i = k + 1; i < n + 1; i++)
        if (s[i - 1] != t[i])
            return 0;
    return 1;
}
int isMC(string s, string t, int c) {
    return isEC(t, s, c);
}
int issame(string s, string t, int c) {
    if (sz(s) != sz(t)) return 0;
    if (c) t = flipCL(t);
    for (int i = 0; i < sz(s); i++)
        if (s[i] != t[i])
            return 0;
    return 1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    assert(sz(rs1) == sz(rs2));
    assert(sz(ls1) == sz(ls2));
    cin >> p;
    int n; cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int ok = 0;
        for (int i = 0; i <= 1; i++)
            ok += (isLS(p, s, i) || isRS(p, s, i) || isEC(p, s, i) || isMC(p, s, i) || issame(p, s, i));
        if (ok)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
/*

A:'
2
AL;
al;


='A:'
1
=1S:'


*/