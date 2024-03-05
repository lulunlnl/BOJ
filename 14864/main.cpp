#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#ifdef ONLINE_JUDGE
#define debug(x)
#else
#define debug(x) cout << "[Debug] " << #x << ": " << x << '\n'
#define debug2(x, y) cout << "[Debug] " << #x << ": " << x << ", " << #y << ": " << y << '\n';
#endif

int dp[800000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    vector<int> cnt(N+1, 0);
    for (int i = 1; i <= N; i++) cnt[i] = i;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        cnt[a]++; cnt[b]--;
    }
    vector<int> p(N+1, 0);
    for (int i = 1; i <= N; i++) {
        if (p[cnt[i]]) {
            cout << "-1\n";
            return 0;
        }
        p[cnt[i]] = 1;
    }
    for (int i = 1; i <= N; i++) cout << cnt[i] << " ";
}