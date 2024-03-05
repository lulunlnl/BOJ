#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string S; cin >> S;
    int ans = 0;
    vector<char> v;
    for (int i = 0; i < S.size(); i++) {
        if (v.empty()) v.push_back(S[i]);
        else if (i != 0 && S[i-1] == '(' && S[i] == ')') {
            v.pop_back();
            ans += v.size();
        }
        else if (v.back() == '(' && S[i] == ')') {
            v.pop_back(); ans++;
        }
        else v.push_back(S[i]);
    }
    cout << ans << "\n";
}