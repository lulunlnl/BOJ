#include <bits/stdc++.h>
using namespace std;typedef long long ll;const ll MOD = 998244353;ll c[100005],a[100005],ans;vector<pair<ll, int>> arr;
main(){int N; cin >> N;for(int i=0;i<N;i++){cin >> c[i] >> a[i];ans += (N-1)*a[i];arr.push_back({c[i]-a[i], i});}sort(arr.begin(),arr.end());ll t = 1, x = 1;for (int i = 1; i < N; i++){if (arr[i-1].first == arr[i].first){t *= x;t %= MOD;x++;}else{t *= x;t %= MOD;x = 1;}}t *= x;t %= MOD;ll m = ans, M = ans;for (int i=0;i<N;i++) {m+=(N-i-1)*arr[i].first;M+=i*arr[i].first;}
cout<<m<<" "<<t<<"\n";for(int i=0;i<N;i++)cout<<arr[N-i-1].second+1<<" ";
cout<<"\n"<<M<<" "<<t<<"\n";for(int i=0;i<N;i++)cout<<arr[i].second+1<<" ";}