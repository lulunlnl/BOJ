#include "bits/stdc++.h"
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;
typedef long long ll;
const int INF = 1234567890;
const int MAX = 100005;

struct Node {
    ll lmax, rmax, mx, pSum;
    Node() {lmax = rmax = mx = pSum = -INF;}
    void set(int x) {lmax = rmax = mx = pSum = x;}
};

Node tree[4*MAX];
ll arr[MAX];

Node merge(Node left, Node right) {
    Node ret;
    ret.lmax = max(left.lmax, left.pSum + right.lmax);
    ret.rmax = max(right.rmax, right.pSum + left.rmax);
    ret.mx = max({left.mx, right.mx, left.rmax + right.lmax});
    ret.pSum = left.pSum + right.pSum;

    return ret;
}

void init(int node, int start, int end) {
    if (start == end) {
        tree[node].set(arr[start]);
        return;
    }
    int mid = (start+end)/2;
    init(node*2, start, mid);
    init(node*2+1, mid+1, end);
    tree[node] = merge(tree[node*2], tree[node*2+1]);
}

void update(int node, int start, int end, int index, ll val) {
    if (start == end) {
        tree[node].set(val);
        return;
    }
    int mid = (start+end)/2;
    if (index <= mid) update(node*2, start, mid, index, val);
    else update(node*2+1, mid+1, end, index, val);
    tree[node] = merge(tree[node*2], tree[node*2+1]);
}

Node query(int node, int start, int end, int left, int right) {
    if (left > end || right < start)
        return Node();
    if (left <= start && end <= right)
        return tree[node];
    int mid = (start+end)/2;
    return merge(query(node*2, start, mid, left, right), query(node*2+1, mid+1, end, left, right));
}

int main(void) {
    fastio;
    int N, Q, U, V;
    cin >> N >> Q >> U >> V;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i]; arr[i] = arr[i]*U + V;
    }
    init(1, 1, N);
    while (Q--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 0) cout << query(1, 1, N, a, b).mx - V << "\n";
        else update(1, 1, N, a, b*U + V);
    }
}