#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#ifdef ONLINE_JUDGE
#define debug(x)
#else
#define debug(x) cout << "[Debug] " << #x << ": " << x << '\n'
#define debug2(x, y) cout << "[Debug] " << #x << ": " << x << ", " << #y << ": " << y << '\n';
#endif

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int A, B, C; cin >> A >> B >> C;
    int g = gcd(A, gcd(B, C));
    A /= g, B /= g, C /= g;
    if ((A+B+C) % 3 != 0) {
        cout << 0;
        return 0;
    }
    int t = A + B + C; t /= 3;
    while (1) {
        if (t % 2 == 0) t /= 2;
        else break;
    }
    if (t == 1) cout << 1;
    else cout << 0;
}