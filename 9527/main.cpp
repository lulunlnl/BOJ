#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll F(ll x) {
    ll ret = 0;
    for (int i = 0; i < 60; i++) {
        ret += ((x + 1) >> (i+1) << i);
        ret += max<ll>(0, (x + 1) % (1ll << (i+1)) - (1ll << i));
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll A, B; cin >> A >> B;
    cout << F(B) - F(A-1) << "\n";
}