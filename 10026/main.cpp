#include "bits/stdc++.h"
using namespace std;
int N;
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int arr[105][105], chk[205][205];

void dfs(int x, int y, int c) {
    chk[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (!chk[nx][ny] && arr[nx][ny] == c) dfs(nx, ny, c);
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char c; cin >> c;
            arr[i][j] = c == 'B' ? 0 : c == 'R' ? 1 : 2;
        }
    }
    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!chk[i][j]) {
                dfs(i, j, arr[i][j]); ans1++;
            }
        }
    }
    memset(chk, 0, sizeof chk);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j] == 2) arr[i][j] = 1;
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            if (!chk[i][j]) {
                dfs(i, j, arr[i][j]); ans2++;
            }
        }
    }
    cout << ans1 << " " << ans2 << "\n";
}