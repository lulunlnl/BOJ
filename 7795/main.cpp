#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        vector<int> a(N), b(M);
        for (int i = 0; i < N; i++) cin >> a[i];
        for (int j = 0; j < M; j++) cin >> b[j];
        int cnt = 0;
        sort(a.begin(), a.end());
        for (int i = 0; i < M; i++) {
            cnt += N - (upper_bound(a.begin(), a.end(), b[i]) - a.begin());
        }
        cout << cnt << "\n";
    }
}