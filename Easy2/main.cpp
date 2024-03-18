#include "bits/stdc++.h"
using namespace std;
int N, ans;

void solve(int x) {
    if (x > N) return;
    if (x == N) {
        ans++;
        return;
    }
    for (int i = 1; i <= 2; i++) {
        solve(x + i);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    solve(0);
    solve(2);
    cout << ans;
}