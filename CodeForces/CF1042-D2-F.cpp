/*
        Very nice problem, merging sets + little optimization to make it run in O(nlogn)
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pb push_back
ll n , k;
const ll N = 1e6 + 10;
vector< ll > g[N];
ll ans;
ll dfs(ll s,ll pr)
{
        vector< ll > cc;
        cc.clear();
        if(g[s].size()==1) return 0LL;
        for(auto i : g[s]) {
                if(i==pr) continue;
                cc.pb(dfs(i,s) + 1);
        }
        sort(cc.begin(), cc.end());
        while(cc.size() > 1) {
                ll lst = cc.back();
                ll sl = cc[cc.size()-2];
                if(lst + sl <= k) break;
                ans++;
                cc.pop_back();
        }
        assert(cc.size() > 0);
        return cc.back();
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> k;
        for(ll i=1;i<n;i++) {
                ll u,v;
                cin >> u >> v;
                g[u].pb(v); g[v].pb(u);
        }
        for(ll i=1;i<=n;i++) {
                if(g[i].size()>1){
                        dfs(i,-1); break;
                }
        }
        cout << ans + 1 << endl;
        return 0;
}
