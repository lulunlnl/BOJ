#include "bits/stdc++.h"
using namespace std;
typedef vector<vector<int>> vvi;
int ans = 0, n;

void rotate(vvi& arr) {
    vvi t = arr;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        arr[i][j] = t[n - 1 - j][i];
    }
}

void dfs(vvi& arr, int cur) {
    if (cur == 5) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans = max(ans, arr[i][j]);
            }
        }
        return;
    }
    vvi t = arr;
    for (int d = 0; d < 4; d++) {
        for (int i = 0; i < d; i++) rotate(arr);
        for (auto& row: arr) {
            vector<int> ret(n);
            for (int i = 0, j = 0, flag = 0; i < n; i++) {
                if (!row[i]) continue;
                else if (flag && row[i] == ret[j - 1]) {
                    ret[j - 1] *= 2;
                    flag = 0;
                }
                else {
                    ret[j++] = row[i];
                    flag = 1;
                }
            }
            row = ret;
        }
        for (int i = 0; i < 4 - d; i++) rotate(arr);
        dfs(arr, cur + 1);
        arr = t;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    vvi arr(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    dfs(arr, 0);
    cout << ans << "\n";
}