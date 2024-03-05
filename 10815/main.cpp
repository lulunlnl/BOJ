#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N;
    map<int, bool> mp;
    while (N--) {
        int x; cin >> x;
        mp[x] = 1;
    }
    cin >> M;
    while (M--) {
        int x; cin >> x;
        if (mp.find(x) != mp.end()) cout << "1 ";
        else cout << "0 ";
    }
}