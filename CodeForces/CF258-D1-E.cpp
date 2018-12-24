/*
  Editorial solution: https://codeforces.com/blog/entry/6213
*/
#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
typedef pair<ll,ll> pll;
ll n , m;
vector< ll > g[100005] , q[100005];
pll tree[4000005];
ll lazy[4000005];
inline ll left(ll x)
{
        return x << 1;
}
inline ll right(ll x)
{
        return (x << 1) + 1;
}
void build(ll id,ll l,ll r)
{
        ll mid = (l + r) >> 1;
        if(l == r) {
                tree[id].first = 0;
                tree[id].second = 1; return;
        }
        build(left(id), l , mid);
        build(right(id), mid+1, r);
        tree[id].first = 0;
        tree[id].second = r - l + 1;
}
ll timer;
ll in[100005] , outt[100005];
pll merges(pll lft, pll rgt)
{
        pll nw = {-1,-1};
        if(lft.first < rgt.first){
                nw = lft;
        }else if(rgt.first < lft.first){
                nw = rgt;
        }else {
                nw.first = lft.first;
                nw.second = lft.second + rgt.second;
        }
        return nw;
}
void shift(ll id,ll l,ll r)
{
        if(lazy[id] != 0){
                tree[id].first += lazy[id];
                if(l != r){
                        lazy[left(id)] += lazy[id];
                        lazy[right(id)] += lazy[id];
                }
                lazy[id] = 0;
        }
}
void upd(ll id,ll x,ll y, ll l,ll r,ll val)
{
        shift(id,l,r);
        if(l > y || r < x) return;
        if(l >= x && r <= y) {
                lazy[id] += val;
                shift(id,l,r); return;
        }
        ll mid = (l + r) >> 1;
        upd(left(id), x,y,l,mid,val);
        upd(right(id),x,y,mid+1,r,val);
        tree[id] = merges(tree[left(id)], tree[right(id)]);
}
void dfss(ll s,ll pr)
{
        timer++;
        in[s] = timer;
        for(auto i : g[s]) {
                if(i == pr) continue;
                dfss(i, s);
        }
        outt[s] = timer;
}
ll ans[100005];
void dfs(ll s,ll pr)
{
        for(auto i : q[s]) {
                upd(1, in[i], outt[i], 1 , timer, 1);
        }
        ll MN = tree[1].first;
        if(MN!=0) ans[s] = n-1;
        else {
                ans[s] = max(0LL, n-1-tree[1].second);
        }
        for(auto i : g[s]) {
                if(i == pr) continue;
                dfs(i, s);
        }
        for(auto i : q[s]) {
                upd(1, in[i], outt[i], 1 , timer, -1);
        }
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> m;
        for(ll i=1;i<n;i++) {
                ll a , b;
                cin >> a >> b;
                g[a].pb(b);
                g[b].pb(a);
        }
        dfss(1,-1);
        build(1, 1, timer);
        while(m--){
                ll u, v;
                cin >> u >> v;
                q[u].pb(u);
                q[u].pb(v);
                q[v].pb(v);
                q[v].pb(u);
        }
        dfs(1, -1);
        for(ll i=1;i<=n;i++) cout << ans[i] << " ";
        return 0;
}
