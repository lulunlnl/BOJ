#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, c; cin >> n >> c;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int l = 0, r = 1e9;
    int ans = 0;
    auto ok = [&](int x) {
        int prev = a[0];
        int cnt = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] - prev >= x) prev = a[i], cnt++;
        }
        if (cnt >= c) return true;
        return false;
    };
    while (l <= r) {
        int m = l + r >> 1;
        if (ok(m)) {
            l = m + 1;
            ans = m;
        }
        else {
            r = m - 1;
        }
    }
    cout << ans << "\n";
}