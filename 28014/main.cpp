#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, cnt = 0;
    cin >> N;
    vector<int> a(N+1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        if (a[i] > a[i-1]) cnt++;
    }
    cout << cnt << "\n";
}