#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;

vector<ull> A = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

ull mul(ull x, ull y, ull mod)
{
    return (i128)x * y % mod;
}

ull powmod(i128 x, i128 y, i128 mod) // x^y % mod
{
    x %= mod;
    i128 res = 1;
    while (y > 0)
    {
        if (y % 2 == 1)
            res = (res*x)%mod;
        x = (x*x) % mod;
        y /= 2;
    }
    return  (ull)res;
}

bool miller_rabin(ull n, ull a)
{
    ull d = n-1;
    while (d % 2 == 0)
    {
        if (powmod(a, d, n) == n-1)
            return true;
        d /= 2;
    }
    ull tmp = powmod(a, d, n);
    return (tmp == 1 || tmp == n-1);
}

bool is_prime(ull n)
{
    if (n <= 1) return false;
    if (n <= 10000)
    {
        for (int i = 2; i*i <= n; i++)
            if (n % i == 0)
                return false;

        return true;
    }
    for (ull a: A)
        if (!miller_rabin(n, a))
            return false;
    return true;
}

ull gcd(ull a, ull b)
{
    if (a < b)  swap(a, b);
    while (b != 0)
    {
        ull r = a % b;
        a = b;
        b = r;
    }
    return a;
}

ull find_div(i128 n)
{
    if (n % 2 == 0)
        return 2;
    if (is_prime(n))    return n;
    i128 x = rand()%(n-2)+2, y = x;
    i128 c = rand() % 20 + 1, d = 1;
    while (d == 1)
        // 토끼와 거북이
    {
        x = (mul(x, x, n) + c)%n;
        y = (mul(y, y, n) + c)%n;
        y = (mul(y, y, n) + c)%n;
        d = gcd(abs(x-y), n);
        if (d == n) return find_div(n);
    }
    if (is_prime(d)) return d;
    else return find_div(d);
}

int main(void)
{
    while (1) {
        ull N, ret = 2;
        vector<ull> ans, temp;
        cin >> N;
        if (N == 0) return 0;
        while (N % 2 == 0) N /= 2;
        if (N == 1) {
            cout << "2\n";
            continue;
        }
        while (N > 1)
        {
            ull div = find_div(N);
            N /= div;
            ans.push_back(div);
        }
        sort(ans.begin(), ans.end());
        temp = ans;
        temp.erase(unique(temp.begin(), temp.end()), temp.end());
        for (ull &i: temp) {
            ull x = upper_bound(ans.begin(), ans.end(), i) - lower_bound(ans.begin(), ans.end(), i);
            x = 2*x+1;
            ret *= x;
        }
        cout << ret << "\n";
    }
}