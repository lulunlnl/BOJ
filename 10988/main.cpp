#include "bits/stdc++.h"
using namespace std;

int main() {
    string S; cin >> S;
    int N = S.size();
    for (int i = 0; i < N/2; i++) {
        if (S[i] != S[N-i-1]) {
            cout << 0;
            return 0;
        }
    }
    cout << 1;
}