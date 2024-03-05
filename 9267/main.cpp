#include "bits/stdc++.h"
#define ll __int128
using namespace std;

ll _gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a < b) swap(a, b);
    return b ? _gcd(b, a % b) : a;
}

ll mod(ll a, ll b) {
    a %= b; return (a >= 0) ? a : a + b;
}

tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x, y] = ext_gcd(b, a % b);
    return {g, y, x - a/b * y};
}

ll inv(ll a, ll n) {
    auto [g, x, y] = ext_gcd(a, n);
    if (a == 0 || g != 1) return -1;
    return mod(x, n);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    long long a, b, s; cin >> a >> b >> s;
    ll A, B, S; A = a, B = b, S = s;
    if (A > B) swap(A, B);
    if (A == 0 && B == 0) {
        if (S != 0) cout << "NO\n";
        else cout << "YES\n";
        return 0;
    }
    if (A == 0) {
        if (S % B == 0) cout << "YES\n";
        else cout << "NO\n";
        return 0;
    }
    ll g = _gcd(A, B);
    if (S % g != 0) {
        cout << "NO\n"; return 0;
    }
    A /= g; B /= g; S /= g;
    ll c = inv(A, B);
    if (c == -1) {
        cout << "NO\n"; return 0;
    }
    ll x = inv(A, B) * S % B;
    ll y = (S - A*x) / B;
    if (y < 0) {
        cout << "NO\n"; return 0;
    }
    while (_gcd(x, y) != 1 && y >= 0) {
        x += B; y -= A;
    }
    if (y < 0) cout << "NO\n";
    else cout << "YES\n";
}