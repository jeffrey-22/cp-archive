#include "template.cpp"

typedef double T;
typedef vector<T> vd;
typedef vector<vd> vvd;
const T eps = 1e-8, inf = 1/.0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

int n;
int globalBest = 1e5;

vector<vector<int>> b = {};

typedef vector<double> vd;
// const double eps = 1e-12;
int solveLinear2(vector<vd>& A, vd& b, vd& x) {
int n = sz(A), m = sz(x), rank = 0, br, bc;
if (n) assert(sz(A[0]) == m);
vi col(m); iota(all(col), 0);
rep(i,0,n) {
double v, bv = 0;
rep(r,i,n) rep(c,i,m)
if ((v = fabs(A[r][c])) > bv)
br = r, bc = c, bv = v;
if (bv <= eps) {
rep(j,i,n) if (fabs(b[j]) > eps) return -1;
break;
}
swap(A[i], A[br]);
swap(b[i], b[br]);swap(col[i], col[bc]);
rep(j,0,n) swap(A[j][i], A[j][bc]);
bv = 1/A[i][i];
rep(j,0,n) if (j != i)  {
double fac = A[j][i] * bv;
b[j] -= fac * b[i];
rep(k,i+1,m) A[j][k] -= fac*A[i][k];
}
rank++;
}
// x.assign(m, 0);
// for (int i = rank; i--;) {
// b[i] /= A[i][i];
// x[col[i]] = b[i];
// rep(j,0,i) b[j] -= A[j][i] * b[i];
// }
x.assign(m, -123);
rep(i,0,rank) {
rep(j,rank,m) if (fabs(A[i][j]) > eps) goto fail;
x[col[i]] = b[i] / A[i][i];
fail:; 
}
return rank;
}
int solveLinear(vector<vd>& A, vd& b, vd& x) {
int n = sz(A), m = sz(x), rank = 0, br, bc;
if (n) assert(sz(A[0]) == m);
vi col(m); iota(all(col), 0);
rep(i,0,n) {
double v, bv = 0;
rep(r,i,n) rep(c,i,m)
if ((v = fabs(A[r][c])) > bv)
br = r, bc = c, bv = v;
if (bv <= eps) {
rep(j,i,n) if (fabs(b[j]) > eps) return -1;
break;
}
swap(A[i], A[br]);
swap(b[i], b[br]);
swap(col[i], col[bc]);
rep(j,0,n) swap(A[j][i], A[j][bc]);
bv = 1/A[i][i];
rep(j,i+1,n) {
double fac = A[j][i] * bv;
b[j] -= fac * b[i];
rep(k,i+1,m) A[j][k] -= fac*A[i][k];
}
rank++;
}
x.assign(m, 0);
for (int i = rank; i--;) {
b[i] /= A[i][i];
x[col[i]] = b[i];
rep(j,0,i) b[j] -= A[j][i] * b[i];
}
return rank; // (multiple so lutions if rank < m)
}
void dfs(vector<int> &unsInd, vector<int> a, int current, int total) {
    if (total >= globalBest) return;
    int left = sz(unsInd) - 1 - current + 1;
    vvd A(sz(a), vd(left, 0));
    vd B(sz(a)), X(left, 0);
    rep(t,0,sz(a)) B[t] = a[t];
    for (int t = 0; t < sz(a); t++)
        for (int x = current; x < sz(unsInd); x++) {
            int found = 0;
            for (auto q : b[unsInd[x]]) if (q == t) {found = 1; break;}
            A[t][x - current] = found;
        }
    int res = solveLinear(A, B, X);
    if (res == -1) return;
    if (res >= left) {
        assert(res == left);
        int sumInX = 0;
        for (auto v : X) {
            sumInX += (int)(v + 0.5); 
            if (abs(v - floor(v + 0.5)) > 1e-5) {
                return;
            }
            if (v < -1e-5) return;
        }
        if (total + sumInX < globalBest) {
            globalBest = min(globalBest, total + sumInX);
            cerr << "Found new global best = " << total << " + " << sumInX << endl;
            cerr << "Left indicies: "; for (auto t : unsInd) cerr << t << " "; cerr << endl;
            cerr << "X: "; for (auto t : X) cerr << t << " "; cerr << endl;
            cerr << "Current: " << current << " ; Total: " << total << endl;
            cerr << "a Left: "; for (auto qq : a) cerr << qq << " "; cerr << endl;
        }
        return;
    }
    if (current >= sz(unsInd)) {
        return;
    }
    int x = unsInd[current];
    int maxPossible = INT_MAX; for (auto t : b[x]) maxPossible = min(maxPossible, a[t]);
    for (int val = 0; val <= maxPossible; val++) {
        if (val > 0) {for (auto t : b[x]) a[t]--;}
        dfs(unsInd, a, current + 1, total + val);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    vector<string> tokens;
    vector<vector<string>> allTokens;
    while (1) {
        tokens = readTokens();
        if (tokens.empty()) break;
        n++;
        allTokens.push_back(tokens);
    }
    cerr << "n = " << n << endl;

    int m = 0;
    ll ans = 0;
    // vector<vector<ll>> a = {};
    for (int Tt = 0; Tt < n; Tt++) {
        vector<string> tokens = allTokens[Tt];

        // m = sz(tokens);
        
        string initConfig = tokens[sz(tokens) - 1];
        vector<int> a = {}; int val = 0;
        for (int j = 0; j < sz(initConfig); j++)
            if (initConfig[j] >= '0' && initConfig[j] <= '9') val = val * 10 + initConfig[j] - '0';
            else if (initConfig[j] == ',' || initConfig[j] == '}') {a.push_back(val); val = 0;}
        
        b.clear();
        for (int j = 1; j < sz(tokens) - 1; j++) {
            string seq = tokens[j];
            vector<int> c = {};
            int val = 0;
            for (int k = 0; k < sz(seq); k++)
                if (seq[k] >= '0' && seq[k] <= '9') val = val * 10 + seq[k] - '0';
                else if (seq[k] == ',' || seq[k] == ')') {
                    c.push_back(val);
                    val = 0;
                }
            b.push_back(c);
        }
        vector<vector<int>> qb = vector<vector<int>> (sz(b), vector<int>(sz(a), 0));
        for (int j = 0; j < sz(b); j++) {
            for (int k = j; k < sz(b); k++) {
                for (auto t : b[k]) qb[j][t] = 1;
            }
        }
        
        // dp.clear();
        // int mincnt = dfs(a, 0, 0, 1);
        // cerr << mincnt << endl;
        // ans += mincnt;

        vector<vector<double>> A(sz(a), vd(sz(b), 0));
        vd B(sz(a), 0);
        rep(j, 0, sz(a)) B[j] = a[j];
        for (int j = 0; j < sz(b); j++) {
            for (auto t : b[j])
                A[t][j] = 1;
        }
        // cerr<<"A:"<<endl;for (auto xx : A) {for(auto t : xx) cerr << t << " "; cerr << endl;}
        // cerr<<"B:"<<endl;for (auto xx : B) {cerr << xx << " ";} cerr << endl;
        vd X(sz(b), 0);
        solveLinear2(A, B, X);
        vector<int> unsolvedIdx = {};
        vector<pair<int, int>> solved = {};
        // cerr<<"X: ";for (int t = 0; t < sz(X); t++) cerr << X[t] << " "; cerr << endl;
        int curpresses = 0;
        for (int t = 0; t < sz(X); t++)
            if (X[t] == -123) {
                unsolvedIdx.push_back(t);
            } else {
                assert(abs(X[t] - floor(X[t] + 0.5)) < 0.0001);
                solved.push_back({t, (int)(X[t] + 0.5)});
                curpresses += (int)(X[t] + 0.5);
            }
        for (auto [x, y] : solved) {
            for (auto t : b[x])
                a[t] -= y;
        }
        globalBest = 1e5;
        dfs(unsolvedIdx, a, 0, 0);
        int curTotal = globalBest + curpresses;
        ans += curTotal;
    }
    
    cout << "answer = " << ans << endl;
}