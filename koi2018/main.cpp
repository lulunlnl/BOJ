#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<int, ll>> x(n);
    for (int i = 0; i < n; i++) {
        int idx, t; cin >> idx >> t;
        x[i] = {idx, t};
    }
    int m; cin >> m;
    vector<pair<int, ll>> y(m);
    vector<ll> pSum(m + 1, 0);
    for (int i = 0; i < m; i++) {
        int idx, t; cin >> idx >> t;
        y[i] = {idx, t};
        pSum[i + 1] = pSum[i] + t;
    }
    int a, b; cin >> a >> b;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int l = 0, r = m - 1, left = 0, right = m - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (y[mid].first - x[i].first >= a) r = mid - 1, left = mid;
            else l = mid + 1;
        }
        l = 0, r = m - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (y[mid].first - x[i].first <= b) l = mid + 1, right = mid;
            else r = mid - 1;
        }
        ans += x[i].second * (pSum[right + 1] - pSum[left]);
    }
    cout << ans << "\n";
}