#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    stack<int> s;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (s.empty()) {
            s.push(x);
            continue;
        }
        while (!s.empty() && s.top() < x) {
            s.pop();
            ans++;
        }
        ans++;
        s.push(x);
    }
    cout << ans << "\n";
}