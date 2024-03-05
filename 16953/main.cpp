#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    ll A, B; cin >> A >> B;
    int ans = 1;
    while (1) {
        if (A == B) break;
        if (A > B) {
            ans = -1; break;
        }
        if (B % 10 == 1) B /= 10;
        else if (B % 2 == 0) B /= 2;
        else {
            ans = -1; break;
        }
        ans++;
    }
    cout << ans << "\n";
}