#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    vector<int> a(N+1);
    for (int i = 1; i <= N; i++) a[i] = i;
    while (M--) {
        int i, j; cin >> i >> j;
        reverse(a.begin() + i, a.begin() + j + 1);
    }
    for (int i = 1; i <= N; i++) cout << a[i] << " ";
}