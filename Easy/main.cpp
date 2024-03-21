#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (1) {
        int n; cin >> n;
        if (!n) break;
        vector<int> a(n), tmp(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 6; i < n; i++) tmp[i] = 1;
        do {
            for (int i = 0; i < n; i++) {
                if (!tmp[i]) {
                    cout << a[i] << " ";
                }
            }
            cout << "\n";
        } while (next_permutation(tmp.begin(), tmp.end()));
        cout << "\n";
    }
}