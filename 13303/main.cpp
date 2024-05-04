#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dist[2000005];

int main() {
    int n; cin >> n;
    int sy, ex; cin >> sy >> ex;
    set<int> s;
    vector<pair<int, pair<int, int>>> arr(n);
    for (int i = 0; i < n; i++) {
        int x, yl, yr; cin >> x >> yl >> yr;
        arr[i] = {x, {yl, yr}};
    }
    sort(arr.begin(), arr.end());
    fill(dist, dist + 2000005, 2e18);
    s.insert(sy); dist[sy] = 0;
    for (int i = 0; i < n; i++) {
        int a = arr[i].second.first, b = arr[i].second.second;
        auto it = s.upper_bound(a);
        while (it != s.end() && *it < b) {
            dist[a] = min(dist[a], dist[*it] + (*it - a));
            dist[b] = min(dist[b], dist[*it] + (b - *it));
            dist[*it] = 2e18;
            it = s.erase(it);
        }
        if (dist[a] != 2e18) s.insert(a);
        if (dist[b] != 2e18) s.insert(b);
    }
    ll ans = 2e18;
    for (auto t: s) {
        ans = min(ans, dist[t]);
    }
    vector<int> sol;
    for (auto t: s) {
        if (ans == dist[t]) sol.push_back(t);
    }
    cout << ans + ex << "\n";
    cout << sol.size() << " ";
    for (auto t: sol) cout << t << " ";
}