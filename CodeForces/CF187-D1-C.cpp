#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
typedef pair<ll,ll> pll;
ll n,m,k;
ll s,t;
vector<ll> g[100005];
ll ok[100005];
ll vis[100005];
const ll inf = 1e9;
bool check(ll x)
{
        queue<pll> q;
        q.push(make_pair(s,0));
        for(ll i=0;i<=n;i++) vis[i]=inf;
        vis[s]=0;
        //ll itr=0;
        while(q.empty()==false) {

                ll u = q.front().first;
                ll dd = q.front().second;
                //cout << u << " " << dd << " " << x << endl;
                q.pop();
                if(dd > x) continue;
                //cout << u << " " << dd << "  " << x << endl;
                if(u==t) return true;
                //itr++;
                //if(itr >= 1000001) return false;
                for(auto i : g[u]) {
                        //if(vis[i]) continue;
                        if(ok[i] && vis[i] > 0 && dd < x){
                                vis[i]=0;
                                q.push(make_pair(i, 0));
                        }else {
                                ll D = dd+1;
                                if(D > x) continue;
                                if(vis[i] <= D) continue;
                                vis[i]=D;
                                q.push(make_pair(i, D));
                        }
                }
        }
        return false;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin>>n>>m>>k;
        for(ll i=1;i<=k;i++){
                ll x; cin>>x;
                ok[x]=1;
        }
        for(ll i=1;i<=m;i++) {
                ll u,v;
                cin>> u >> v;
                g[u].pb(v);
                g[v].pb(u);
        }
        cin>>s >> t;
        if(s==t){
                cout << "0\n"; return 0;
        }
        ll lo=0;
        ll hi=n+10;
        while(hi > lo) {

                ll mid = lo + (hi-lo)/2;
                if(check(mid)) hi=mid;
                else lo= mid+1;
        }
        if(check(lo)) {
                cout << lo << endl;
        }else {
                cout << "-1\n";
        }
        return 0;
}
