#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int d; cin >> d;
    // 5.5t % 360 = d or 360-d
    int cnt = 0;
    vector<int> ans;
    for (int i = 0; i < 12*60; i += 2) {
        if (i / 2 * 11 % 360 == d || i / 2 * 11 % 360 == 360-d) {
            cnt++;
            ans.push_back(i);
        }
    }
    cout << cnt << "\n";
    for (auto &i: ans) {
        printf("%02d:%02d\n", i/60, i%60);
    }
}