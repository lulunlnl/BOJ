#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<vector<int>> arr(N, vector<int>(N));
    vector<pair<int, int>> w, b;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
            if (arr[i][j]) {
                if ((i+j)%2 == 1) w.push_back({i, j});
                else b.push_back({i, j});
            }
        }
    }
    vector<pair<int, int>> tmp;
    auto chk = [&](auto x) {
        for (int i = 0; i < tmp.size(); i++) {
            if (abs(tmp[i].first - x.first) == abs(tmp[i].second - x.second)) return 0;
        }
        return 1;
    };
    int ans[2] = {};
    auto solve = [&](auto self, vector<pair<int, int>>& v, int now, int cnt, int k) -> void {
        if (now == v.size()) {
            ans[k] = max(ans[k], cnt);
            return;
        }
        if (chk(v[now])) {
            tmp.push_back(v[now]);
            self(self, v, now+1, cnt+1, k);
            tmp.pop_back();
        }
        self(self, v, now+1, cnt, k);
    };
    solve(solve, w, 0, 0, 0);
    solve(solve, b, 0, 0, 1);
    cout << ans[0] + ans[1] << "\n";
}