#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template<class T> int sgn(T x){return (x>0)-(x<0);}
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point (T x=0, T y=0): x(x), y(y) {}
    bool operator<(P p)const{return tie(x,y)<tie(p.x,p.y);}
    bool operator==(P p)const{return tie(x,y)==tie(p.x,p.y);}
    P operator+(P p)const{return P(x+p.x,y+p.y);}
    P operator -(P p)const{return P(x-p.x,y-p.y);}
    P operator *(T d)const{return P(x*d,y*d);}
    P operator /(T d)const{return P(x/d,y/d);}
    T dot(P p)const{return x*p.x+y*p.y;}
    T cross(P p)const{return x*p.y-y*p.x;}
    T cross(P a,P b)const{return (a-*this).cross(b-*this);}
    T dist2()const{return x*x+y*y;}
    double dist() const{return sqrt((double)dist2());}
    P unit() const { return *this/dist(); }
    double angle()const{return atan2(y,x);}
    P perp()const{return P(-y,x);}// counter clockwise rotate 90 deg
};
typedef Point<double> P;
P a, b, c, d;
double h1, h2;
vector<tuple<P, P, P>> decomp(P a, P b, double hh) {
    P oa = a, ob = b;
    vector<tuple<P, P, P>> ret = {};
    for (int i = 0; i < 4; i++) {
        P h = a + (b - a) / 2;
        P delta = (b - a).perp();
        P vh = delta.unit();
        double og = ((b - a) / 2).dist();
        vh = vh * sqrt(hh * hh + og * og);
        P fake = h + vh;
        ret.push_back({a, b, fake});
        a = b; b = a + delta;
    }
    assert(a == oa && b == ob);
    return ret;
}
typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
if (s==e) return (p-s).dist();
auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
return ((p-s)*d-(e-s)*t).dist()/d;
}
template<class P> bool onSegment(P s, P e, P p) {
    return segDist(s,e,p) < 1e-9;
}
template<class P> vector<P> segInter(P a, P b, P c, P d) {
auto oa = c.cross(d, a), ob = c.cross(d, b),
oc = a.cross(b, c), od = a.cross(b, d);
if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
return {(a * ob - b * oa) / (ob - oa)};
set<P> s;
if (onSegment(c, d, a)) s.insert(a);
if (onSegment(c, d, b)) s.insert(b);
if (onSegment(a, b, c)) s.insert(c);
if (onSegment(a, b, d)) s.insert(d);
return {all(s)};
}
double ans;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> a.x >> a.y >> b.x >> b.y >> h1;
    cin >> c.x >> c.y >> d.x >> d.y >> h2;
    vector<tuple<P, P, P>> v1, v2; v1.clear(); v2.clear();
    v1 = decomp(a, b, h1);
    v2 = decomp(c, d, h2);
    ans = 1e20;
    for (auto [A, B, R] : v1)
        for (auto [C, D, Q] : v2) {
            ans = min(ans, (R - A).dist() + (C - A).dist() + (Q - C).dist());
            ans = min(ans, (R - B).dist() + (C - B).dist() + (Q - C).dist());
            ans = min(ans, (R - A).dist() + (D - A).dist() + (Q - D).dist());
            ans = min(ans, (R - B).dist() + (D - B).dist() + (Q - D).dist());
            vector<P> inter, inter2;
            inter = segInter(R, C, A, B);
            if (sz(inter) == 1) ans = min(ans, (R - C).dist() + (Q - C).dist());
            inter = segInter(R, D, A, B);
            if (sz(inter) == 1) ans = min(ans, (R - D).dist() + (Q - D).dist());
            inter = segInter(Q, A, C, D);
            if (sz(inter) == 1) ans = min(ans, (Q - A).dist() + (A - R).dist());
            inter = segInter(Q, B, C, D);
            if (sz(inter) == 1) ans = min(ans, (Q - B).dist() + (B - R).dist());
            inter = segInter(R, Q, A, B);
            inter2 = segInter(R, Q, C, D);
            if (sz(inter) == 1 && sz(inter2) == 1) 
                ans = min(ans, (R - inter[0]).dist() + (inter[0] - inter2[0]).dist() + (Q - inter2[0]).dist());
        }
    cout << fixed << setprecision(10);
    cout << ans << endl;
}