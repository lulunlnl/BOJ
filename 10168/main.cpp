#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct line {
    mutable ll m, k, p;
    bool operator<(const line &o) const { return m < o.m; }
    bool operator<(ll x) const { return p < x; }
};

struct CHT : multiset<line, less<>> {
    const static ll inf = LLONG_MAX;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->m == y->m) x->p = x->k > y->k ? inf : -inf;
        else x->p = div(y->k - x->k, x->m - y->m);
        return x->p >= y->p;
    }
    void add(ll m, ll k) {
        auto z = insert({m, k}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= (y->p)) isect(x, erase(y));
    }
    ll query(ll x) {
        auto l = *lower_bound(x);
        return l.m * x + l.k;
    }
};

int main() {
    int n; cin >> n;
    vector<ll> a(n + 2), pSum1(n + 2), pSum2(n + 2), dp1(n + 2), dp2(n + 2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) pSum1[i] = pSum1[i - 1] + a[i];
    for (int i = n; i >= 1; i--) pSum2[i] = pSum2[i + 1] + a[i];

    CHT cht1, cht2;
    for (int i = 1; i <= n; i++) {
        if (!a[i]) {
            dp1[i] = dp1[i - 1];
            continue;
        }
        cht1.add(pSum1[i - 1], -dp1[i - 1]);
        dp1[i] = -cht1.query(i) + (pSum1[i] + 1) * i;
    }
    for (int i = n; i >= 1; i--) {
        if (!a[i]) {
            dp2[i] = dp2[i + 1];
            continue;
        }
        cht2.add(pSum2[i + 1], -dp2[i + 1]);
        dp2[i] = -cht2.query(n - i + 1) + (pSum2[i] + 1) * (n - i + 1);
    }
    ll ans = LLONG_MAX;
    for (int i = 0; i <= n; i++) ans = min(ans, dp1[i] + dp2[i + 1]);
    cout << ans << "\n";
}