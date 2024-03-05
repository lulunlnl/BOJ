#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int MAX = 100005;

struct Segtree {
    ll tree[4*MAX] = {}, lazy[4*MAX] = {};
    void push(int node, int s, int e) {
        if (!lazy[node]) return;
        tree[node] += (e-s+1) * lazy[node];
        if (s != e) {
            lazy[node << 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    void update(int node, int s, int e, int l, int r, ll v) {
        push(node, s, e);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lazy[node] = v;
            push(node, s, e);
            return;
        }
        int m = s + e >> 1;
        update(node << 1, s, m, l, r, v);
        update(node << 1 | 1, m+1, e, l, r, v);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }
    ll query(int node, int s, int e, int l, int r) {
        push(node, s, e);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return query(node << 1, s, m, l, r) + query(node << 1 | 1, m+1, e, l, r);
    }
} seg;

struct GCD_Segtree {
    ll tree[4*MAX] = {};
    ll update(int node, int s, int e, int idx, int v) {
        if (idx < s || e < idx) return tree[node];
        if (s == e) return tree[node] += v;
        int m = s + e >> 1;
        return tree[node] = __gcd(update(node << 1, s, m, idx, v), update(node << 1 | 1, m+1, e, idx, v));
    }
    ll query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return __gcd(query(node << 1, s, m, l, r), query(node << 1 | 1, m+1, e, l, r));
    }
} gcd_seg;


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q; cin >> N;
    vector<ll> a(N+1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        seg.update(1, 1, N, i, i, a[i]);
        if (i != 1) gcd_seg.update(1, 1, N, i, a[i] - a[i-1]);
    }
    cin >> Q;
    while (Q--) {
        ll T; int A, B; cin >> T >> A >> B;
        if (T) {
            seg.update(1, 1, N, A, B, T);
            gcd_seg.update(1, 1, N, A, T);
            gcd_seg.update(1, 1, N, B+1, -T);
        }
        else {
            ll now = seg.query(1, 1, N, A, A);
            if (A == B) cout << now << "\n";
            else cout << gcd(now, gcd_seg.query(1, 1, N, A+1, B)) << "\n";
        }
    }
}