#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;

ll Pow(ll a, ll b) {
    if (!b) return 1;
    ll ret = Pow(a, b/2);
    if (b & 1) return a * ret % MOD * ret % MOD;
    return ret * ret % MOD;
}

int main() {
    int M; cin >> M;
    ll N, S, ret = 0;
    for (int i = 0; i < M; i++) {
        cin >> N >> S;
        ret += S * Pow(N, MOD-2) % MOD;
        ret %= MOD;
    }
    cout << ret << "\n";
}