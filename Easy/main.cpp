#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    int ans = 0, now = 1, ret = 0;
    for (int i = 1; i <= n; i++) {
        now = i, ret = 0;
        while (ret < n) {
            ret += now++;
        }
        if (ret == n) ans++;
    }
    cout << ans << "\n";
}