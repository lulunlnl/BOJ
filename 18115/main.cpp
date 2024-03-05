#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    reverse(a.begin(), a.end());
    deque<int> dq;
    for (int i = 0; i < N; i++) {
        if (a[i] == 1) dq.push_front(i+1);
        else if (a[i] == 2) {
            int x = dq.front();
            dq.pop_front();
            dq.push_front(i+1);
            dq.push_front(x);
        }
        else dq.push_back(i+1);
    }
    for (int i = 0; i < N; i++) {
        cout << dq[i] << " ";
    }
}