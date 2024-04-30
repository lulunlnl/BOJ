#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int s = 0, e = n - 1, ans = 2e9;
    int a1, a2;
    while (s < e) {
        int sum = a[s] + a[e];
        if (abs(sum) < ans) {
            ans = abs(sum);
            a1 = s, a2 = e;
        }
        if (sum < 0) s++;
        else e--;
    }
    cout << a[a1] << " " << a[a2];
}