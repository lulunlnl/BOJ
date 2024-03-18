#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll dp[105];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 1; i <= 100; i++) {
        if (i < 10) dp[i] = i;
        else if (i < 25) dp[i] = i / 10 + i % 10;
        else dp[i] = min(dp[i-10] + 1, dp[i-25] + 1);
    }
    int T; cin >> T;
    while (T--) {
        ll x; cin >> x;
        ll ans = 0;
        while (x > 0) {
            ans += dp[x % 100];
            x /= 100;
        }
        cout << ans << "\n";
    }
}