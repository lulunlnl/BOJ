#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string S; cin >> S;
    stack<char> stk;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] >= 'A' && S[i] <= 'Z') cout << S[i];
        else if (stk.empty()) stk.push(S[i]);
        else if (S[i] == '+' || S[i] == '-') {

        }
        else if (S[i] == '*' || S[i] == '/') {

        }
        else if (S[i] == '(') stk.push('(');
        else {
            while (!stk.empty() && stk.top() != '(') {
                cout << stk.top();
                stk.pop();
            }
            stk.pop();
        }
    }
    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
}