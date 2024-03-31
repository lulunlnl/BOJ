#include <bits/stdc++.h>
using namespace std;

int sqrtN;
int arr[100005];
vector<int> node[400];

void update(int a, int b) {
    int t = a / sqrtN;
    if (arr[a]) {
        for (int i = 0; i < node[t].size(); i++) {
            if (node[t][i] == arr[a]) {
                node[t].erase(node[t].begin() + i);
                break;
            }
        }
    }
    for (int i = 0; i <= node[t].size(); i++) {
        if (i == node[t].size() || node[t][i] >= b) {
            node[t].insert(node[t].begin() + i, b);
            break;
        }
    }
    arr[a] = b;
}

int query(int s, int e, int c) {
    int ret = 0;
    if (s / sqrtN == e /sqrtN) {
        for (int i = s; i <= e; i++) ret += arr[i] > c;
        return ret;
    }
    for (int i = s; i < (s / sqrtN + 1) * sqrtN; i++) ret += arr[i] > c;
    for (int i = e / sqrtN * sqrtN; i <= e; i++) ret += arr[i] > c;
    for (int i = s / sqrtN + 1; i < e / sqrtN; i++) ret += node[i].end() - upper_bound(node[i].begin(), node[i].end(), c);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n;
    sqrtN = (int)sqrt(n);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        update(i, x);
    }
    cin >> q;
    while (q--) {
        int op, i, j; cin >> op >> i >> j;
        if (op == 1) {
            int k; cin >> k;
            cout << query(i, j, k) << "\n";
        }
        else {
            update(i, j);
        }
    }
}