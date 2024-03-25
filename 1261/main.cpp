#include "bits/stdc++.h"
using namespace std;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> m >> n;
    vector<vector<int>> arr(n, vector<int>(m)), dist(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            arr[i][j] = c - '0';
            dist[i][j] = 1e9;
        }
    }
    dist[0][0] = 0;
    deque<pair<int, int>> DQ;
    DQ.push_back({0, 0});
    while (!DQ.empty()) {
        auto [i, j] = DQ.front(); DQ.pop_front();
        for (int k = 0; k < 4; k++) {
            int x = i + dx[k], y = j + dy[k];
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            if (dist[x][y] > dist[i][j] + arr[x][y]) {
                dist[x][y] = dist[i][j] + arr[x][y];
                if (arr[x][y]) DQ.push_back({x, y});
                else DQ.push_front({x, y});
            }
        }
    }
    cout << dist[n-1][m-1] << "\n";
}