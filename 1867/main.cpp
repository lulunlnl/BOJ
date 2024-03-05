#include "bits/stdc++.h"
using namespace std;
vector<int> g[505];
vector<int> par(1005, -1);
bool chk[1005];

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
    int N, K; cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b+500);
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        fill(chk, chk+1005, 0);
        ans += match(i);
    }
    cout << ans << "\n";
}