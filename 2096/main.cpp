#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> dp1(3), dp2(3);
    for (int i = 0; i < N; i++) {
        int t[3];
        cin >> t[0] >> t[1] >> t[2];
        auto tmp1 = dp1, tmp2 = dp2;
        dp1[0] = max(tmp1[0], tmp1[1]) + t[0];
        dp1[1] = max({tmp1[0], tmp1[1], tmp1[2]}) + t[1];
        dp1[2] = max(tmp1[1], tmp1[2]) + t[2];

        dp2[0] = min(tmp2[0], tmp2[1]) + t[0];
        dp2[1] = min({tmp2[0], tmp2[1], tmp2[2]}) + t[1];
        dp2[2] = min(tmp2[1], tmp2[2]) + t[2];
    }
    cout << *max_element(dp1.begin(), dp1.end()) << " " << *min_element(dp2.begin(), dp2.end());
}