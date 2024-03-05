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
    int W, N; cin >> W >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    sort(a.begin(), a.end());
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int x = a[i] + a[j];
            if (W < x) continue;
            if (dp[W-x] && dp[W-x] < i) {
                cout << "YES\n";
                return 0;
            }
            if (!dp[x]) dp[x] = j;
            else dp[x] = min(j, dp[x]);
        }
    }
    cout << "NO\n";
}