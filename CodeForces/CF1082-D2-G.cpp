/*
  Editorial solution, using capacity constraints!
          https://codeforces.com/blog/entry/63544
*/

#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n, m;
ll a[1003];
vector< ll > g[20002];
ll sum;
ll S;
ll T;
const ll inf = 1e16;
ll vis[3003];
ll cur;
class edge
{
public:
        ll to, c, f;
        edge(){};
        edge(ll tt, ll cc, ll ff)
        {
                to = tt; c = cc; f = ff;
        }

};
vector< edge > e;
void addedge(ll u, ll v, ll ca)
{
        g[u].pb(e.size());
        edge nw(v , ca, 0);
        e.pb(nw);
        g[v].pb(e.size());
        edge nww(u , 0, 0);
        e.pb(nww);
}
ll dfs(ll s, ll k)
{
        if(s == T) return k;
        //if(vis[s] == cur) return 0;
        vis[s] = cur;
        for(auto i : g[s]) {
                ll to = e[i].to;
                ll cap = e[i].c;
                ll flo = e[i].f;
                if(vis[to] != cur) {
                        if((cap - flo) >= k) {
                                ll nxt = dfs(to , k);
                                if(nxt > 0) {
                                        e[i].f += nxt;
                                        e[(i^1)].f -= nxt;
                                        return nxt;
                                }
                        }
                }
        }
        return 0;
}
ll enlarge(ll k)
{
        ll ret = 0;
        while(1)
        {
                ++cur;
                ll h = dfs(S , k);
                ret += h;
                if(h==0) break;
                //cout << k << " --->" << h << endl;
        }
        return ret;
}
ll flow()
{
        ll ret = 0LL;
        for(ll i = (1LL << 30); i > 0; i = (i >> 1)) {
                ret += enlarge(i);
        }
        return ret;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> m;
        S = 0;
        T = n + m + 5;
        for(ll i=1;i<=n;i++) {
                cin >> a[i];
                addedge(m + i , T , a[i]);
        }
        for(ll i=1;i<=m;i++) {
                ll u, v, w;
                cin >> u >> v >> w;
                sum += w;
                addedge(i , u + m , inf);
                addedge(i, v + m , inf);
                addedge(S , i , w);
        }
        ll yo = flow();
        //cout << yo << endl; return 0;
        cout << sum - yo << endl;
        return 0;
}
