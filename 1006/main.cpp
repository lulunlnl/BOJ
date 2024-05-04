#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n, w; cin >> n >> w;
        vector<array<int, 2>> arr(n);
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(4, vector<int>(4, -1)));
        for (int i = 0; i < 2 * n; i++) {
            cin >> arr[i % n][i / n];
        }
        auto solve = [&](auto self, int now, int prev, int last) {
            int &ret = dp[now][prev][last];
            if (ret != -1) return ret;

            int in = (arr[(now - 1 + n) % n][0] + arr[now][0] <= w);
            int out = (arr[(now - 1 + n) % n][1] + arr[now][1] <= w);
            int all = (arr[now][0] + arr[now][1] <= w);
            if (now == n - 1) {
                if (n == 1) return 2 - all;
                ret = 2;
                if (last == 0) {
                    if (in && !(prev & 1)) ret = 1;
                    if (out && prev < 2) ret = 1;
                    if (all) ret = 1;
                    if (in && out && !prev) ret = 0;
                }
                else if (last == 1) {
                    if (out && prev < 2) ret = 1;
                }
                else if (last == 2) {
                    if (in && !(prev & 1)) ret = 1;
                }
                return ret;
            }
            ret = self(self, now + 1, 0, now ? last : 0) + 2;
            if (in && !(prev & 1)) ret = min(ret, self(self, now + 1, 1, now ? last : 1) + 1);
            if (out && (prev < 2)) ret = min(ret, self(self, now + 1, 2, now ? last : 2) + 1);
            if (all) ret = min(ret, self(self, now + 1, 3, now ? last : 0) + 1);
            if (in && out && !prev) ret = min(ret, self(self, now + 1, 3, now ? last : 3));
            return ret;
        };
        cout << solve(solve, 0, 0, 0) << "\n";
    }
}