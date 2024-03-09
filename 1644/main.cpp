#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> p(4000005, 1);
    p[1] = 0;
    for (int i = 2; i * i <= 4000000; i++) {
        if (p[i]) {
            for (int j = i*i; j <= 4000000; j += i) p[j] = 0;
        }
    }

    int N; cin >> N;
    if (N == 1) {
        cout << 0; return 0;
    }
    vector<int> prm;
    for (int i = 2; i <= N; i++) {
        if (p[i]) prm.push_back(i);
    }
    int ans = 0;
    int s = 0, e = 0, sum = 0;
    while (1) {
        if (e >= prm.size()) break;
        if (sum == N) ans++;
        if (sum < N && s < prm.size()) {
            sum += prm[s];
            s++;
        }
        else {
            sum -= prm[e];
            e++;
        }
    }
    cout << ans << "\n";
}