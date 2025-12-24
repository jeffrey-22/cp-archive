#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
int n, k;
int p[100009], cntp[109];
double f[39][39], oa[39][39];
double nCr[69][69];
double qpow(double chance, int n) {
    double ret = 1;
    while (n) {
        if (n & 1) ret = ret * chance;
        n >>= 1; chance *= chance;
    }
    return ret;
}
double estoa(int a, int b) {
    // a +, b -
    double tau;
    double weightSum;
    double weight[109];
    for (int x = 0; x <= 100; x++) {
        int cnt = cntp[x];
        double prior = 1.0 * cnt / n;
        double plus = 1.0 * x / 100;
        double chance = nCr[a + b][a] * qpow(plus, a) * qpow(1 - plus, b);
        weight[x] = prior * chance;
        // if (cnt > 0 && x > 0 && x < 100) assert(weight[x]);
    }
    weightSum = 0;
    for (int x = 0; x <= 100; x++) weightSum += weight[x];
    // assert(weightSum > 0);
    if (weightSum < 1e-9) {
        if (cntp[0] > 0 && a > 0) return 0;
        if (cntp[100] > 0 && b > 0) return 0;
        return 1;
    }
    tau = 1.0 / weightSum;
    // cout << weightSum << " - " << tau << endl;
    double totOAchance = 0;
    for (int x = 0; x <= 100; x++) {
        double plus = 1.0 * x / 100;
        double cond = weight[x] * tau;
        totOAchance += plus * cond;
    }
    return totOAchance;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0); cin.exceptions(cin.failbit);
    cout << fixed << setprecision(12);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        cntp[p[i]]++;
    }
    for (int i = 0; i <= 60; i++) nCr[i][0] = nCr[i][i] = 1;
    for (int i = 1; i <= 60; i++) for (int j = 1; j < i; j++) nCr[i][j] = nCr[i - 1][j - 1] + nCr[i - 1][j];
    for (int a = 0; a <= k; a++)    
        for (int b = 0; b <= k; b++) {
            oa[a][b] = estoa(a, b);
            // cout << a << " " << b << ": " << oa[a][b] << endl;
        }
    for (int j = 0; j <= k; j++) f[0][j] = 1;
    for (int i = 1; i <= k; i++) 
        for (int j = 0; j <= k - i; j++) {
            double s1 = 0, s2 = 0;
            double o = 1 - oa[j][k - i - j];
            s1 = f[i - 1][j] * o + f[i - 1][j + 1] * (1 - o);
            s2 = 0.0 * o + f[i - 1][j + 1] * 2 * (1 - o);
            f[i][j] = max(s1, s2);
        }
    double ans = f[k][0] - 1;
    cout << ans * 1000 << endl;
}

/*

f[i][j] = max expected value for i remaining rounds, except there are j +s from (k-i) rounds, assuming i hold 1 dollar at this moment
f[i][j] = 
Strat 1: bet 0
outcome a: get -: f[i - 1][j]
outcome b: get +: f[i - 1][j + 1]
Strat 2: bet 1
outcome a: get -: 0
outcome b: get +: f[i - 1][j + 1] * 2

PROBLEM: Given that there are (a, b) (+, -), compute prob of each outcome
prob of I = t 
Prob(outcome a|I=t, obs) * P(I=t|obs)
P(I=t | obs) = tau * P(obs | I = t) * P(I = t) = tau * (cnt/n) * (C(a+b,a)*plus^a*minus^b)


Strategy must be either bet 0 or bet full
*/