#include "bits/stdc++.h"
using namespace std;
vector<int> g[205];
vector<int> par(205, -1);
bool chk[205];

int match(int v) {
    for (auto i: g[v]) {
        if (chk[i]) continue;
        chk[i] = 1;
        if (par[i] == -1 || match(par[i])) {
            par[i] = v;
            return 1;
        }
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        b += 100;
        g[a].push_back(b);
    }
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        memset(chk, 0, sizeof chk);
        ans += match(i);
    }
    cout << ans << "\n";
}