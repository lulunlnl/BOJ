#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
    ll p, q, l;
    bool operator < (const Point &O) {
        if (q * O.p != p * O.q) return q * O.p < p * O.q;
        return l > O.l;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<array<ll, 3>> arr(n);
    for (int i = 0; i < n; i++) {
        ll x1, x2, y; cin >> x1 >> x2 >> y;
        if (x1 > x2) swap(x1, x2);
        arr[i] = {x1, x2, y};
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (auto t: {0, 1}) {
            vector<Point> P;
            for (int j = 0; j < n; j++) {
                if (arr[i][2] == arr[j][2]) continue;
                auto tmp = arr[j];
                if (arr[i][2] < arr[j][2]) {
                    arr[j][0] = 2 * arr[i][t] - arr[j][0];
                    arr[j][1] = 2 * arr[i][t] - arr[j][1];
                    swap(arr[j][0], arr[j][1]);
                }
                P.push_back({arr[j][0] - arr[i][t], abs(arr[j][2] - arr[i][2]), -(arr[j][1] - arr[j][0])});
                P.push_back({arr[j][1] - arr[i][t], abs(arr[j][2] - arr[i][2]), arr[j][1] - arr[j][0]});
                assert(arr[j][0] <= arr[j][1]);
                arr[j] = tmp;
            }
            sort(P.begin(), P.end());
            ll now = arr[i][1] - arr[i][0];
            ans = max(ans, now);
            for (int j = 0; j < P.size(); j++) {
                now += P[j].l;
                ans = max(ans, now);
            }
        }
    }
    cout << ans;
}