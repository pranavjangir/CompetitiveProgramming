#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n;
ll a[105];
vector< ll > mers;
map<ll,ll> mp;
bool isprime(ll x)
{
        for(ll i=2;i*i <= x;i++) {
                if(x%i==0) return false;
        }
        return true;
}
ll dp[105][1LL << 8];
ll solve(ll id,ll mask)
{
        if(id==n+1) {
                return 0;
        }
        if(dp[id][mask] != -1) return dp[id][mask];
        ll &ret = dp[id][mask];
        ret = solve(id+1, mask);
        ll nm = 0;
        ll tmp = a[id];
        ll c=0;
        for(ll i=0;i<mers.size();i++) {
                ll cnt = 0;
                while(tmp%mers[i] == 0) {
                        tmp /= mers[i];
                        cnt++;
                }
                if(cnt > 1) return ret;
                if(cnt==1){
                nm |= (1LL << i);
                c += mp[mers[i]];
                }
        }
        if((nm&mask)) return ret;
        if(tmp > 1) return ret;
        ret = max(ret , solve(id+1, mask|nm) + c);
        return ret;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        for(ll i=2;i<=31;i++) {
                if(isprime((1LL << i) - 1)) {
                        mp[(1LL << i) - 1] = i;
                        mers.pb((1LL<<i)-1);
                }
        }
        while(cin >> n)
        {
                for(ll i=1;i<=n;i++) cin >> a[i];
                memset(dp,-1,sizeof dp);
                ll ans = solve(1, 0);
                if(ans==0){
                        cout << "NO\n"; continue;
                }
                cout << ans << "\n";
        }
        return 0;
}
