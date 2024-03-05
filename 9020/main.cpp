#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> p(10005, 1);
    p[1] = 0;
    for (int i = 2; i <= 100; i++) {
        if (p[i]) {
            for (int j = i * i; j <= 10000; j += i) {
                p[j] = 0;
            }
        }
    }
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = N/2; i >= 1; i--) {
            if (p[i] && p[N - i]) {
                cout << i << " " << N - i << "\n";
                break;
            }
        }
    }
}