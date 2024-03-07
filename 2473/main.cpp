#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<ll> v(N);
    for (auto &e: v) cin >> e;
    sort(v.begin(), v.end());
    vector<int> ans(3);
    ll ret = 2e18;
    for (int i = 0; i < N-2; i++) {
        int s = i + 1, e = N-1;
        while (s < e) {
            ll sum = v[i] + v[s] + v[e];
            if (abs(sum) < ret) {
                ret = abs(sum);
                ans[0] = v[i];
                ans[1] = v[s];
                ans[2] = v[e];
            }
            if (sum == 0) break;
            else if (sum < 0) s++;
            else e--;
        }
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < 3; i++) cout << ans[i] << " ";
}