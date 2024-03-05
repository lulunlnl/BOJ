#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    stack<int> s;
    vector<int> ans;
    for (int i = N-1; i >= 0; i--) {
        while (!s.empty()) {
            if (s.top() <= a[i]) s.pop();
            else break;
        }
        if (s.empty()) ans.push_back(-1);
        else ans.push_back(s.top());
        s.push(a[i]);
    }
    for (int i = N-1; i >= 0; i--) cout << ans[i] << " ";
}