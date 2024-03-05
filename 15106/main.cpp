#include "bits/stdc++.h"
using namespace std;
typedef unsigned long long ll;

ll F(ll N) {
    ll ret = 0, j = 0;
    // Harmonic Lemma
    for (ll i = 1; i <= N; i = j + 1) {
        j = N / (N / i);
        ret += (i + j) * (j - i + 1) / 2 * (N / i);
    }
    return ret;
}

int main() {
    ll a, b; cin >> a >> b;
    cout << F(b) - F(a-1) << "\n";
}
