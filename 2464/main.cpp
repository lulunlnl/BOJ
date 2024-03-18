#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll N; cin >> N;
    int flag = 0;
    for (int i = 1; i <= 61; i++) {
        if (((1ll << i) & N) && !((1ll << (i-1)) & N)) {
            ll ans = N - (1ll << (i-1));
            int cnt = 0;
            for (int j = 0; j <= i-2; j++) {
                if ((1ll << j) & N) {
                    cnt++;
                    ans -= (1ll << j);
                }
            }
            for (int j = i-2; j > i-2-cnt; j--) {
                ans += (1ll << j);
            }
            cout << ans << " ";
            flag = 1;
            break;
        }
    }
    if (!flag) cout << "0 ";
    for (int i = 0; i <= 60; i++) {
        if (((1ll << i) & N) && !((1ll << (i+1)) & N)) {
            ll ans = N + (1ll << i);
            int cnt = 0;
            for (int j = 0; j <= i-1; j++) {
                if ((1ll << j) & N) {
                    cnt++;
                    ans -= (1ll << j);
                }
            }
            for (int j = 0; j < cnt; j++) {
                ans += (1ll << j);
            }
            cout << ans << "\n";
            break;
        }
    }
}