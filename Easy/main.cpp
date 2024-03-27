#include "bits/stdc++.h"
using namespace std;

int main() {
    int l, p, v, cnt = 1;
    while (1) {
        cin >> l >> p >> v;
        if ((l | p | v) == 0) break;
        int ans = (v / p) * l + min(l, v % p);
        cout << "Case " << cnt << ": " << ans << "\n";
        cnt++;
    }
}