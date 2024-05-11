#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    int cnt = 0, now = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        now = max(0, now + x);
        cnt += now >= m;
    }
    cout << cnt;
}