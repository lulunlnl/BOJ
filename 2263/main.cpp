#include "bits/stdc++.h"
using namespace std;
int in[100005], post[100005], pos[100005];

void solve(int l1, int r1, int l2, int r2) {
    if (l1 > r1 || l2 > r2) return;
    int root = post[r2], cur = pos[root];
    cout << root << " ";
    solve(l1, cur-1, l2, l2 + (cur-1-l1));
    solve(cur+1, r1, l2+cur-l1, r2-1);
}

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> in[i]; pos[in[i]] = i;
    }
    for (int i = 0; i < N; i++) cin >> post[i];
    solve(0, N-1, 0, N-1);
}