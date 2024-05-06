#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (auto next: g[i]) {
            if (next < i) continue;
            int a = i, b = next;
            if (g[a].size() > g[b].size()) swap(a, b);
            for (auto e: g[a]) {
                ans += binary_search(g[b].begin(), g[b].end(), e);
            }
        }
    }
    cout << ans / 3 << "\n";
}