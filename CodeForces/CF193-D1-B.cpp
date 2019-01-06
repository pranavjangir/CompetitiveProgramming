#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n,u,r;
ll a[35] , b[35], k[35], p[35];
ll ans;
ll calc(vector<ll> &t)
{
        ll ret=0;
        assert(t.size()== n+1);
        for(ll i=1;i<=n;i++) {
                ret+= t[i]*k[i];
        }
        return ret;
}
void solve(ll pst, vector<ll> c, ll m)
{
        if(m%2 == 0) {
                ans = max(ans,calc(c));
                if(m==0) return;
        }
        vector<ll> t;
        t.clear(); t.pb(0);
        for(ll i=1;i<=n;i++) {
                t.pb(c[p[i]] + r);
        }
        solve(0, t, m-1);
        if(pst==1) return;
        t.clear(); t.pb(0);
        for(ll i=1;i<=n;i++) {
                t.pb(c[i]^b[i]);
        }
        solve(1, t,m-1);
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> u >> r;
        ans = -1e16;
        vector<ll> v;
        v.pb(0);
        for(ll i=1;i<=n;i++){
                cin>>a[i];
                v.pb(a[i]);
        }

         for(ll i=1;i<=n;i++){
                cin>>b[i];
        }

         for(ll i=1;i<=n;i++){
                cin>>k[i];
        }

         for(ll i=1;i<=n;i++){
                cin>>p[i];
        }
        // 0 - no restriction
        solve(0LL,v,u);
        cout << ans << endl;
        return 0;
}
