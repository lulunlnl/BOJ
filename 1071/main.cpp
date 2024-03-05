#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    map<int, int> m;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        m[x]++;
    }
    vector<pair<int, int>> ans;
    for (auto e: m) {
        ans.push_back({e.first, e.second});
    }
    for (int i = 0; i < ans.size()-1; i++) {
        if (ans[i].first + 1 != ans[i+1].first) continue;
        if (i + 1 == ans.size() - 1) {
            swap(ans[i], ans[i+1]);
        }
        else {
            ans[i+2].second--;
            ans.insert(ans.begin()+i+1, {ans[i+2].first, 1});
            if (ans[i+3].second == 0) ans.erase(ans.begin()+i+3);
        }
    }
    for (auto e: ans) {
        for (int i = 0; i < e.second; i++) cout << e.first << " ";
    }
}