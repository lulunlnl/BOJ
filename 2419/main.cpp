#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    int pos = lower_bound(a.begin(), a.end(), 0) - a.begin();
    for (int i = 1; i <= N; i++) {
        vector dp(N, vector(N, 1e9));
        // dp[l][r]
        auto dfs = [&](auto&& self, int l, int r, int k) -> int {
            if (k == 0)
        };
    }
}