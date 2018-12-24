/*
https://github.com/arvindr9/CompetitiveProgramming/blob/master/LiveArchive/LiveArchive%203343.cpp
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,b,p;
ll pw[12];
ll phi(ll x)
{
        ll ret = x;
        if(x%2==0) ret = ret/2;
        if(x%5 == 0) ret = (4*ret)/5;
        return ret;
}
ll newmod(ll x,ll m)
{
        if(x<m) return x;
        return (x%m + m);
}
ll ME(ll nn, ll xx, ll md)
{
        ll ret = newmod(1, md);
        ll h = nn;
        while(xx) {
                if(xx&1) {
                        ret = newmod(ret*h , md);
                }
                h = newmod(h*h, md);
                xx = xx >> 1;
        }
        return ret;
}
ll solve(ll base, ll pwr, ll md)
{
        if(pwr == 0) return newmod(1LL, md);
        else {
                ll x = solve(base, pwr-1, phi(md));
                ll ret = ME(base, x, md);
                return ret;
        }
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        pw[0]=1;
        for(ll i=1;i<=10;i++) pw[i] = pw[i-1] * 10LL;
        while(cin >> b) {
                if(b==0) break;
                cin >> p >> n;
                ll mod = pw[n];
                ll ans = solve(b,p,mod) % mod;
                string ret = to_string(ans);
                while(ret.length() < n) ret = '0' + ret;
                cout << ret << "\n";
        }
        return 0;
}
