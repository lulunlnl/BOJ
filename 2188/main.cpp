#include "bits/stdc++.h"
using namespace std;
vector<int> g[405];
vector<int> par(405, -1);
bool chk[405];

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
    for (int i = 0; i < N; i++) {
        int t; cin >> t;
        while (t--) {
            int x; cin >> x;
            x += 200;
            g[i].push_back(x);
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        memset(chk, 0, sizeof chk);
        if (match(i)) ans++;
    }
    cout << ans << "\n";
}