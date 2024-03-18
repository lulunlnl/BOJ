#include "bits/stdc++.h"
using namespace std;

int main() {
    int N, K; cin >> N >> K;
    int now = 0, prev = 0;
    for (int i = 2; i <= N; i++) {
        now = prev + K;
        now %= i;
        prev = now;
    }
    cout << now + 1;
}