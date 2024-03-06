#include "bits/stdc++.h"
using namespace std;
typedef pair<int, int> pii;

void solve() {
    int N, M, W; cin >> N >> M >> W;
    vector<vector<pii>> g(N);
    for (int i = 0; i < M + W; i++) {
        int a, b, T; cin >> a >> b >> T;
        a--; b--;
        if (i < M) {
            g[a].push_back({b, T});
            g[b].push_back({a, T});
        }
        else {
            g[a].push_back({b, -T});
        }
    }
    int flag = 0;
    vector<int> D(N, 1e9);
    D[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (auto next: g[j]) {
                if (D[next.first] > D[j] + next.second) {
                    D[next.first] = D[j] + next.second;
                    if (i == N - 1) flag = 1;
                }
            }
        }
    }
    if (flag) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}