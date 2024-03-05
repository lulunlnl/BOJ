#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
constexpr ll MOD = 100007; // 97 * 1031
ll Ms[2] = {97, 1031}, fac[2][1050], inv[2][1050];

ll mod(ll a, ll b) {
    a %= b;
    return (a >= 0) ? a : a + b;
}

ll Pow(ll a, ll b, ll mod) {
    if (b == 0) return 1;
    ll ret = Pow(a, b/2, mod);
    if (b & 1) return ret*ret%mod*a%mod;
    return ret*ret%mod;
}

tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x, y] = ext_gcd(b, a % b);
    return {g, y, x - a/b * y};
}

pair<ll, ll> crt(ll a1, ll m1, ll a2, ll m2) {
    // a = a1 (mod m1), a = a2 (mod m2)
    // a = a1 + m1x, a = a2 - m2y
    // m1x + m2y = a2 - a1 => x
    ll g = gcd(m1, m2), m = m1 * m2 / g;
    if ((a2-a1) % g) return {-1, -1};
    ll mul = mod((a2-a1) / g, m2);
    ll x = mod(get<1>(ext_gcd(m1, m2)), m2) * mul % m2;
    return {(a1 + x*m1) % m, m};
}

pair<ll, ll> crt(vector<ll> &a, vector<ll> &m) {
    ll ra = a[0], rm = m[0];
    for (int i = 1; i < m.size(); i++) {
        auto [aa, mm] = crt(ra, rm, a[i], m[i]);
        if (mm == -1) return {-1, -1};
        ra = aa, rm = mm;
    }
    return {ra, rm};
}

void init(int t) {
    ll p = Ms[t];
    fac[t][0] = 1;
    for (int i = 1; i < p; i++) fac[t][i] = fac[t][i-1] * i % p;
    inv[t][p-1] = Pow(fac[t][p-1], p-2, p);
    for (int i = p-2; i >= 0; i--) inv[t][i] = inv[t][i+1] * (i+1) % p;
}

ll small(ll n, ll r, int t) {
    ll p = Ms[t];
    if (n < r || n < 0 || r < 0) return 0;
    return fac[t][n] * inv[t][r] % p * inv[t][n-r] % p;
}

ll lucas(ll n, ll r, int t) {
    ll p = Ms[t];
    if (n < r || n < 0 || r < 0) return 0;
    if (n == r || !n || !r) return 1;
    return small(n%p, r%p, t) * lucas(n/p, r/p, t) % p;
 }

void solve() {
    ll N, M; cin >> N >> M;
    // nHk = (n+k-1)C(n-1);
    // (m-1)H(n-m+1) = (n-1)C(m-2)
    if (N == 0 && M == 1) {
        cout << "1\n"; return;
    }
    else if (M == 1) {
        cout << "0\n"; return;
    }
    ll a1 = lucas(N-1, M-2, 0);
    ll a2 = lucas(N-1, M-2, 1);
    ll ret = crt(a1, Ms[0], a2, Ms[1]).first;
    cout << ret << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    init(0); init(1);
    int T; cin >> T;
    while (T--) solve();
}