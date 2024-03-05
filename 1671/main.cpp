#include "bits/stdc++.h"
using namespace std;
vector<int> g[255];
vector<int> par(255, -1);
bool chk[255];

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
    int N; cin >> N;
    vector<array<int, 3>> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (v[i][1] <= v[j][1] && v[i][2] <= v[j][2]) {
                g[j].push_back(i + 50);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        memset(chk, 0, sizeof chk);
        match(i);
        memset(chk, 0, sizeof chk);
        match(i);
    }
    int ans = 0;
    for (int i = 50; i < N + 50; i++) {
        ans += (par[i] == -1);
    }
    cout << ans << "\n";
}