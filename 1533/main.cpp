#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll MOD = 1000003;

struct Mat {
    int sz = 0;
    vector<vector<ll>> arr;
    Mat(int N) {
        sz = N;
        arr = vector<vector<ll>>(N, vector<ll>(N));
    }
    Mat operator * (const Mat &x) const {
        Mat ret(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                for (int k = 0; k < sz; k++) {
                    ret.arr[i][j] += arr[i][k] * x.arr[k][j];
                    ret.arr[i][j] %= MOD;
                }
            }
        }
        return ret;
    };
};

Mat pow_mat(Mat a, ll b) {
    if (b == 1) return a;
    Mat ret = pow_mat(a, b/2);
    ret = ret*ret;
    if (b & 1) return ret*a;
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll N, S, E, T; cin >> N >> S >> E >> T;
    S--; E--;
    Mat mat(5*N); // i: j ~ j+4, (j+4, j+3) ...
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < 5; j++) {
            mat.arr[i*5+j][i*5+j-1] = 1;
        }
    }
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        for (int j = 0; j < N; j++) {
            int x = s[j] - '0';
            if (x != 0) mat.arr[i*5][j*5+x-1] = 1;
        }
    }
    Mat ans = pow_mat(mat, T);
    cout << ans.arr[S*5][E*5] << "\n";
}