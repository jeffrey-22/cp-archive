#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i =(a); i < (b);i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
ll n, qu, qv;
ll clkdist(ll x, ll y) {
    x %= n; y %= n;
    x += n; y += n;
    x %= n; y %= n;
    if (x <= y) return y - x;
    y += n;
    return y - x;
}
ll revdist(ll x, ll y) {
    return clkdist(y, x);
}
ll dist(ll x, ll y) {
    return min(clkdist(x, y), revdist(x, y));
}
ll bestdist(ll x, ll y, ll u = qu, ll v = qv) {
    return min(dist(x, y), min(dist(x, u) + dist(v, y) + 1, dist(y, u) + dist(v, x) + 1));
}
ll ask(ll x, ll y) {
    ll d;
    x %= n; y %= n;
    x += n; y += n;
    x %= n; y %= n;
    assert(x != y);
    x++, y++;
    cout << "? " << x << " " << y << endl;
    cout.flush();
    cin >> d;
    // d = bestdist(x, y);

    return d;
}
void guess(ll x, ll y) {
    x %= n; y %= n;
    x += n; y += n;
    x %= n; y %= n;
    assert(x != y);
    x++, y++;
    int d;
    cout << "! " << x << " " << y << endl;
    cout.flush();
    cin >> d;
    // d = (min(x,y)==min(qu, qv) && max(x,y)==max(qu,qv)) ? 1 : -1; if (d==1) cout << "OK" << endl;else cout << "WRONG GUESS" << endl;

    if (d == -1) exit(0);
}
void solve(ll x, ll y, ll d) { // clockwise x to y, delta = d
    x %= n; y %= n;
    x += n; y += n;
    x %= n; y %= n;
    ll L = x, R = y;
    if (L > R) R += n;
    ll M;
    while (L < R) {
        M = (L + R + 1) >> 1ll;
        if (ask(x, M) == dist(x, M))
            L = M;
        else
            R = M - 1;
    }
    M = L;
    guess(L - d + d/2, L + d/2);
}
void solve2(ll a, ll b, ll c, ll d, ll X, ll Q) {
    ll L = a, R = d;
    while (L > R) R += n,c+=n,d+=n; while (L <= R - n) R -= n,c-=n,d-=n;
    ll M;
    while (L < R) {
        M = (L + R + 1) >> 1ll;
        if (ask(a, M) == dist(a, M))
            L = M;
        else
            R = M - 1;
    }
    M = L;
    ll sx, sy;
    ll P = ask(a, L + 1) - 1 + (L + 1 - a);
    ll T = X + a - c;
    // cout << "a=" << a << " L=" << L%n << endl;
    // cout << "plus=" << P << " minus=" << T << endl;
    ll SX2 = P + T;
    assert(SX2 % 2 == 0);
    sx = SX2 / 2;
    sy = P - sx;
    guess(a - sx, a + sy);
}
void solve3(ll a, ll b, ll c, ll d, ll X, ll Q) {
    ll L = c, R = b;
    while (L > R) R += n,b+=n;
    ll M;
    while (L < R) {
        M = (L + R) >> 1ll;
        if (ask(b, M) == dist(b, M))
            R = M;
        else
            L = M + 1;
    }
    M = L;
    ll sx, sy;
    ll P = ask(b, L - 1) + b - L;
    ll T = -X + 1 +clkdist(c,b);
    // cout << "a=" << a << " L=" << L%n << endl;
    // cout << "plus=" << P << " minus=" << T << endl;
    ll SX2 = P + T;
    assert(SX2 % 2 == 0);
    sx = SX2 / 2;
    sy = P - sx;
    guess(b - sx, b + sy);
}
int main() {

    int Tt; cin >> Tt;
    while (Tt--) {
        cin >> n;
        // n = rand() % 20 + 4;

        // do{qu = (rand() ^ (rand() << 15)) % n + 1, qv = (rand() ^ (rand() << 15)) % n + 1;}while (dist(qu,qv)<=1);
        // qu = 7, qv = 2;
        // cout<<"ANS="<<qu<< " "<<qv<<endl;


        if (n <= 8) {
            int ok = 0;
            for (int x = 0; x < n; x++)
                for (int y = 0; y < n; y++)
                    if (dist(x, y) >= 2) {
                        if (ok) continue;
                        if (ask(x, y) == 1) {
                            ok = 1;
                            guess(x, y);
                        }
                    }
            assert(ok);
            continue;
        }
        ll a = n - 1, b = 0;
        ll c = n / 2 + 1, d = n / 2;
        ll ac, ad, bc, bd;
        ac = ask(a, c);
        ad = ask(a, d);
        bc = ask(b, c);
        bd = ask(b, d);
        if (ac == 1) {guess(a, c); continue;}
        if (ad == 1) {guess(a, d); continue;}
        if (bc == 1) {guess(b, c); continue;}
        if (bd == 1) {guess(b, d); continue;}
        if (ac == dist(a, c) && ad == dist(a, d) && bc == dist(b, c) && bd == dist(b, d)) {
            a += 2, b += 2, c += 2, d += 2;
            ac = ask(a, c);
            ad = ask(a, d);
            bc = ask(b, c);
            bd = ask(b, d);
            if (ac == 1) {guess(a, c); continue;}
            if (ad == 1) {guess(a, d); continue;}
            if (bc == 1) {guess(b, c); continue;}
            if (bd == 1) {guess(b, d); continue;}
        }
        assert(ac < dist(a, c) || ad < dist(a, d) || bc < dist(b, c) || bd < dist(b, d));
        if (ac < dist(a, c) && bc == ac + 1 && ad == ac + 1)
            solve(c, a, dist(a, c) - ac + 1);
        else if (bd < dist(b, d) && ad >= bd && bc >= bd)
            solve(b, d, dist(b, d) - bd + 1);
        else {
            if (ad < dist(a, d) && bd >= ad + 1) {
                solve2(a, b, c, d, ad, dist(a,d));
            } else {
                assert(bc < dist(b, c));
                solve3(a, b, c, d, bc, dist(b,c));
            }
        }
    }
    return 0;
}