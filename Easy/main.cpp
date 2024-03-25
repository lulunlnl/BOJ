#include "bits/stdc++.h"
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        int now = 0, S = -1e9;
        for (int i = 0; i < n; i++) {
            now = max(a[i], now + a[i]);
            S = max(S, now);
        }
        cout << S << "\n";
    }
}