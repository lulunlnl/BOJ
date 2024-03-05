#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    cin >> K;
    vector<int> s;
    for (int i = 0; i < 2*K; i++) {
        int x; cin >> x; x--;
        if (i % 2 == 1) x = -x;
        while (!s.empty()) {
            if (abs(s.back()) <= abs(x)) s.pop_back();
            else break;
        }
        s.push_back(x);
    }
    deque<int> DQ;
    int sort_idx = abs(s[0]);
    sort(a.begin(), a.begin() + sort_idx + 1);
    for (int i = 0; i <= sort_idx; i++) {
        DQ.push_back(a[i]);
    }
    int l = 0, r = sort_idx;
    vector<int> ans;
    for (int i = 0; i < s.size() - 1; i++) {
        int t = abs(s[i]) - abs(s[i+1]);
        if (s[i] >= 0) {
            for (int j = 0; j < t; j++) {
                ans.push_back(DQ.back());
                DQ.pop_back();
            }
        }
        else {
            for (int j = 0; j < t; j++) {
                ans.push_back(DQ.front());
                DQ.pop_front();
            }
        }
    }
    if (s.back() >= 0) {
        while (!DQ.empty()) {
            ans.push_back(DQ.back());
            DQ.pop_back();
        }
    }
    else {
        while (!DQ.empty()) {
            ans.push_back(DQ.front());
            DQ.pop_front();
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    for (int i = sort_idx + 1; i < N; i++) cout << a[i] << " ";
}