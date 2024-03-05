#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

struct Matrix{
    int size;
    vector< vector<ll> > arr;
    Matrix(int n){
        size = n;
        arr = vector< vector<ll> >(n, vector<ll>(n, 0));
    }
    Matrix operator * (const Matrix &x){
        Matrix ret(size);
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                for(int k=0; k<size; k++){
                    ret.arr[i][j] += arr[i][k] * x.arr[k][j];
                    ret.arr[i][j] %= MOD;
                }
            }
        }
        return ret;
    }
};

Matrix powmat(Matrix a, ll b){
    if(b == 1) return a;
    Matrix ret = powmat(a, b/2);
    ret = ret * ret;
    if(b & 1) ret = ret * a;
    return ret;
}

ll Pow(ll a, ll b) {
    if (b == 0) return 1;
    ll ret = Pow(a, b/2);
    if (b & 1) return a * ret % MOD * ret % MOD;
    return ret * ret % MOD;
}

void solve() {
    ll K, N; cin >> K >> N;
    if (N <= K) {
        cout << "1\n";
        return;
    }
    if (K == 0) {
        cout << Pow(2, N) << "\n";
        return;
    }
    Matrix g(K+1);
    g.arr[0][0] = g.arr[0][K] = 1;
    for (int i = 1; i <= K; i++) {
        g.arr[i][i-1] = 1;
    }
    Matrix ret = powmat(g, N);
    cout << ret.arr[0][0] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}