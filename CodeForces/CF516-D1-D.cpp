/*
        Editorial solution:
                Basically we will first find the farthest distance for all the vertices
                and then sort them.
                After sorting, we will add them one by one starting from the largest one(highest distance)
                using 2 pointers, keeping a window such that all elements inside that window are within 'L' distance

https://codeforces.com/blog/entry/16468
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef pair<ll,ll> pll;
#define pb push_back
ll n;
vector< pll > g[100005];
ll q;
pll dpd[100005];
ll dp[100005];
vector< pll > v;
void dfs(ll s ,ll pr)
{
        dpd[s] = make_pair(0, 0);
        for(auto i : g[s]) {
                if(i.first == pr) continue;
                dfs(i.first, s);
                ll D = dpd[i.first].first + i.second;
                if(dpd[s].first < D) {
                        dpd[s].second = dpd[s].first;
                        dpd[s].first = D;
                }else if(dpd[s].first == D) {
                        dpd[s].second = dpd[s].first;
                }else {
                        if(D > dpd[s].second) dpd[s].second = D;
                }
        }
}
void dfs2(ll s, ll pr, ll W)
{
        dp[s] = 0;
        if(s != 1) {

                ll D = W + dp[pr];
                dp[s] = D;
                D = W;
                if(D + dpd[s].first == dpd[pr].first) D += dpd[pr].second;
                else D += dpd[pr].first;
                dp[s] = max(dp[s], D);
        }
        for(auto i : g[s]) {
                if(i.first != pr) {
                        dfs2(i.first, s, i.second);
                }
        }
}
ll ans;
ll p[100005], sz[100005], rnk[100005];
ll par[100005];
void init()
{
        for(ll i=1;i<=n;i++) {
                p[i] = i; sz[i] = 1; rnk[i] = 1;
        }
        ans = 0;
}
bool used[100005];
ll fs(ll x)
{
        return p[x] == x ? x : p[x] = fs(p[x]);
}
void ms(ll x, ll y)
{
        x = fs(x);
        y = fs(y);
        if(rnk[x] > rnk[y]) {
                sz[x] += sz[y];
                rnk[x] += rnk[y];
                p[y] = x;
        }else {
                sz[y] += sz[x];
                rnk[y] += rnk[x];
                p[x] = y;
        }
}
bool sames(ll x, ll y)
{
        if(fs(x) == fs(y)) return true;
        return false;
}
ll solve(ll l){
        memset(p, 0, sizeof p);
        memset(sz, 0, sizeof sz);
        memset(rnk, 0, sizeof rnk);
        init();
        ll q = v.size()-1;
        for(ll i = v.size()-1; i >= 0 ; i--) {
                ll ye = v[i].second;
                //used[ ye ] = true;
                for(auto i : g[ye]) {
                        if(i.first == par[ye]) {
                                continue;
                        }
                        //cout << ye << " " << i.first << endl;
                        ms(ye, i.first);
                }
                //cout << sz[4] << endl;
                while(v[q].first - v[i].first > l) {
                        //if(i == 0) cout << fs(v[q].second) << " --- " << v[q].second << endl;
                        sz[fs(v[q].second)]--;
                        q--;
                }
                //if(i==0) cout << p[4] << " " << p[5] << " "<<fs(ye) << endl;;
                ans = max(ans , sz[fs(ye)]);
        }
        return ans;

}
void go(ll s, ll pr)
{
        par[s] = pr;
        for(auto i : g[s]) {
                if(i.first == pr) continue;
                go(i.first, s);
        }
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n;
        for(ll i=1;i<n;i++) {
                ll x , y , v;
                cin >> x >> y >> v;
                g[x].pb(make_pair(y, v));
                g[y].pb(make_pair(x, v));
        }
        //return 0;
        dfs(1 , -1); //return 0;
        dfs2(1, -1, 0);
        for(ll i=1;i<=n;i++) dp[i] = max(dp[i] , dpd[i].first);
        ll root = min_element(dp+1, dp+n+1) - dp;
        go(root, root);
        cin >> q;
        v.clear();
        for(ll i=1;i<=n;i++) {
                v.pb(make_pair(dp[i], i));
        }
        sort(v.begin(), v.end());
        while(q--) {
        ll l;
                cin >> l;
                cout << solve(l) << "\n";
        }
        return 0;
}
