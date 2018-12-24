/*
  There was no editorial , so my solution:
  basic combinatorics, the answer is actually 
  Summation(r from 0 to n1) of (Summation(i from 0 to n1) of (C(n2, r-i) * C(n1, n1-i)))
  where n1 = number of smaller elemetns than our given number and n2 = number of bigger elements!
  By using pascal's extended formula, our form becomes
  summation(r from 0 to n1) C(n-1, r)  .... (( using n1+n2 = n-1)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef pair<ll,ll> pll;
ll n, k;
map<ll,ll> mp;
const ll mod = 1e9 + 7;
ll ans[100005], a[100005];
ll fac[100005];
ll ifac[100005];
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
ll inv(ll x)
{
        return ME(x, mod-2, mod);
}
void pre()
{
        fac[0] = 1;
        ifac[0] = 1;
        for(ll i=1;i<=n;i++) {
                fac[i] = (fac[i-1] * i)%mod;
                ifac[i] = (ifac[i-1] * inv(i))%mod;
        }
}
ll C(ll x, ll y)
{
        if(y > x) return 0LL;
        return ((fac[x] * ifac[y])%mod * ifac[x-y])%mod;
}
int main()
{
        ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
        cin >> n >> k;
        pre();
        for(ll i=1;i<=n;i++) {
                cin >> a[i];
        }
        sort(a+1, a+n+1);
        for(ll i=1;i<=n;i++) mp[a[i]] = i;
        ll cur = 0;
        for(ll i=1;i<=n;i++) {
                ll S = i-1;
                cur = (cur + C(n-1, S))%mod;
                ans[i] = cur;
        }
        for(ll i=1;i<=k;i++) {
                        ll x;
                cin >> x;
                ll id = mp[x];
                cout << ans[id] << "\n";
        }
        return 0;
}
