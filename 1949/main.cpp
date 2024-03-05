#include "bits/stdc++.h"
using namespace std;
int dp[10005][2], cost[10005];
vector<int> adj[10005], g[10005];

void make_tree(int v, int par) {
    for (auto next: adj[v]) {
        if (next != par) {
            g[v].push_back(next);
            make_tree(next, v);
        }
    }
}

void dfs(int v) {
    dp[v][1] = cost[v];
    for (auto next: g[v]) {
        dfs(next);
        dp[v][0] += max(dp[next][0], dp[next][1]);
        dp[v][1] += dp[next][0];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    for (int i = 1; i <= N; i++) cin >> cost[i];
    for (int i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    make_tree(1, 0);
    dfs(1);
    cout << max(dp[1][0], dp[1][1]) << "\n";
}