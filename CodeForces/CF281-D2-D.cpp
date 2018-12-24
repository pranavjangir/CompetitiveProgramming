#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n;
ll a[100005];
vector< ll > v;
map<ll ,ll> mp;
const ll INVAL = -1e18;
ll b[400005];
inline ll left(ll x)
{
        return x << 1;
}
inline ll right(ll x)
{
        return (x << 1) + 1;
}
class segMax
{
public:
        vector< ll > tree;
        segMax()
        {
                tree.resize(400005, 0);
        }
        void upd(ll id ,ll x, ll l,ll r, ll val)
        {
                if(l == r && l == x){
                        tree[id] = val;
                        //b[l] = val;
                        return;
                }
                ll mid= (l + r) >> 1;
                //cout << "xDD\n\n";
                if(x <= mid) upd(left(id), x, l , mid, val);
                else upd(right(id), x, mid+1, r, val);
                tree[id] = max(tree[left(id)] , tree[right(id)]);
        }
        ll qry(ll id, ll x, ll y,ll l, ll r)
        {
                if(l > y || r < x) return 0;
                if(l >= x && r <= y) return tree[id];
                ll mid = (l + r) >> 1;
                ll X = qry(left(id), x,y,l,mid);
                ll Y = qry(right(id),x,y,mid+1,r);
                return max(X,Y);
        }
};

class segMin
{
public:
        vector< ll > tree;
        segMin()
        {
                tree.resize(400005, n*n);
        }
        void upd(ll id ,ll x, ll l,ll r, ll val)
        {
                if(l == r && l == x){
                        tree[id] = val;
                        //b[l] = val;
                        return;
                }
                ll mid= (l + r) >> 1;
                //cout << "xDD\n\n";
                if(x <= mid) upd(left(id), x, l , mid, val);
                else upd(right(id), x, mid+1, r, val);
                tree[id] = min(tree[left(id)] , tree[right(id)]);
        }
        ll qry(ll id, ll x, ll y,ll l, ll r)
        {
                if(l > y || r < x) return n*n;
                if(l >= x && r <= y) return tree[id];
                ll mid = (l + r) >> 1;
                ll X = qry(left(id), x,y,l,mid);
                ll Y = qry(right(id),x,y,mid+1,r);
                return min(X,Y);
        }
};
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n;
        for(ll i=1;i<=n;i++) {
                cin >> a[i];
                v.push_back(a[i]);
                mp[ a[i] ] = i;
        }
        sort(v.begin(), v.end());
        ll ans = 0;
        segMax A;
        segMin B;
        while(v.size() > 0) {

                ll u = v.back();
                ll pos = mp[u];
                ll L = INVAL;
                ll R = INVAL;
                if(pos != 1) L = A.qry(1,1,pos-1,1,n);
                if(pos != n) R = B.qry(1,pos+1, n,1,n);
                //cout << L << " " << R << endl;
                if(L >= 1 && L <= n) ans = max(ans , (u^b[L]));
                if(R <= n && R >= 1) ans = max(ans , (u^b[R]));
                A.upd(1 , pos, 1 , n , pos);
                B.upd(1,pos,1,n,pos);
                b[pos] = u;
                v.pop_back();
        }
        cout << ans << endl;
        return 0;
}
