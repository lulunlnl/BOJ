#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll phi(ll x) {
    ll ret = 1;
    for (ll i = 2; i * i <= x; i++) {
        ll k = 1;
        while (x % i == 0) {
            k *= i;
            x /= i;
        }
        if (k != 1) {
            ret *= k - k / i;
            ret %= MOD;
        }
    }
    if (x != 1) ret *= x - 1;
    ret %= MOD;

    return ret;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        ll ret = 1;
        for (int i = 0; i < n; i++) {
            ll x; cin >> x;
            ret *= phi(x); ret %= MOD;
        }
        cout << ret << "\n";
    }
}