#include "bits/stdc++.h"
using namespace std;
int arr[30][30];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C; cin >> R >> C;
    int chk[30] = {};
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            char c; cin >> c;
            arr[i][j] = c - 'A';
        }
    }
    int ret = 0;
    chk[arr[0][0]] = 1;
    auto dfs = [&](auto&& self, int x = 0, int y = 0, int cnt = 1) -> void {
        ret = max(ret, cnt);
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= R || ny < 0 || ny >= C || chk[arr[nx][ny]]) continue;
            chk[arr[nx][ny]] = 1;
            self(self, nx, ny, cnt + 1);
            chk[arr[nx][ny]] = 0;
        }
    };
    dfs(dfs);
    cout << ret << "\n";
}