#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
const int MAX = 100005;

ll init(vll &arr, vll &tree, int node, int start, int end) {
    if (start == end) return tree[node] = arr[start];
    int mid = start + end >> 1;
    return tree[node] = init(arr, tree, node*2, start, mid) + init(arr, tree, node*2+1, mid+1, end);
}

void update_lazy(vll &tree, vll &lazy, int node, int start, int end) {
    if (!lazy[node]) return;
    tree[node] += (end-start+1) * lazy[node];
    if (start != end) {
        lazy[node*2] += lazy[node];
        lazy[node*2+1] += lazy[node];
    }
    lazy[node] = 0;
}

void update_range(vll &tree, vll &lazy, int node, int start, int end, int left, int right, ll diff) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) return;
    if (left <= start && end <= right) {
        tree[node] += (end-start+1)*diff;
        if (start != end) {
            lazy[node*2] += diff;
            lazy[node*2+1] += diff;
        }
        return;
    }
    int mid = start + end >> 1;
    update_range(tree, lazy, node*2, start, mid, left, right, diff);
    update_range(tree, lazy, node*2+1, mid+1, end, left, right, diff);
    tree[node] = tree[node*2] + tree[node*2+1];
}

ll query(vll &tree, vll &lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) return 0;
    if (left <= start && end <= right) return tree[node];
    int mid = start + end >> 1;
    return query(tree, lazy, node*2, start, mid, left, right) + query(tree, lazy, node*2+1, mid+1, end, left, right);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, K;
    cin >> N >> M >> K;
    int h = (int)ceil(log2(N)) + 1;
    int size = (1 << h);
    vll arr(N+1), lazy(size), tree(size);
    for (int i = 1; i <= N; i++) cin >> arr[i];
    init(arr, tree, 1, 1, N);
    M += K;
    while (M--) {
        int op, b, c;
        cin >> op >> b >> c;
        if (op == 1) {
            ll d; cin >> d;
            update_range(tree, lazy, 1, 1, N, b, c, d);
        }
        else cout << query(tree, lazy, 1, 1, N, b, c) << "\n";
    }
}