#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> a(N), cnt(1000005, 0), chk(1000005, 0);
    for (int i = 0; i < N; i++) {
        cin >> a[i]; chk[a[i]] = 1;
    }
    for (int i = 0; i < N; i++) {
        int x = 2*a[i];
        while (x <= 1000000) {
            if (chk[x]) {
                cnt[a[i]]++;
                cnt[x]--;
            }
            x += a[i];
        }
    }
    for (int i = 0; i < N; i++) {
        cout << cnt[a[i]] << " ";
    }
}