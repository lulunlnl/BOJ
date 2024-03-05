#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<ll> A(N), B(N), C(N), D(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }
    vector<ll> v1, v2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            v1.push_back(A[i] + B[j]);
            v2.push_back(C[i] + D[j]);
        }
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    ll ans = 0;
     for (auto e: v1) {
        ans += upper_bound(v2.begin(), v2.end(), -e) - lower_bound(v2.begin(), v2.end(), -e);
    }
    cout << ans << "\n";
}