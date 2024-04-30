#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    auto b = a;
    reverse(b.begin(), b.end());
    for (int i = 0; i < n; i++) b[i] *= -1;

    int ans1 = 0, ans2 = 0, m = 2e9;
    for (int i = 0; i < n; i++) {
        int idx1 = lower_bound(a.begin(), a.end(), -a[i]) - a.begin();
        int idx2 = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        if (a[idx1] - b[idx2] < m) {
            m = a[idx1] - b[idx2];
            ans1 = idx1, ans2 = idx2;
        }
    }
    cout << a[ans1] << " " << -b[ans2] << "\n";
}