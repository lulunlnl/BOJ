#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int l = 0, r = N-1, x, cnt = 0;
    cin >> x;
    while (l < r) {
        if (a[l] + a[r] == x) cnt++, l++;
        else if (a[l] + a[r] > x) r--;
        else l++;
    }
    cout << cnt << "\n";
}