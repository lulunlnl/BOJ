#include "bits/stdc++.h"
using namespace std;
int arr[800][800], dp[800][800];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C; cin >> R >> C;
    for (int i = 0; i < R; i++) {
        string S; cin >> S;
        for (int j = 0; j < C; j++) {
            arr[i][j] = S[j] - '0';
        }
    }
    // 대각선 누적합 구현하면 끝
}