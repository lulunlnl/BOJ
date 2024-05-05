#include <bits/stdc++.h>
using namespace std;
typedef pair<int, pair<int, int>> piii;

int main() {
    int n, m; cin >> n >> m;
    vector<pair<int, pair<int, int>>> arr(m);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        if (x > y) y += n;
        arr[i] = {i, {x, y}};
    }
    sort(arr.begin(), arr.end(), [&](const piii& a, const piii& b) {
        if (a.second.first == b.second.first) return a.second.second > b.second.second;
        return a.second.first < b.second.first;
    });
    set<int> ans;
    pair<int, int> last = arr[0].second;
    ans.insert(arr[0].first);
    for (int i = 1; i < m; i++) {
        if (last.second >= arr[i].second.second) continue;
        ans.insert(arr[i].first);
        last = arr[i].second;
    }
    for (int i = 0; i < m; i++) {
        if (last.second - n >= arr[i].second.second) ans.erase(arr[i].first);
    }
    for (auto& e: ans) cout << e + 1 << " ";
}