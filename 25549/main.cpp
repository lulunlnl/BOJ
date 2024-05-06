#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int> v(n + 1);
    int root;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        if (x != -1) g[x].push_back(i);
        else root = i;
    }
    vector<set<int>> s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        s[i].insert(v[i]);
    }
    vector<int> ans(n + 1);
    auto dfs = [&](auto self, int now) -> int {
        int &ret = ans[now];
        for (auto next: g[now]) {
            ret = max(ret, self(self, next));
            if (s[now].size() < s[next].size()) swap(s[now], s[next]);
            for (auto x: s[next]) s[now].insert(x);
            s[next].clear();
        }
        for (auto it = s[now].find(ret); it != s[now].end() && *it == ret; it++) ret++;
        return ret;
    };
    dfs(dfs, root);
    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
}