#include <bits/stdc++.h>
using namespace std;
long double eps = 1e-7;

struct line {
    mutable long double m, k, p;
    mutable int id;
    bool operator<(const line& o) const { return m < o.m; }
    bool operator<(const long double& x) const { return p < x; }
};

struct CHT : multiset<line, less<>> {
    const long double inf = numeric_limits<long double>::max();
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (abs(x->m - y->m) < eps) x->p = (x->k > y->k) ? inf : -inf;
        else x->p = (x->k - y->k) / (y->m - x->m);
        return x->p >= y->p;
    }
    void add(long double m, long double k, int id) {
        auto z = insert({m, k}); z->id = id;
        auto y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x->p) >= (y->p)) isect(x, erase(y));
    }
    long double query(long double x) {
        auto l = *lower_bound(x);
        return l.id;
    }
} cht;

int main() {
    long double ymx, ymn; cin >> ymx >> ymn;
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        long double a, b; cin >> a >> b;
        long double m = (a - b) / (ymx - ymn);
        cht.add(-m, -b + m * ymn, i);
    }
    int m; cin >> m;
    while (m--) {
        long double x; cin >> x;
        cout << cht.query(x) << "\n";
    }
}