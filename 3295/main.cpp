#include "bits/stdc++.h"
using namespace std;

void solve() {
    int N, M; cin >> N >> M;
    vector<vector<int>> g(N);
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b + 1000);
    }
    vector<int> par(2005, -1);
    vector<bool> chk(2005, 0);
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
    for (int i = 0; i < N; i++) {
        fill(chk.begin(), chk.end(), 0);
        if (match(match, i)) ans++;
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}