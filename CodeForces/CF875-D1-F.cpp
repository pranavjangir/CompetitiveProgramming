/*
  Very nice problem, first it should be clear that greedily taking princesses by their dowry is optimal
                    Next question is which prince to take?
                    The answer depends on future coming princesses choices of princes..,
                    let current princess likes 'a' and 'b' princes,
                    then we add edge between 'a' and 'b'
                    We follow the given algo -->
                    
                    1) first let's sort princesses as in editorial

                    2) then if we take princess i, we make edge from ai to bi

                    3) then we can add new princess, if and only if graph, which we got, has no component,
                    that has n vericles and > n edges, so you need only check it with dsu
                    
                    https://codeforces.com/blog/entry/55201?#comment-390974
*/

#include <bits/stdc++.h>
typedef long long ll;
#define pb push_back
using namespace std;
ll n,m;
ll p[200005];
ll used[200005];
vector< pair<ll, pair<ll,ll> > > v;
ll fs(ll x)
{
        return p[x] == x ? x  : p[x] = fs(p[x]);
}
bool check(ll x,ll y)
{
        x = fs(x); y = fs(y);
        if(x==y) {
                if(used[x]) return false;
                used[x] = true;
                return true;
        }else {

                if(used[x] && used[y]) return false;
                p[y] = x;
                if(used[x] || used[y]) used[x] = true;
                return true;
        }
        return false;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> m;
        for(ll i=1;i<=n;i++) {
                p[i]=i;
                used[i]=false;
        }
        for(ll i=1;i<=m;i++) {

                ll x,y,z;
                cin >> x >> y >> z;
                v.pb(make_pair(z, make_pair(x,y)));
        }
        sort(v.rbegin(), v.rend());
        ll ans = 0;
        for(auto i : v) {

                 ll w = i.first;
                 ll x = i.second.first;
                 ll y = i.second.second;
                 if(check(x,y)) {
                        ans += w;
                 }
        }
        cout << ans << endl;
        return 0;
}
