#include "bits/stdc++.h"
using namespace std;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int arr[105][105], chk[105][105];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    auto BFS = [&](int m, int M) {
        queue<pair<int, int>> Q;
        Q.push({0, 0});
        chk[0][0] = 1;
        while (!Q.empty()) {
            auto [x, y] = Q.front(); Q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n || chk[nx][ny]) continue;
                if (arr[nx][ny] < m || arr[nx][ny] > M) continue;
                Q.push({nx, ny});
                chk[nx][ny] = 1;
            }
        }
        if (chk[n-1][n-1]) return 1;
        return 0;
    };
    int ans = 1e9;
    for (int i = 0; i <= 200; i++) {
        int l = 0, r = 200;
        while (l <= r) {
            memset(chk, 0, sizeof chk);
            int m = l + r >> 1;
            if (arr[0][0] >= i && arr[0][0] <= i + m && BFS(i, i + m)) {
                r = m - 1;
                ans = min(m, ans);
            } else l = m + 1;
        }
    }
    cout << ans << "\n";
}