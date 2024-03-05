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
    int T; cin >> T;
    // CX = 1 (mod K)
    while (T--) {
        ll K, C; cin >> K >> C;
        if (K == 1 && C == 1) cout << "2\n";
        else if (C == 1) {
            if (K + 1 > 1e9) cout << "IMPOSSIBLE\n";
            else cout << K+1 << "\n";
        }
        else if (K == 1) cout << "1\n";
        else {
            ll ret = inv(C, K);
            if (ret == -1) cout << "IMPOSSIBLE\n";
            else cout << ret << "\n";
        }
    }
}