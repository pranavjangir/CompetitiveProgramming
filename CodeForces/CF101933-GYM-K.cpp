/*
  Apply inclusion exclusion principle, direct application!
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n ,k;
const ll mod = 1e9 + 7;
ll ME(ll x,ll nn,ll M)
{
    ll result=1;
    while(nn>0)
    {
        if(nn % 2 ==1)
            result=(result * x)%M;
        x=(x*x)%M;
        nn=nn/2;
    }
    return result;
}
ll C[3002][3002];
int main()
{
        cin >> n >> k;
        for(ll i=0;i<=n;i++) C[i][0] = 1;
        for(ll i=1;i<=n;i++) {
                for(ll j=1;j<=i;j++) C[i][j] = (C[i-1][j] + C[i-1][j-1])%mod;
        }
        ll ans = k;
        ans = (ans * ME(k-1, n-1, mod))%mod;
        for(ll i=1;i<k-1;i++){
                ll M = 1;
                if(i&1) M = -1;
                ans = (ans + (((M*(k-i)*ME(k-i-1, n-1, mod))%mod)*C[k][i])%mod + mod)%mod;
        }
        cout << ans << endl;
        return 0;
}
