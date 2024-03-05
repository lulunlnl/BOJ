#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;

struct Fenwick {
    vector<ll> tree;
    int sz;
    void init(int N) {
        sz = N;
        tree.resize(N+1);
    }
    void update(int i, ll v) {
        while (i <= sz) {
            tree[i] += v; tree[i] %= MOD;
            i += i & -i;
        }
    }
    ll sum(int i) {
        ll ans = 0;
        while (i > 0) {
            ans += tree[i]; ans %= MOD;
            i -= i & -i;
        }
        return ans;
    }
} fen[12];
// fen[i]: 길이 i, x로 끝나는 증가 수열 개수

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    for (int i = 0; i < 12; i++) fen[i].init(N);
    for (int i = 0; i < N; i++) {
        ll x; cin >> x;
        fen[1].update(x, 1);
        for (int j = 2; j < 12; j++) {
            fen[j].update(x, fen[j-1].sum(x-1));
        }
    }
    cout << fen[11].sum(N) << "\n";
}