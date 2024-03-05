#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll N, K;

ll f(ll x) {
    // return B[x]
    ll ret = 0;
    for (int i = 1; i <= N; i++) {
        ret += min<ll>(x / i, N);
    }
    return ret;
}

int main() {
    cin >> N >> K;
    ll s = 1, e = N*N;
    while (s <= e) {
        ll m = s + e >> 1;
        if (f(m) >= K) e = m-1;
        else s = m+1;
    }
    cout << s << "\n";
}