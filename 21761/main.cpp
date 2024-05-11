#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n, k; cin >> n >> k;
    ll val[4];
    for (int i = 0; i < 4; i++) cin >> val[i];
    vector<priority_queue<ll>> PQ(4);
    for (int i = 0; i < n; i++) {
        char c; int x;
        cin >> c >> x;
        PQ[c - 'A'].push(x);
    }
    for (int i = 0; i < k; i++) {
        double mx = 0;
        int idx = 0;
        for (int j = 0; j < 4; j++) {
            if (PQ[j].empty()) continue;
            if (mx < (double)PQ[j].top() / val[j]) {
                mx = (double)PQ[j].top() / val[j];
                idx = j;
            }
        }
        val[idx] += PQ[idx].top();
        cout << (char)(idx + 'A') << " " << PQ[idx].top() << "\n";
        PQ[idx].pop();
    }
}