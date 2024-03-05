#include "bits/stdc++.h"
using namespace std;
int num[100005], low[100005], par[100005];
vector<int> adj[100005];
vector<pair<int, int>> ans;
int pv;

void dfs(int v) {
    num[v] = ++pv;
    low[v] = pv;
    for (auto i: adj[v]) {
        if (i == par[v]) continue;
        if (!num[i]) {
            par[i] = v;
            dfs(i);
            if (low[i] > num[v]) ans.push_back({min(v, i), max(v, i)});
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
    dfs(1);
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto &[a, b]: ans) {
        cout << a << " " << b << "\n";
    }
}