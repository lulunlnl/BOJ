#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    auto f = [&](auto&& self, int l, int r) -> void {
        if (l > r) return;
        if (l == r) {
            cout << v[l] << "\n";
            return;
        }
        int t = l + 1;
        while (t <= r) {
            if (v[l] < v[t]) break;
            else t++;
        }
        self(self, l+1, t-1); self(self, t, r);
        cout << v[l] << "\n";
    };
    f(f, 0, v.size()-1);
}