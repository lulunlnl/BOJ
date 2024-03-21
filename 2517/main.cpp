#include "bits/stdc++.h"

using namespace std;

struct Fenwick {
    vector<int> tree;
    int sz;

    void init(int n) {
        sz = n;
        tree.resize(n + 1, 0);
    }

    int sum(int i) {
        int ans = 0;
        while (i > 0) {
            ans += tree[i];
            i -= (i & -i);
        }
        return ans;
    }

    void update(int i, int num) {
        while (i <= sz) {
            tree[i] += num;
            i += (i & -i);
        }
    }
} fen;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> in, v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        in.push_back(x);
        v.push_back(x);
    }
    sort(in.begin(), in.end());
    in.erase(unique(in.begin(), in.end()), in.end());
    for (int i = 0; i < n; i++) {
        v[i] = lower_bound(in.begin(), in.end(), v[i]) - in.begin();
    }
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) arr[v[i]]++;
    for (int i = 0; i < n; i++) {
        cout << i - v[i] << "\n";
    }
}