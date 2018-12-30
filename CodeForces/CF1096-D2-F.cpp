#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n;
ll p[200005];
const ll mod = 998244353;
ll ME(ll x,ll nn,ll M)
{
    ll result=1;
    while(nn>0)
    {
        if(nn % 2 ==1)
            result=(result * x)%M;
        x=(x*x)%M;
        nn=nn/2;
    }
    return result;
}
ll inv(ll x)
{
        return ME(x, mod-2, mod);
}
class BIT
{
public:
        vector<ll> tree;
        BIT(){
                tree.resize(300005, 0LL);
        }
        ll qry(ll x)
        {
                ll sum=0;
                for(;x>0;x -= (x&(-x))) sum += tree[x];
                return sum;
        }
        void upd(ll x,ll v)
        {
                for(;x <= n; x+= (x&(-x))) tree[x] += v;
        }
};
BIT ft;
ll getans(ll l, ll r)
{
        return ft.qry(r) - ft.qry(l-1);
}
ll gaps;
ll seens[200005];
int main()
{
        cin >> n;
        ll ans = 0;
        for(ll i=1;i<=n;i++) {
                cin >> p[i];
                if(p[i] != -1) {

                        ans += getans(p[i], n);
                        ft.upd(p[i], 1);
                        seens[p[i]] = 1;
                }else {
                        gaps++;
                }
        }
        ll lft = 0;
        ll rgt = gaps;
        //cout << ft.qry(n) << endl;
        //cout << ans << endl;
        ft.tree.clear();
        ft.tree.resize(300005, 0LL);
        for(ll i=1; i <= n;i++) {
                if(seens[i] == 0) {
                        //cout <<".... "<< i << endl;
                        ft.upd(i, 1LL);
                        //cout << "**** " << ft.qry(i) << endl;
                }
        }
        //cout << getans(1, n) << endl;
        ll yo = inv(gaps);
        for(ll i=1;i<=n;i++) {

                if(p[i] == -1) {
                        lft += 1;
                        rgt -= 1; continue;
                }
                ll bgs = getans(p[i] , n);
                ll sml = getans(1 , p[i]);
                ans = (ans + (((bgs*lft)%mod)*yo)%mod)%mod;
                ans = (ans + (((sml*rgt)%mod)*yo)%mod)%mod;
        }
        ll uk = ft.qry(n);
        ll haha = uk*(uk-1)/2;
        haha %= mod;
        haha = (haha * inv(2) )%mod;

        //cout << uk <<  " " << haha << endl;
        cout << (ans + haha)%mod << endl;
        return 0;
}
