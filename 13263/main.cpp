#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct line {
    mutable ll m, k, p;
    bool operator<(const line &o) const { return m < o.m; }

    bool operator<(ll x) const { return p < x; }
};

struct CHT : multiset<line, less<>> { // upper hull
    const static ll inf = LLONG_MAX;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->m == y->m) x->p = x->k > y->k ? inf : -inf;
        else x->p = div(y->k - x->k, x->m - y->m);
        return x->p >= y->p;
    }
    void add(ll m, ll k) { // add y = mx + k
        auto z = insert({m, k}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    ll query(ll x) {
        auto l = *lower_bound(x);
        return l.m * x + l.k;
    }
} cht;


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    ll dp = 0;
    for (int i = 1; i < n; i++) {
        cht.add(-b[i - 1], -dp);
        dp = -cht.query(a[i]);
    }
    cout << dp << "\n";
}