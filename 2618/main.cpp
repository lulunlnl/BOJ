#include "bits/stdc++.h"
#define ft first
#define sd second
using namespace std;
typedef pair<int, int> P;
int N, W;
int dp[1005][1005];
P pos[1005], trace[1005][1005];

int dist(P a, P b) {
    return abs(a.ft-b.ft) + abs(a.sd-b.sd);
}

int solve(int x, int y) {
    if (x == W+1 || y == W+1) return 0;
    int &ret = dp[x][y];
    if (ret != -1) return ret;
    int k = max(x, y) + 1;
    ret = solve(k, y) + dist(pos[k], pos[x]);
    int tmp = solve(x, k) + dist(pos[y], pos[k]);
    if (tmp < ret) {
        ret = tmp;
        trace[x][y] = {x, k};
    }
    else trace[x][y] = {k, y};
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> W;
    memset(dp, -1, sizeof dp);
    pos[0] = {1, 1}; pos[1] = {N, N};
    for (int i = 2; i < W+2; i++) {
        cin >> pos[i].ft >> pos[i].sd;
    }
    int ans = solve(0, 1);
    cout << ans << "\n";
    int x = 0, y = 1;
    for (int i = 2; i < W+2; i++) {
        P nxt = trace[x][y];
        if (nxt.ft == x) cout << "2\n";
        else cout << "1\n";
        x = nxt.ft, y = nxt.sd;
    }
}