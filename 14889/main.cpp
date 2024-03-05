#include "bits/stdc++.h"
using namespace std;
int N, a[25][25], team[25];
int ans = 1e9;

void dfs(int cur, int x) {
    if (cur == N/2) {
        vector<int> t1, t2;
        for (int i = 0; i < N; i++) {
            if (team[i]) t1.push_back(i);
            else t2.push_back(i);
        }
        int ans1 = 0, ans2 = 0;
        for (int i = 0; i < N/2; i++) {
            for (int j = i+1; j < N/2; j++) {
                ans1 += a[t1[i]][t1[j]] + a[t1[j]][t1[i]];
                ans2 += a[t2[i]][t2[j]] + a[t2[j]][t2[i]];
            }
        }
        ans = min(ans, abs(ans1 - ans2));
    }
    for (int i = x; i < N; i++) {
        team[i] = 1;
        dfs(cur+1, i+1);
        team[i] = 0;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a[i][j];
        }
    }
    dfs(0, 0);
    cout << ans << "\n";
}