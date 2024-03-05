#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
int N;
ll v1[40], v2[40];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> v1[i];
    for (int i = 0; i < N; i++) cin >> v2[i];

    for (int i = 0; i < (1<<(N/2)); i++) {
        ll sum = 0;
        for (int j = 0; j < N/2; j++) {
            if (i & (1<<(N/2-1-j))) sum += v1[i];
            else sum -= v2[i];
        }
        if ()
    }
}