#include "bits/stdc++.h"
using namespace std;
constexpr int MOD = 1e9 + 7;
#define debug(v) for (const auto& i : v) std::cout << i << ' '; std::cout << '\n'

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    if (a[0] > 0 || a[n-1] > 0) {
        cout << 0; return 0;
    }
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i < n; i++) {
        vector<int> nxt(n + 1);
        for (int j = 0; j < n; j++) {
            for (auto x: {-1, 0, 1}) {
                if (j + x < 0 || (a[i] != -1 && j + x != a[i])) continue;
                nxt[j + x] += dp[j];
                nxt[j + x] %= MOD;
            }
        }
        dp = nxt;
    }
    cout << dp[0] << "\n";
}