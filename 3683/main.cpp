#include "bits/stdc++.h"
using namespace std;

void solve() {
    int c, d, v; cin >> c >> d >> v;
    vector<pair<int, int>> cat, dog;
    for (int i = 0; i < v; i++) {
        string a, b; cin >> a >> b;
        int x = stoi(a.substr(1)), y = stoi(b.substr(1));
        if (a[0] == 'C') cat.push_back({x, y});
        else dog.push_back({x, y});
    }
    vector<vector<int>> g(700);
    vector<int> par(700, -1);
    vector<bool> chk(700, 0);
    for (int i = 0; i < cat.size(); i++) {
        for (int j = 0; j < dog.size(); j++) {
            if (cat[i].first == dog[j].second || cat[i].second == dog[j].first) {
                g[i].push_back(j+100);
            }
        }
    }
    auto match = [&](auto&& self, int v) -> int {
        for (auto i: g[v]) {
            if (chk[i]) continue;
            chk[i] = 1;
            if (par[i] == -1 || self(self, par[i])) {
                par[i] = v;
                return 1;
            }
        }
        return 0;
    };
    int ans = 0;
    for (int i = 0; i < cat.size(); i++) {
        fill(chk.begin(), chk.end(), 0);
        ans += match(match, i);
    }
    cout << v - ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}