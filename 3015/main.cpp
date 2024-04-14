#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    stack<pair<int, int>> s;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int x, cnt = 1; cin >> x;
        while (!s.empty() && s.top().first <= x) {
            if (s.top().first == x) {
                ans += s.top().second;
                cnt = s.top().second + 1;
                s.pop();
            }
            else {
                ans += s.top().second;
                cnt = 1;
                s.pop();
            }
        }
        if (!s.empty()) ans++;
        s.push({x, cnt});
    }
    cout << ans << "\n";
}