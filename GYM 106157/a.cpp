#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < b; i++)
template<class T> int sgn(T x){return (x>0)-(x<0);}
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0): x(x), y(y) {}
    bool operator <(P p)const{return tie(x,y)<tie(p.x,p.y);}
    bool operator ==(P p)const{return tie(x,y)==tie(p.x,p.y);}
    P operator +(P p)const {return P(x+p.x, y+p.y);}
    P operator -(P p)const {return P(x-p.x, y-p.y);}
    P operator *(T d)const {return P(x*d, y*d);}
    T operator /(T d)const {return P(x/d, y/d);}
    T dot(P p)const{return x*p.x+y*p.y;}
    T cross(P p)const{return x*p.y-y*p.x;}
    T cross(P a, P b)const{return (a-*this).cross(b-*this);}
    T dist2() const{return x*x+y*y;}
    double dist() const{return sqrt((double)dist2());}
    double angle()const{return atan2(y, x);}
    P unit()const{return *this/dist();}
    P perp()const{return P(-y, x);}
    P normal() const{return perp().unit();}
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));
    }
    friend ostream& operator <<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
template<class P>
int sideOf(P s, P e, P p){return sgn(s.cross(e, p));}
typedef Point<double> P;
double segDist(P &s, P &e, P &p) {
    if (s == e) return (p-s).dist();
    auto d = (e-s).dist2(), t = min(d, max(.0, (p-s).dot(e-s)));
    return ((p-s)*d-(e-s)*t).dist()/d;
}
template<class T>
T polygonArea2(vector<Point<T>>&v) {
    T a = v.back().cross(v[0]);
    rep(i, 0, sz(v) - 1) a += v[i].cross(v[i+1]);
    return a;
}
template<class F>pair<double, P> hillClimb(P start, F f) {
    pair<double, P> cur(f(start), start);
    for (double jmp=5;jmp>1e-9;jmp/=4) {
        rep(j, 0, 200) rep(dx, -1, 2) rep(dy, -1, 2) {
            if (dx == 0 && dy == 0) continue;
            P p = cur.second;
            p.x += dx * jmp, p.y += dy * jmp;
            cur = max(cur, make_pair(f(p), p));
        }
    }
    return cur;
}
template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0, n = sz(p);
    rep(i, 0, n) {
        P q = p[(i + 1) % n];
        if (segDist(p[i], q, a) <= 1e-9) return !strict;
        cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}
double timeTaken(P p, vector<P> &a) {
    double ret = 1e9;
    for (int i = 0; i < sz(a); i++) {
        P A = a[i], B = a[(i + 1) % sz(a)];
        ret = min(ret, segDist(A, B, p));
    }
    if (!inPolygon(a, p)) ret *= -1;
    return ret;
}
double speed;
int n;
vector<P> a;
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cout << fixed << setprecision(10);
    cin >> speed >> n;
    a = vector<P>(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].x >> a[i].y;
    if (polygonArea2(a) < 0) reverse(all(a));
    pair<double, P> ans = {-1e9, P(0, 0)};
    // cerr << timeTaken(P(-3, 1), a) << endl;
    auto f = [&](P p) {return timeTaken(p, a);};
    for (int i = 1; i < n; i+=2) {
        ans = max(ans, hillClimb(a[i], f));
    }
    cout << ans.first / speed << endl;
    cout << ans.second.x << " " << ans.second.y << endl;
}