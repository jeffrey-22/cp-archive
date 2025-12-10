// give up on seg tree beats implementation

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int n, k;
ll a[200009], b[200009];
int p, q;
ll s, d, a1;

struct Node {
	ll sum;   // Sum tag
	ll max1;  // Max value
	ll max2;  // Second Max value
	ll maxc;  // Max value count
	ll min1;  // Min value
	ll min2;  // Second Min value
	ll minc;  // Min value count
	ll lazy;  // Lazy tag
} T[200009 * 4];
const ll inf = 4e18;

void merge(int t) {
	// sum
	T[t].sum = T[t << 1].sum + T[t << 1 | 1].sum;

	// max
	if (T[t << 1].max1 == T[t << 1 | 1].max1) {
		T[t].max1 = T[t << 1].max1;
		T[t].max2 = max(T[t << 1].max2, T[t << 1 | 1].max2);
		T[t].maxc = T[t << 1].maxc + T[t << 1 | 1].maxc;
	} else {
		if (T[t << 1].max1 > T[t << 1 | 1].max1) {
			T[t].max1 = T[t << 1].max1;
			T[t].max2 = max(T[t << 1].max2, T[t << 1 | 1].max1);
			T[t].maxc = T[t << 1].maxc;
		} else {
			T[t].max1 = T[t << 1 | 1].max1;
			T[t].max2 = max(T[t << 1].max1, T[t << 1 | 1].max2);
			T[t].maxc = T[t << 1 | 1].maxc;
		}
	}

	// min
	if (T[t << 1].min1 == T[t << 1 | 1].min1) {
		T[t].min1 = T[t << 1].min1;
		T[t].min2 = min(T[t << 1].min2, T[t << 1 | 1].min2);
		T[t].minc = T[t << 1].minc + T[t << 1 | 1].minc;
	} else {
		if (T[t << 1].min1 < T[t << 1 | 1].min1) {
			T[t].min1 = T[t << 1].min1;
			T[t].min2 = min(T[t << 1].min2, T[t << 1 | 1].min1);
			T[t].minc = T[t << 1].minc;
		} else {
			T[t].min1 = T[t << 1 | 1].min1;
			T[t].min2 = min(T[t << 1].min1, T[t << 1 | 1].min2);
			T[t].minc = T[t << 1 | 1].minc;
		}
	}
}

void push_add(int t, int tl, int tr, ll v) {
	if (v == 0) { return; }
	T[t].sum += (tr - tl + 1) * v;
	T[t].max1 += v;
	if (T[t].max2 != -inf) { T[t].max2 += v; }
	T[t].min1 += v;
	if (T[t].min2 != inf) { T[t].min2 += v; }
	T[t].lazy += v;
}

// corresponds to a chmin update
void push_max(int t, ll v, bool l) {
	if (v >= T[t].max1) { return; }
	T[t].sum -= T[t].max1 * T[t].maxc;
	T[t].max1 = v;
	T[t].sum += T[t].max1 * T[t].maxc;
	if (l) {
		T[t].min1 = T[t].max1;
	} else {
		if (v <= T[t].min1) {
			T[t].min1 = v;
		} else if (v < T[t].min2) {
			T[t].min2 = v;
		}
	}
}

// corresponds to a chmax update
void push_min(int t, ll v, bool l) {
	if (v <= T[t].min1) { return; }
	T[t].sum -= T[t].min1 * T[t].minc;
	T[t].min1 = v;
	T[t].sum += T[t].min1 * T[t].minc;
	if (l) {
		T[t].max1 = T[t].min1;
	} else {
		if (v >= T[t].max1) {
			T[t].max1 = v;
		} else if (v > T[t].max2) {
			T[t].max2 = v;
		}
	}
}

void pushdown(int t, int tl, int tr) {
	if (tl == tr) return;
	// sum
	int tm = (tl + tr) >> 1;
	push_add(t << 1, tl, tm, T[t].lazy);
	push_add(t << 1 | 1, tm + 1, tr, T[t].lazy);
	T[t].lazy = 0;

	// max
	push_max(t << 1, T[t].max1, tl == tm);
	push_max(t << 1 | 1, T[t].max1, tm + 1 == tr);

	// min
	push_min(t << 1, T[t].min1, tl == tm);
	push_min(t << 1 | 1, T[t].min1, tm + 1 == tr);
}

void build(int t, int tl, int tr) {
	T[t].lazy = 0;
	if (tl == tr) {
		T[t].sum = T[t].max1 = T[t].min1 = min(b[tl], 0ll);
		T[t].maxc = T[t].minc = 1;
		T[t].max2 = -inf;
		T[t].min2 = inf;
		return;
	}

	int tm = (tl + tr) >> 1;
	build(t << 1, tl, tm);
	build(t << 1 | 1, tm + 1, tr);
	merge(t);
}

void update_add(int l, int r, ll v, int t, int tl, int tr) {
	if (r < tl || tr < l) { return; }
	if (l <= tl && tr <= r) {
		push_add(t, tl, tr, v);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_add(l, r, v, t << 1, tl, tm);
	update_add(l, r, v, t << 1 | 1, tm + 1, tr);
	merge(t);
}

void update_chmin(int l, int r, ll v, int t, int tl, int tr) {
	if (r < tl || tr < l || v >= T[t].max1) { return; }
	if (l <= tl && tr <= r && v > T[t].max2) {
		push_max(t, v, tl == tr);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_chmin(l, r, v, t << 1, tl, tm);
	update_chmin(l, r, v, t << 1 | 1, tm + 1, tr);
	merge(t);
}

void update_chmax(int l, int r, ll v, int t, int tl, int tr) {
	if (r < tl || tr < l || v <= T[t].min1) { return; }
	if (l <= tl && tr <= r && v < T[t].min2) {
		push_min(t, v, tl == tr);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_chmax(l, r, v, t << 1, tl, tm);
	update_chmax(l, r, v, t << 1 | 1, tm + 1, tr);
	merge(t);
}

ll query_sum(int l, int r, int t, int tl, int tr) {
	if (r < tl || tr < l) { return 0; }
	if (l <= tl && tr <= r) { return T[t].sum; }
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	return query_sum(l, r, t << 1, tl, tm) + query_sum(l, r, t << 1 | 1, tm + 1, tr);
}

void print_ok() {
	ll q_sum = query_sum(1, n, 1, 1, n);
	cerr << "qsum = " << q_sum << "  vs  -a1 = " << -a1 << endl;
    if (q_sum < -a1)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int Tt;
    cin >> Tt;
    while (Tt--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        a1 = a[1]; a[1] = 0; b[1] = 0;
        for (int i = 2; i <= n; i++)
            b[i] = a[i] - a[i - 1];
        build(1, 1, n);
        print_ok();
        while (k--) {
            int p, q; ll s, d;
            cin >> p >> q >> s >> d;
            if (p == 1) {
                a1 += s;
                s += d; p++;
                if (p > q) continue;
            }
            update_add(p, p, s, 1, 1, n);
            if (p + 1 <= q) {
                update_add(p + 1, q, d, 1, 1, n);
			}
            if (q + 1 <= n) {
            	point_add(q + 1, q + 1, -s-d * (q - p), 1, 1, n);
			}
			update_chmin(1, n, 0, 1, 1, n);
            print_ok();
        }
    }
    return 0;
}
/*
b[i] = a[i] - a[i - 1] or a[1]

ci := di | di < 0, otherwise 0
cis are initially non-positive integers
query for sum(ci)
range plus: for i in [l, r], ci := min(ci + positive_value, 0)
point set ci := negative_value

sum(ci) < -a1

dp += s, d(p+1...q) += d, d(q+1) += -s-(q-p)d

5  8  5  2  4
0  0 -3 -3  0
0  0 -3 -3  0
  +2 +3 +3 -7
0  2  0  0 -7
0  0  0  0 -7

5 3 -3 -3 2

*/