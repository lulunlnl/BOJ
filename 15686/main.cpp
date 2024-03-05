#include "bits/stdc++.h"
using namespace std;
int N, M, chk[14], ans = 1e9;
vector<pair<int, int>> house, chick;

void dfs(int cur, int t) {
    if (cur == M) {
        int ret = 0;
        for (auto [x, y]: house) {
            int tmp = 1e9;
            for (int i = 0; i < chick.size(); i++) {
                if (chk[i]) {
                    int a = chick[i].first, b = chick[i].second;
                    tmp = min(tmp, abs(x-a) + abs(y-b));
                }
            }
            ret += tmp;
        }
        ans = min(ans, ret);
        return;
    }
    for (int i = t; i < chick.size(); i++) {
        if (chick.size() - i < M - cur) return;
        chk[i] = 1;
        dfs(cur+1, i+1);
        chk[i] = 0;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x; cin >> x;
            if (x == 1) house.push_back({i, j});
            else if (x == 2) chick.push_back({i, j});
        }
    }
    dfs(0, 0);
    cout << ans << "\n";
}