#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    vector<vector<bool>> arr(N, vector<bool>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char c; cin >> c;
            arr[i][j] = c - '0';
        }
    }
    int cnt = 0;
    for (int i = N-1; i >= 0; i--) {
        for (int j = M-1; j >= 0; j--) {
            if (arr[i][j]) {
                cnt++;
                for (int k = 0; k <= i; k++) {
                    for (int l = 0; l <= j; l++) {
                        arr[k][l] = 1 - arr[k][l];
                    }
                }
            }
        }
    }
    cout << cnt << "\n";
}