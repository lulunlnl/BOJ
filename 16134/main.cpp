#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int MAX = 1e6+5;
const ll MOD = 1e9+7;
ll fac[MAX], inv[MAX];

ll Pow(ll a, ll b, ll m) {
    if (b == 0) return 1;
    ll ret = Pow(a, b/2, m);
    if (b & 1) return a * ret % m * ret % m;
    return ret * ret % m;
}

void prepare() {
    fac[0] = 1;
    for (int i = 1; i < MAX; i++) fac[i] = fac[i-1] * i % MOD;
    inv[MAX-1] = Pow(fac[MAX-1], MOD-2, MOD);
    for (int i = MAX-2; i >= 0; i--) inv[i] = inv[i+1] * (i+1) % MOD;
}

ll ncr(int n, int r) {
    return fac[n] * inv[r] % MOD * inv[n-r] % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r; cin >> n >> r;
    prepare();
    cout << ncr(n, r) << "\n";
}