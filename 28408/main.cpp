#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

int main() {
    int n; cin >> n;
    vector<int> pre(n + 1), post(n + 1), pos1(n + 1), pos2(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> pre[i];
        pos1[pre[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> post[i];
        pos2[post[i]] = i;
    }
    function<long long(int, int, int, int)> solve = [&](int l1, int r1, int l2, int r2) -> long long {
        if (pre[l1] != post[r2]) return 0;
        if (l1 == r1) return 1;
        int left = pre[l1 + 1], right = post[r2 - 1];
        int a = pos1[right], b = pos2[left];
        if (a == l1 + 1) return 2 * solve(l1 + 1, r1, l2, r2 - 1) % mod;
        return solve(l1 + 1, a - 1, l2, b) * solve(a, r1, b + 1, r2 - 1) % mod;
    };
    cout << solve(1, n, 1, n) << '\n';
}