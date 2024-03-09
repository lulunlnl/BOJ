#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int M, N; cin >> M >> N;
    vector<int> p(10005, 1);
    p[1] = 0;
    for (int i = 2; i * i <= 10000; i++) {
        if (p[i]) {
            for (int j = i*i; j <= 10000; j += i) p[j] = 0;
        }
    }
    int sum = 0;
    for (int i = M; i <= N; i++) {
        if (p[i]) sum += i;
    }
    if (sum == 0) {
        cout << -1 << "\n";
        return 0;
    }
    cout << sum << "\n";
    for (int i = M; i <= N; i++) {
        if (p[i]) {
            cout << i; return 0;
        }
    }
}