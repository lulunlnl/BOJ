#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#ifdef ONLINE_JUDGE
#define debug(x)
#else
#define debug(x) cout << "[Debug] " << #x << ": " << x << '\n'
#define debug2(x, y) cout << "[Debug] " << #x << ": " << x << ", " << #y << ": " << y << '\n';
#endif

const int INF = 1e9;
int ans[305][305][305];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q; cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> ans[i][j][0];
            if (i == j) continue;
            if (!ans[i][j][0]) ans[i][j][0] = INF;
        }
    }
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                ans[i][j][k] = min(ans[i][j][k-1], ans[i][k][k-1] + ans[k][j][k-1]);
            }
        }
    }
    while (Q--) {
        int C, s, e; cin >> C >> s >> e;
        int x = ans[s][e][C-1];
        if (x == INF) cout << "-1\n";
        else cout << x << "\n";
    }
}