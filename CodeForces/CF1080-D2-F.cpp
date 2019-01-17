#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pb push_back
ll n,m,k;
typedef pair<ll,ll> pll;
vector< pair< pll, ll > > e;
ll cur = 0;
const ll NOTS = 0;
ll MAXM = 1e10 + 2;
struct node
{
        ll L, R, val;
        ll lft , rgt;
        node()
        {
                L = R = val = lft = rgt = 0;
                val = MAXM;
        }
        node(ll l, ll r , ll lftt , ll rgtt , ll v)
        {
                L = l; R = r; val = v;
                lft = lftt;
                rgt = rgtt;
        }
};
node tree[400005 * 20];
ll root[400005];
ll newnode(ll l, ll r , ll lf , ll rg , ll vv)
{
        ++cur;
        tree[cur].L = l;
        tree[cur].R = r;
        tree[cur].val = vv;
        tree[cur].lft = lf;
        tree[cur].rgt = rg;
        return cur;
}
void upd(ll &curnode , ll prvnode ,ll l, ll r,  ll pos, ll v)
{
        if(l == r) {
                if(prvnode != 0 && tree[prvnode].val <= v) {
                        curnode = prvnode; return;
                }
                curnode = newnode(l,r,NOTS, NOTS, v);
                return;
        }
        ll mid = ( l + r) >> 1;
        if(pos <= mid) {

                curnode = newnode(l, r , NOTS , tree[prvnode].rgt , 0);
                upd(tree[curnode].lft , tree[prvnode].lft , l , mid , pos , v);
        }else {
                curnode = newnode(l,r , tree[prvnode].lft , NOTS , 0);
                upd(tree[curnode].rgt , tree[prvnode].rgt , mid+1 , r , pos, v);
        }
                ll XL = tree[curnode].lft;
                ll XR = tree[curnode].rgt;
        //if(tree[curnode].lft != NOTS && tree[curnode].rgt != NULL) {

                tree[curnode].val = max(tree[XL].val , tree[XR].val);
        //}else if
}
ll qry(ll curnode , ll l ,ll r , ll x , ll y)
{
        if(l > y || r < x) return 0;
        if(curnode == NOTS) return MAXM;
        if(l >= x && r <= y) return tree[curnode].val;
        ll mid = (l + r) >> 1;
        return max(qry(tree[curnode].lft , l , mid , x , y) , qry(tree[curnode].rgt , mid+1 , r , x , y));
}
int main()
{
        cin >> n >> m >> k;
        for(ll i=1;i<=k;i++) {
                ll l ,r , p;
                cin >> l >> r >> p;
                e.pb(make_pair(make_pair(l , r) , p));
        }
        sort(e.begin() , e.end());
        ll sz = e.size();
        root[sz] = NOTS;
        for(ll i = sz-1; i >= 0 ; i--) {

                ll l = e[i].first.first;
                ll r = e[i].first.second;
                ll id = e[i].second;
                root[i] = root[i + 1];
                upd(root[i] , root[i + 1],1,n , id , r);
        }
        //for(auto i : e) cout << i.first.first << " " << i.first.second << " " << i.second << endl;
        while(m--) {

                ll a,b,x,y;
                cin >> a >> b >> x >> y;
                ll pos = lower_bound(e.begin() , e.end() , make_pair(make_pair(x , 0LL) , 0LL)) - e.begin();
                //cout << pos << "**** " << endl;
                //cout << qry(root[pos] , 1 , n , a , b) << " ---- " << endl;
                if(pos >= sz) {
                        cout << "no" << endl;
                }else {
                        if(qry(root[pos] , 1 , n , a , b) > y) {
                                cout << "no" << endl;
                        }else {
                                cout << "yes" << endl;
                        }
                }
        }
        return 0;
}
