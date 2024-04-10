#include <bits/stdc++.h>
using namespace std;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int n; cin >> n;
    vector<vector<int>> arr(n, vector<int>(n));
    pair<int, int> now, prv;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 9) now = {i, j};
        }
    }
    prv = {-1, -1};
    int sz = 1, ans = 0;
    while (1) {
        if (now == prv) break;
        queue<pair<int, int>> Q;
        vector<vector<int>> chk(n, vector<int>(n, -1));
        Q.push(now);
        chk[now.first][now.second] = 0;
        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();
            if (arr[cur.first][cur.second] <= sz && arr[cur.first][cur.second] != 0) {
                sz++;
                now = cur;
                ans += chk[cur.first][cur.second];
                break;
            }
            for (int i = 0; i < 4; i++) {
                int nx = now.first + dx[i], ny = now.second + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n || chk[nx][ny] != -1 || arr[nx][ny] <= sz) continue;
                Q.push({nx, ny});
                chk[nx][ny] = chk[now.first][now.second] + 1;
            }
        }
        prv = now;
    }
    cout << ans;
}