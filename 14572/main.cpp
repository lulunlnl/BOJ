#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int main() {
    int n, k, D; cin >> n >> k >> D;
    vector<pii> arr(n);
    for (int i = 0; i < n; i++) {
        int m, d; cin >> m >> d;
        int state = 0;
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            state |= (1 << x);
        }
        arr[i] = {d, state};
    }
    sort(arr.begin(), arr.end());
    int ans = 0;
    int l = 0, r = 0;
    int m, M;
    vector<int> state(32);
    for (int i = 1; i <= 30; i++) {
        if ((1 << i) & arr[0].second) {
            state[i]++;
        }
    }
    while (l <= r) {
        if (l == n - 1) break;
        if (r == n || arr[r].first - arr[l].first > D) {
            for (int i = 1; i <= 30; i++) {
                if ((1 << i) & arr[l].second) {
                    state[i]--;
                }
            }
            l++;
        }
        else {
            M = m = 0;
            for (int i = 1; i <= 30; i++) {
                if (state[i] == r - l + 1) m++;
                if (state[i] > 0) M++;
            }
            ans = max(ans, (r - l + 1) * (M - m));
            r++;
            for (int i = 1; i <= 30; i++) {
                if ((1 << i) & arr[r].second) {
                    state[i]++;
                }
            }
        }
    }
    cout << ans << "\n";
}