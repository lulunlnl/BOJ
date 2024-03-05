#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll mod(ll a, ll b) {
    a %= b;
    return (a >= 0) ? a : a + b;
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
    ll N, A; cin >> N >> A;
    cout << mod(-A, N) << " " << inv(A, N) << "\n";
}