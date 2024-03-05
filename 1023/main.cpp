#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll dp[55][26];
// dp[i][j]: i번째까지 봤을 때 합 j

ll f(int n, int s) {
    if (n == 0) return s == 0;
    ll &ret = dp[n][s];
    if (ret != -1) return ret;
    ret = f(n-1, s+1);
    if (s != 0) ret += f(n-1, s-1);
    return ret;
}

void solve(ll n, ll k, int s, int chk) {
    if (n == 0) return;
    ll cnt = (1ll << (n-1)) - f(n-1, s+1) * chk;
    if (k < cnt) {
        cout << '(';
        solve(n-1, k, s+1, chk);
    }
    else {
        cout << ')';
        solve(n-1, k-cnt, s-1, chk & (s != 0));
    }
}

int main() {
    ll N, K; cin >> N >> K;
    memset(dp, -1, sizeof dp);
    if (K >= (1ll << N) - f(N, 0)) {
        cout << "-1\n";
        return 0;
    }
    solve(N, K, 0, 1);
}