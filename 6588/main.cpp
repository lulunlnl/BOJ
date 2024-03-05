#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> p(1000005, 1);
    p[1] = 0;
    for (int i = 2; i <= 1000; i++) {
        if (p[i]) {
            for (int j = i * i; j <= 1000000; j += i) {
                p[j] = 0;
            }
        }
    }
    while (1) {
        int N; cin >> N;
        if (!N) break;
        for (int i = 2; i <= N/2; i++) {
            if (p[i] && p[N-i]) {
                cout << N << " = " << i << " + " << N-i << "\n";
                break;
            }
        }
    }
}