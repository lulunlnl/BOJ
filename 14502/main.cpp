#include "bits/stdc++.h"
#define ft first
#define sd second
using namespace std;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int arr[10][10];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    vector<pair<int, int>> v;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
            if (!arr[i][j]) v.push_back({i, j});
        }
    }
    int ret = 0;
    for (int i = 0; i < v.size(); i++) for (int j = i + 1; j < v.size(); j++) for (int k = j + 1; k < v.size(); k++) {
        arr[v[i].ft][v[i].sd] = arr[v[j].ft][v[j].sd] = arr[v[k].ft][v[k].sd] = 1;
        int chk[10][10] = {};
        int now = 0;
        auto dfs = [&](auto&& self, int x, int y) -> void {
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= N || ny < 0 || ny >= M || arr[nx][ny] != 0) continue;
                if (chk[nx][ny]) continue;
                chk[nx][ny] = 1;
                self(self, nx, ny);
            }
        };
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < M; y++) {
                if (arr[x][y] == 2) dfs(dfs, x, y);
            }
        }
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < M; y++) {
                if (!arr[x][y] && !chk[x][y]) now++;
            }
        }
        ret = max(ret, now);
        arr[v[i].ft][v[i].sd] = arr[v[j].ft][v[j].sd] = arr[v[k].ft][v[k].sd] = 0;
    }
    cout << ret << "\n";
}