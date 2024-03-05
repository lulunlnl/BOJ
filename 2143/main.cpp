#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll T; cin >> T;
    int N, M; cin >> N;
    vector<ll> a(N+1, 0), p1(N+1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        p1[i] = p1[i-1] + a[i];
    }
    cin >> M;
    vector<ll> b(M+1, 0), p2(M+1, 0);
    for (int i = 1; i <= M; i++) {
        cin >> b[i];
        p2[i] = p2[i-1] + b[i];
    }
    vector<ll> c;
    for (int i = 1; i <= M; i++) {
        for (int j = i; j <= M; j++) {
            c.push_back(p2[j] - p2[i-1]);
        }
    }
    sort(c.begin(), c.end());
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j++) {
            ll x = T - p1[j] + p1[i-1];
            ll cnt = upper_bound(c.begin(), c.end(), x) - lower_bound(c.begin(), c.end(), x);
            ans += cnt;
        }
    }
    cout << ans << "\n";
}