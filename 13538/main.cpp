#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l, r, val;
};

vector<Node> tree(2);
int head[(1 << 19) + 5];

void init(int node, int s, int e) {
    if (s == e) return;
    int m = s + e >> 1;
    tree.push_back({0, 0, 0});
    tree[node].l = tree.size() - 1;
    init(tree[node].l, s, m);
    tree.push_back({0, 0, 0});
    tree[node].r = tree.size() - 1;
    init(tree[node].r, m + 1, e);
}

void update(int node, int s, int e, int idx, int val) {
    if (s == e) return;
    int m = s + e >> 1;
    if (idx <= m) {
        int lidx = tree[node].l;
        tree.push_back({tree[lidx].l, tree[lidx].r, tree[lidx].val + val});
        tree[node].l = tree.size() - 1;
        update(tree[node].l, s, m, idx, val);
    }
    else {
        int ridx = tree[node].r;
        tree.push_back({tree[ridx].l, tree[ridx].r, tree[ridx].val + val});
        tree[node].r = tree.size() - 1;
        update(tree[node].r, m + 1, e, idx, val);
    }
}

int sum(int node, int s, int e, int l, int r) {
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[node].val;
    int m = s + e >> 1;
    return sum(tree[node].l, s, m, l, r) + sum(tree[node].r, m + 1, e, l, r);
}

int kth(int n1, int n2, int s, int e, int k) {
    if (s == e) return s;
    int cnt = tree[tree[n1].l].val - tree[tree[n2].l].val;
    int m = s + e >> 1;
    if (k <= cnt) return kth(tree[n1].l, tree[n2].l, s, m, k);
    else return kth(tree[n1].r, tree[n2].r, m + 1, e, k - cnt);
}

int xor_query(int n1, int n2, int s, int e, int x) {
    if (s == e) return s;
    int m = s + e >> 1;
    int lcnt = tree[tree[n1].l].val - tree[tree[n2].l].val;
    int rcnt = tree[tree[n1].r].val - tree[tree[n2].r].val;
    if ((((e - s + 1) / 2) & x) && lcnt || !rcnt) return xor_query(tree[n1].l, tree[n2].l, s, m, x);
    else return xor_query(tree[n1].r, tree[n2].r, m + 1, e, x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    init(1, 0, (1 << 19) - 1);
    int m; cin >> m;
    int cnt = 0;
    while (m--) {
        int op, l, r, x;
        cin >> op;
        if (op == 1) {
            cin >> x;
            tree.push_back({tree[head[cnt]].l, tree[head[cnt]].r, tree[head[cnt]].val});
            head[++cnt] = tree.size() - 1;
            tree[head[cnt]].val += 1;
            update(head[cnt], 0, (1 << 19) - 1, x, 1);
        }
        else if (op == 2) {
            cin >> l >> r >> x;
            cout << xor_query(head[r], head[l - 1], 0, (1 << 19) - 1, x) << "\n";
        }
        else if (op == 3) {
            cin >> x;
            for (int i = cnt; i > cnt - x; i--) head[i] = 0;
            cnt -= x;
        }
        else if (op == 4) {
            cin >> l >> r >> x;
            cout << sum(head[r], 0, (1 << 19) - 1, 1, x) - sum(head[l - 1], 0, (1 << 19) - 1, 1, x) << "\n";
        }
        else {
            cin >> l >> r >> x;
            cout << kth(head[r], head[l - 1], 0, (1 << 19) - 1, x) << "\n";
        }
    }
}