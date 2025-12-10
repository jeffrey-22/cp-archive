#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

template <class T> int sgn(T x) { return (x>0) - (x<0);}
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0): x(x), y(y) {}
    bool operator <(P p)const {return tie(x,y)<tie(p.x,p.y);}
    bool operator ==(P p)const{return tie(x,y)==tie(p.x,p.y);}
    P operator+(P p)const{return P(x+p.x,y+p.y);}
    P operator-(P p)const{return P(x-p.x,y-p.y);}
    P operator*(T d)const{return P(x*d,y*d);}
    P operator/(T d)const{return P(x/d,y/d);}
    T dot(P p)const{return x*p.x+y*p.y;}
    T cross(P p)const{return x*p.y-y*p.x;}
    T cross(P a, P b)const{return (a-*this).cross(b-*this);}
    T dist2() const {return x*x+y*y;}
    double dist() const{return sqrt((double)dist2());}
    P perp() const { return P(-y, x); }
};

typedef Point<double> P;
double ccRadius(const P &A, const P &B, const P &C) {
    return (B-A).dist() * (C-B).dist() * (A-C).dist() / abs((B-A).cross(C-A))/2;
}
P ccCenter(const P &A, const P &B, const P &C) {
    P b = C - A, c = B - A;
    return A + (b * c.dist2() - c * b.dist2()).perp()/b.cross(c)/2;
}

pair<P, double> mec(vector<P> ps) {
    shuffle(all(ps), mt19937(time(0)));
    P o = ps[0];
    double r = 0 ,EPS = 1 + 1e-9;
    rep(i,0,sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
        o = ps[i], r=0;
        rep(j,0,i) if((o-ps[j]).dist() > r*EPS) {
            o = (ps[i] + ps[j]) / 2;
            r = (o - ps[i]).dist();
            rep(k, 0, j) if ((o - ps[k]).dist() > r * EPS) {
                o = ccCenter(ps[i], ps[j], ps[k]);
                r = (o - ps[i]).dist();
            }
        }
    }
    return {o, r};
}

int n, m;
P a[1009], b[1009];

int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    cin >> m;
    for (int i = 1; i <= m; i++)
        cin >> b[i].x >> b[i].y;
    vector<P> vv = {};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            vv.push_back(b[j] - a[i]);
    auto [oo, radius] = mec(vv);
    cout << fixed << setprecision(10);
    cout << radius << " " << oo.x << " " << oo.y << endl;

}