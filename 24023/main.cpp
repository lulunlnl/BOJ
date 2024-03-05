#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K; cin >> N >> K;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    int s = 0, e = 0;
    int x = 0;
    for (int i = 0; i < N; i++) {
        if ((a[i] | K) == K) {
            x |= a[i];
            e = i;
            if (x == K) {
                cout << s + 1 << " " << e + 1 << "\n";
                return 0;
            }
        }
        else {
            s = i + 1;
            x = 0;
        }
    }
    cout << -1;
}