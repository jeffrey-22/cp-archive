#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator < (P p) const {return tie(x, y) < tie(p.x, p.y);}
    bool operator == (P p) const {return tie(x, y) == tie(p.x, p.y);}
    P operator + (P p)const {return P(x+p.x, y+p.y);}
    P operator - (P p)const {return P(x-p.x, y-p.y);}
    P operator *(T d) const{return P(x*d,y*d);}
    P operator /(T d) const{return P(x/d,y/d);}
    T dot(P p)const{return x*p.x+y*p.y;}
    T cross(P p)const{return x*p.y-y*p.x;}
    T cross(P a, P b)const{return (a-*this).cross(b-*this);}
    T dist2() const{return x*x+y*y;}
    double dist() const {return sqrt((double)dist2());}
    double angle()const{return atan2(y,x);}
    P unit()const{return *this/dist();}
    P perp()const{return P(-y, x);}
    P normal() const{return perp().unit();}
    friend ostream& operator << (ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
template<class P>
pair<int, P>lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0)
        return {-(s1.cross(e1, e2)==0), P(0, 0)};
    auto p = s2.cross(e1,e2), q = s2.cross(e2, s1);
    return {1, (s1*p+e1*q)/d};
}
template<class T>
T polygonArea2(vector<Point<T>> &v) {
    T a=v.back().cross(v[0]);
    rep(i, 0, sz(v) - 1) a += v[i].cross(v[i+1]);
    return a;
}
typedef Point<double> P;
vector<P> convexHull(vector<P> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<P> h(sz(pts) + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s=--t, reverse(all(pts)))
        for (P p : pts) {
            while( t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
template<class P>
double lineDist(const P &a, const P &b, const P &p) {
    return (double)(b-a).cross(p-a)/(b-a).dist();
}
template<class P>
bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s-p).dot(e - p) <= 0;
}
template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0, n = sz(p);
    rep(i, 0, n) {
        P q = p[(i + 1) % n];
        if (onSegment(p[i], q, a)) return !strict;
        cnt ^= ((a.y < p[i].y) - (a.y<q.y)) * a.cross(p[i],q) > 0;
    }
    return cnt;
}
int n;
P a[109];
vector<P> hull = {}, tmp = {};
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    hull.push_back(P(0,0));
    for (int i = 1; i <= n; i++)
        hull.push_back(a[i]);
    hull = convexHull(hull);
    int u = 0;
    for (int i = 0; i < sz(hull); i++)
        if (hull[i] == P(0, 0))
            u = i;
    for (int i = u; i < sz(hull); i++)
        tmp.push_back(hull[i]);
    for (int i = 0; i < u; i++)
        tmp.push_back(hull[i]);
    hull = tmp;
    if (sz(hull) <= 2) {
        cout << 0 << endl;
        return 0;
    }
    cout << fixed << setprecision(9);
    P A = hull[1];
    P B = hull[sz(hull) - 1];
    P O = P(0, 0);
    if (sz(hull) == 3) {
        vector<P> tri = {O, A, B};
        double ans = 0.5 * polygonArea2<double>(tri);
        cout << ans << endl;
        return 0;
    }
    double ans = 1e9;
    for (int i = 2; i <= (sz(hull)) - 1; i++) {
        P X = hull[i - 1];
        P Y = hull[i];
        auto [tA, IA] = lineInter(X, Y, O, A);
        auto [tB, IB] = lineInter(X, Y, O, B);
        if (tA <= 0 || tB <= 0) continue;
        if (IA.x <= 0 || IB.x <= 0) continue;
        vector<P> tri = {O, IA, IB};
        double area = 0.5 * polygonArea2<double>(tri);
        ans = min(ans, area);
    }
    for (int i = 2; i <= (sz(hull)) - 2; i++) {
        P X = hull[i];
        double AA = 0.5 * (A.cross(B) / A.dist() / B.dist());
        double BB = lineDist(O, A, X);
        double CC = -lineDist(O, B, X);
        // cout << AA << " " << BB << " " << CC << endl;
        double xx = CC / AA;
        double yy = BB / AA;
        // cout << xx << " " << yy << endl;
        P IA = A.unit() * xx;
        P IB = B.unit() * yy;
        // cout << IA << " " << IB << endl;
        int ok = 1;
        vector<P> tri = {O, IA, IB};
        for (auto p : hull) {
            if (lineDist(IA, IB, p) <= -1e-9) {
                ok =0;
                break;
            }
        }
        if (!ok) continue;
        double area = 0.5 * polygonArea2<double>(tri);
        ans = min(ans, area);
    }

    cout << ans << endl;
}
/*
2
1 2
2 1

4
1 5
6 7
3 2
8 3

4
1 1
1 4
3 2
5 1

*/