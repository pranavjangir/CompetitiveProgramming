/*
  Editorial solution : https://codeforces.com/blog/entry/61356
*/

#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n , m, k;
ll par[500005];
ll p[500005];
ll high[500005] , dep[500005];
bool vis[500005];
bool ok[500005];
void init()
{
        for(ll i=1;i<=n;i++) p[i] = i;
}
class edge
{
public:
        ll u,v,c;
        edge() {}
        edge(ll uu, ll vv, ll cc) {
                u = uu; v=vv; c=cc;
        }
};
vector< edge > e;
ll a[500005] , b[500005] , w[500005];
vector< ll > g[500005];
void dfs(ll s,ll pp)
{
        if(vis[s]) return;
        vis[s] = true;
        //cout << "YOO\n";
        par[s] = pp;
        if(pp == -1) dep[s]=0;
        else dep[s] = dep[pp]+1;
        for(auto i : g[s]) {
                ll to = e[i].v;
                ll cool = e[i].c;
                if(to == pp) continue;
                if(vis[to]==false) {
                        dfs(to,s);
                        if(cool) ok[to] = true;
                }
        }
}
ll fs(ll x)
{
        return p[x]==x ? x : p[x] = fs(p[x]);
}
void ms(ll x,ll y)
{
        x = fs(x); y = fs(y);
        if(x==y) return;
        p[y] = x;
}
void ms2(ll x,ll y)
{
        x = fs(x); y = fs(y);
        if(x==y) return;
        ll yo = 0;
        if(dep[high[x]] < dep[high[y]]) yo = high[x];
        else yo = high[y];
        high[x] = yo;
        high[y] = yo;
        p[y]=x;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> k >> m;
        init();
        for(ll i=1;i<=k;i++) {
                ll u , v;
                cin >> u >> v;
                edge x(u,v,1);
                g[u].pb(e.size());
                e.pb(x);
                edge xx(v,u,1);
                g[v].pb(e.size());
                e.pb(xx);
                ms(u,v);
        }
        for(ll i=1;i<=m;i++) {
                cin >> a[i] >> b[i] >> w[i];
                if(fs(a[i]) == fs(b[i])) continue;
                else {
                        edge x(a[i] , b[i] , 0);
                        g[a[i]].pb(e.size()); e.pb(x);
                        edge xx(b[i], a[i], 0);
                        g[b[i]].pb(e.size()); e.pb(xx);
                        ms(a[i], b[i]);
                }
        }
        init();
        for(ll i=1;i<=n;i++) high[i]=i;
        dfs(1,-1);
        //cout << "DONE\n";
        ll ans = 0;
        ll used=0;
        for(ll i=1;i<=m;i++) {

                ll X = a[i];
                ll Y = b[i];
                ll W = w[i];
                //cout << X << " " << Y << " " << W << endl;
                X = high[fs(X)];
                Y = high[fs(Y)];
                while(X != Y) {
                        if(dep[X] < dep[Y]) swap(X,Y);
                        if(ok[X]){
                                ans += W;
                                used++;
                        }
                        ll P = fs(par[X]);
                        //cout << X << " " << P << endl;
                        ms2(X, P);
                        X = high[fs(X)];
                        //cout << "--" << X << endl;
                }
        }
        if(used == k) cout << ans << endl;
        else cout << "-1\n";
        return 0;
}
