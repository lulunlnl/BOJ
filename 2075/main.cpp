#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> v(N*N);
    for (int i = 0; i < N*N; i++) {
        cin >> v[i];
    }
    sort(v.rbegin(), v.rend());
    cout << v[N-1] << "\n";
}