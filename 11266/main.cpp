#include "bits/stdc++.h"
using namespace std;
vector<int> adj[10005];
int num[10005], low[10005], par[10005], ans[10005];
int pv;

void dfs(int v) {
    num[v] = ++pv;
    low[v] = pv;
    int child = 0;
    for (auto i: adj[v]) {
        if (i == par[v]) continue;
        if (!num[i]) {
            par[i] = v; child++;
            dfs(i);
            if (!par[v] && child > 1) ans[v] = 1;
            else if (par[v] && low[i] >= num[v]) ans[v] = 1;
            low[v] = min(low[v], low[i]);
        }
        else low[v] = min(low[v], num[i]);
    }
}

int main() {
    int V, E; cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= V; i++) {
        if (!num[i]) dfs(i);
    }
    int cnt = 0;
    for (int i = 1; i <= V; i++) {
        if (ans[i]) cnt++;
    }
    cout << cnt << "\n";
    for (int i = 1; i <= V; i++) {
        if (ans[i]) cout << i << " ";
    }
}