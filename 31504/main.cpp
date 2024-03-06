#include <bits/stdc++.h>

#define ft first
#define sd second
using namespace std;
typedef long long ll;
ll MOD;

struct Matrix {
    int size;
    vector<vector<ll> > arr;

    Matrix() { size = 0; }

    Matrix(int n) {
        size = n;
        arr = vector<vector<ll> >(n, vector<ll>(n));
    }

    Matrix operator*(const Matrix &x) {
        Matrix ret(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    ret.arr[i][j] += arr[i][k] * x.arr[k][j];
                    ret.arr[i][j] %= MOD;
                }
            }
        }
        return ret;
    }
};

Matrix powmat(Matrix a, ll b) {
    if (b == 1) return a;
    Matrix ret = powmat(a, b / 2);
    ret = ret * ret;
    if (b & 1) ret = ret * a;
    return ret;
}

ll dp(ll x) {
    if (x == -1 || x == 0 || x == 1) return 1;
    Matrix t(2);
    t.arr = {{3, -1},
             {1, 0}};
    Matrix ret = powmat(t, x - 1);
    return (ret.arr[0][0] + ret.arr[0][1]) % MOD;
}

int main(void) {
    cin.tie(0)->sync_with_stdio(0);
    ll N, K;
    cin >> N >> MOD >> K;
    if (K == 0) {
        cout << dp(N) << "\n";
        return 0;
    }
    vector<pair<int, int>> v(K), arr;
    for (int i = 0; i < K; i++) {
        cin >> v[i].sd >> v[i].ft;
        v[i].ft--;
        v[i].sd--;
    }
    sort(v.begin(), v.end());
    arr.push_back({min(v[0].ft, v[0].sd), max(v[0].ft, v[0].sd)});
    // (3, 3), (3, 4), (3, 5)
    // (5, 3), (5, 4), (5, 5)
    for (int i = 1; i < K; i++) {
        if (v[i-1].ft == v[i].ft) {
            if (v[i].sd <= v[i].ft) continue;
            else arr.pop_back();
        }
        arr.push_back({min(v[i].ft, v[i].sd), max(v[i].ft, v[i].sd)});
    }
    sort(arr.begin(), arr.end());
    ll ans = 1;
    ans *= dp(arr[0].ft + 1);
    ans %= MOD;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i].ft < arr[i - 1].sd) {
            cout << "0\n";
            return 0;
        }
        ans *= 2 * dp(arr[i].ft - arr[i - 1].sd) - dp(arr[i].ft - arr[i - 1].sd - 1);
        ans %= MOD;
    }
    ans *= dp(N - arr.back().sd);
    ans %= MOD;
    cout << ans << "\n";
}