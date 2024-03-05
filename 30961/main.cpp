#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<ll> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    sort(a.begin(), a.end());
    ll ret = 0;
    for (int i = 0; i < N; i++) ret ^= a[i]*a[i];
    for (int i = 1; i < N; i++) ret ^= a[i-1] * a[i];
    cout << ret << "\n";
}