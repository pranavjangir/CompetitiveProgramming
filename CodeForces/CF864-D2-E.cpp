#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n;
ll t[105] , d[105], p[105];
ll a[105];
bool cmp(ll x,ll y)
{
        return d[x] < d[y];
}
ll dp[102][2002];
vector<ll> e;
const ll inf=1e16;
ll solve(ll id,ll tt)
{
        if(tt > 2000) return -inf;
        if(id==n+1) {
                return 0;
        }
        if(dp[id][tt] != -1) return dp[id][tt];
        ll &ret = dp[id][tt];
        ret = solve(id+1,tt);
        if(tt + t[a[id]] < d[a[id]]) ret = max(ret, solve(id+1, tt + t[a[id]])  + p[a[id]]);
        return ret;
}
void trace(ll id, ll tt)
{
        if(id==n+1) return;
        ll opt = solve(id, tt);
        if(opt == solve(id+1, tt)) {
                trace(id+1,tt); return;
        }else {
                e.pb(a[id]);
                trace(id+1, tt + t[a[id]]);
                return;
        }
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin>>n;
        for(ll i=1;i<=n;i++) {

                cin >> t[i] >> d[i] >> p[i];
                a[i]=i;
        }
        sort(a+1, a+n+1, cmp);
        memset(dp,-1,sizeof dp);
        ll ans = solve(1, 0);
        cout << ans << endl;
        trace(1,0);
        cout << e.size() << "\n";
        for(auto i : e) cout << i << " ";
        return 0;
}
