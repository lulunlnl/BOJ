#include "bits/stdc++.h"
using namespace std;
int ans = 0, N;
int arr[25][25];

void dfs(int cur) {
    if (cur == 5) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ans = max(ans, arr[i][j]);
            }
        }
        return;
    }
    int tmp[25][25] = {};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tmp[i][j] = arr[i][j];
        }
    }
    vector<vector<bool>> chk(N, vector<bool>(N, false));
    for (int t = 1; t <= 4; t++) {
        if (t == 1) {
            for (int i = 0; i < N; i++) {
                for (int j = 1; j < N; j++) {
                    if (!arr[i][j]) continue;
                    for (int k = j-1; k >= 0; k--) {
                        if (arr[i][k] == arr[i][k+1] && !chk[i][k]) {
                            arr[i][k] *= 2;
                            arr[i][k+1] = 0;
                            chk[i][k] = 1;
                        }
                    }
                }
            }
        }
        else if (t == 2) {
            for (int i = 0; i < N; i++) {
                vector<int> row;
                int cnt = 0;
                for (int j = 0; j < N; j++) {
                    if (arr[i][j]) row.push_back(arr[i][j]);
                }
                reverse(row.begin(), row.end());
                for (int j = 1; j < row.size(); j++) {
                    if (row[j - 1] == row[j]) {
                        arr[i][N-1-cnt] = 2 * row[j];
                        cnt++;
                        j++;
                    } else {
                        arr[i][N-1-cnt] = row[j - 1];
                        cnt++;
                        if (j == row.size() - 1) arr[i][N-1-cnt] = row.back();
                    }
                }
                for (int j = N-2-cnt; j >= 0; j--) arr[i][j] = 0;
            }
        }
        else if (t == 3) {
            for (int i = 0; i < N; i++) {
                vector<int> row;
                int cnt = 0;
                for (int j = 0; j < N; j++) {
                    if (arr[j][i]) row.push_back(arr[j][i]);
                }
                for (int j = 1; j < row.size(); j++) {
                    if (row[j - 1] == row[j]) {
                        arr[cnt][i] = 2 * row[j];
                        cnt++;
                        j++;
                    } else {
                        arr[cnt][i] = row[j - 1];
                        cnt++;
                        if (j == row.size() - 1) arr[cnt][i] = row.back();
                    }
                }
                for (int j = cnt + 1; j < N; j++) arr[j][i] = 0;
            }
        }
        else {
            for (int i = 0; i < N; i++) {
                vector<int> row;
                int cnt = 0;
                for (int j = 0; j < N; j++) {
                    if (arr[j][i]) row.push_back(arr[j][i]);
                }
                reverse(row.begin(), row.end());
                for (int j = 1; j < row.size(); j++) {
                    if (row[j - 1] == row[j]) {
                        arr[N-1-cnt][i] = 2 * row[j];
                        cnt++;
                        j++;
                    } else {
                        arr[N-1-cnt][i] = row[j - 1];
                        cnt++;
                        if (j == row.size() - 1) arr[N-1-cnt][i] = row.back();
                    }
                }
                for (int j = N-2-cnt; j >= 0; j--) arr[j][i] = 0;
            }
        }
    }
    dfs(cur+1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = tmp[i][j];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    dfs(0);
    cout << ans << "\n";
}