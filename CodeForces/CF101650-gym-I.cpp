/*
  A troublesome problem, got a lot of WAs
  Soltion: Make a graph ..
        Suppose there is just one connected component, the case for multiple components is same, just initialize the answer with 
        'number of Connected Components'
        Now if there is just one Connected component:-
        iterate through that connected component if degree of a vertex is odd, this means that its either 1,3,5..
        Now its final degree is going to be '2' exactly, so if current degree < 2 this means we need to connect it to something else..
        If degree > 2, this means we should first reduce it to 1 by 'dismembering others'
        so we increase odds by 1 if DEGREE[i]%2 = 1
        and for above reason if degree is > 2, we increase 'twos' counter by 1 as well
        Now answer = (odd/2) + twos.
        WHY? - We pair 2 odd degree edges together to connect them, so degree becomes 2, and twos was the cost of dismembering
        degrees > 2.
        
*/
#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n,m;
vector< ll > g[200005];
ll color[200005];
ll d[200005];
ll cols;
ll odds[200005];
void dfs(ll s, ll C)
{
        if(color[s] > 0) return;
        color[s] = C;
        for(auto i : g[s]) {
                if(color[i] == 0 && i != 0) dfs(i, C);
                else if(i == 0) {
                        odds[C]++;
                }
        }
}
vector< ll > comp[200005];
ll yo;
ll kk = 0;
int main()
{
       cin >> n >> m;
       color[0] = 1e16;
        for(ll i=1;i<=m;i++) {

                ll u,v;
                cin >> u >> v;
                if(u==0) u = ++kk + n;
                if(v==0) v = ++kk + n;
                g[u].pb(v); g[v].pb(u);
                d[u]++; d[v]++;
        }
        n = n + kk;
        for(ll i=1;i<=n;i++) {
                if(color[i]==0 && g[i].size() > 0) {

                        dfs(i , ++cols);
                }
        }
        for(ll i=1;i<=n;i++) comp[ color[i] ].pb(i);
        if(cols == 1) {
                ll ans = 0;
                ll odd = odds[1];
                ll twos = 0;
                for(auto i : comp[1]) {

                        if(d[i]%2 == 1) odd++;
                        if(d[i] > 2) twos++;
                }
                ans = (odd/2) + twos;
                if(odd==0 && twos ==0 && yo>0) {
                        ans += yo + 2;
                }
                cout << ans << "\n";
        }else {

                ll ans = cols + yo;
                for(ll i=1;i<=cols;i++) {
                        ll odd = odds[i];
                        ll twos = 0;
                        ll tot = 0;
                        for(auto j : comp[i] ) {

                                if(d[j]%2 == 1) odd++;
                                if(d[j] > 2) twos++;
                                tot += d[j];
                        }
                        if(odd) ans--;
                        else if(odd == 0 && twos == 0) {
                                if(tot) ans++;
                                else ans--;
                                continue;
                        }
                        ans += (odd/2) + twos;
                }
                cout << ans << "\n";
        }
        return 0;
}
