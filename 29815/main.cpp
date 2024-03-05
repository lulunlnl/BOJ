#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;
ll fac[2000005], inv[2000005];

ll Pow(ll a, ll b) {
    if (b == 0) return 1;
    ll ret = Pow(a, b/2);
    if (b & 1) return a*ret%MOD*ret%MOD;
    return ret*ret%MOD;
}

void prepare(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i-1] * i % MOD;
    inv[n] = Pow(fac[n], MOD-2);
    for (int i = n-1; i >= 0; i--) inv[i] = inv[i+1] * (i+1) % MOD;
}

ll ncr(int n, int r) {
    return fac[n]*inv[r]%MOD*inv[n-r]%MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll A, B, N;
    cin >> A >> B >> N;
    prepare(N+3);
    int T; cin >> T;
    while (T--) {
        int R, C; cin >> R >> C;
        R = N-R; C--;
        ll ans = (A + B*N) % MOD * ncr(R, C) % MOD;
        ans -= (ncr(R+2, C+1) - ncr(R, C) + MOD) % MOD * B % MOD;
        ans = (ans + MOD) % MOD;
        cout << ans << "\n";
    }
}