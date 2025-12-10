#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

template<class T> struct Point3D {
    typedef Point3D P;
    typedef const P& R;
    T x, y, z;
    explicit Point3D(T x=0, T y=0, T z=0): x(x), y(y), z(z) {}
    bool operator < (R p) const {
        return tie(x, y, z) < tie(p.x, p.y, p.z);
    }
    bool operator == (R p) const {
        return tie(x, y, z) == tie(p.x, p.y, p.z);
    }
    P operator + (R p) const {
        return P(x+p.x, y+p.y, z+p.z);
    }
    P operator - (R p) const {
        return P(x-p.x, y-p.y, z-p.z);
    }
    P operator * (T d) const {
        return P(x*d, y*d, z*d);
    }
    P operator / (T d) const {
        return P(x/d, y/d, z/d);
    }
    T dot(R p) const {
        return x*p.x+y*p.y+z*p.z;
    }
    P cross(R p) const {
        return P(y*p.z-z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
    }
    T dist2() const {return x*x+y*y+z*z;}
    double dist() const {return sqrt((double)dist2());}
    P unit() const {return *this/(T)dist();}
    P normal(P p) const {return cross(p).unit();}
};
typedef Point3D<double> P3;
double radius;
P3 my, s, t;
double f(double lambda) {
    P3 p = s + (t - s) * lambda;
    P3 q = p.unit() * radius;
    // cout << lambda << endl;
    // cout << s.x << " " << s.y << " " << s.z << endl;
    // cout << t.x << " " << t.y << " " << t.z << endl;
    // cout << (t-s).x << " " << (t-s).y << " " << (t-s).z << endl;
    // cout << p.x << " " << p.y << " " << p.z << endl;
    // cout << q.x << " " << q.y << " " << q.z << endl;
    double dist = (q-my).dist() / radius;
    return radius * 2 * asin(dist / 2);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    int Tt;
    cout << fixed << setprecision(10);
    cin >> Tt;
    while (Tt--) {
        cin >> radius;
        cin >> my.x >> my.y >> my.z;
        cin >> s.x >> s.y >> s.z;
        cin >> t.x >> t.y >> t.z;
        my = my.unit() * radius;
        s = s.unit() * radius;
        t = t.unit() * radius;
        double lambdaL, lambdaR, lambdaM1, lambdaM2;
        lambdaL = 0;
        lambdaR = 1;
        while (lambdaR - lambdaL > 3e-9) {
            lambdaM1 = (lambdaL * 2 + lambdaR) / 3;
            lambdaM2 = (lambdaL + lambdaR * 2) / 3;
            double f1 = f(lambdaM1);
            double f2 = f(lambdaM2);
            if (f1 < f2) lambdaR = lambdaM2;
            else lambdaL = lambdaM1;
        }
        double lambda = (lambdaL + lambdaR) / 2;
        cout << f(lambda) << endl;
    }

}
/*
2
100
1 1 1
1 0 0
0 1 0
100
-1 -1 0
1 0 0
0 1 0

*/