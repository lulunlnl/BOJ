#include "bits/stdc++.h"
using namespace std;
vector<int> button(10, 1);

int ok(int x) {
    int cnt = 0;
    if (x == 0 && button[0]) return 1;
    while (x > 0) {
        if (!button[x % 10]) return 0;
        x /= 10;
        cnt++;
    }
    return cnt;
}

int main() {
    int N, M; cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int x; cin >> x;
        button[x] = 0;
    }
    int ans = abs(N-100);
    if (ok(N)) ans = min(ok(N), ans);
    for (int i = 0; i <= 1000000; i++) {
        if (ok(i)) ans = min(ans, abs(N-i) + ok(i));
    }
    cout << ans << "\n";
}