/*
  Easy problem on BIT trees, editorial : https://codeforces.com/blog/entry/49186
*/
#include <bits/stdc++.h>
typedef long double ld;
typedef long long ll;
using namespace std;
ll n;
ll a[100005];
class BIT
{
public:
        vector<ll> tree;
        BIT(){
                tree.resize(200005, 0LL);
        }
        void upd(ll x,ll v)
        {
                for(;x<=n;x += (x&(-x))) tree[x] += v;
        }
        ll qry(ll x)
        {
                ll sum = 0;
                for(;x>0;x -= (x&(-x))) sum += tree[x];
                return sum;
        }
};
ll gets(ll l,ll r, BIT &A)
{
        ll ans = A.qry(r);
        ans -= A.qry(l-1);
        return ans;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cout << setprecision(10) << fixed;
        cin >> n;
        for(ll i=1;i<=n;i++) cin >> a[i];
        BIT A;
        A.upd(a[1], 1);
        ll inv=0;
        for(ll i=2;i<=n;i++) {
                inv += gets(a[i] , n, A);
                A.upd(a[i], 1);
        }
        ll ans = 0;
        BIT B;
        B.upd(a[1], 1);
        for(ll j=2;j<=n;j++) {

                ll smol = gets(1 , a[j] , B);
                ll lrg = gets(a[j] , n , B);
                ll ret = (n - j + 1)*(smol - lrg);
                ans += ret;
                B.upd(a[j] , j);
        }
        ld aa = (ans);
        aa /= (ld)(1.0*n*(1.0*n + 1.0));
        aa += inv;
        cout << aa << endl;
        return 0;
}
