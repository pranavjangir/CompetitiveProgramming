#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n , t;
ll sum[505];
ll curt;
ll parity(ll x)
{
        return ((x%2) + 2)%2;
}
ll asks(ll i, ll j)
{
        cout << "? " << i << " " << j << endl;
        ll x;
        cin >> x;
        if(x == -1) assert(true == false);
        return x;
}
ll getR(ll i, ll j, ll ss)
{
        ll ret = 0;
        ll req = 0;
        ll t[2] = {0,0};
        if(ss == 0) {
                req = j%2;
        }else req = (n-i+1)%2;
        ll lft = 0;
        ll rgt = 0;
        if(ss == 0){
                lft = req;
                rgt = 1 - lft;
        }else {
                rgt = req;
                lft = 1 - req;
        }
        while(1) {
                ll nwt = asks(i,j);
                //cout << nwt << "---" << curt << endl;
                if(parity(nwt-curt) == lft) t[lft] = t[lft]^1;
                else t[rgt] = t[rgt]^1;
                curt = nwt;
                if(t[req] == 1 && t[1-req] == 0) break;
                //cout << ss << " " << par << endl;
        }
        return curt;
}
int main()
{
        cin >> n >> t;
        curt = t;
        if(n==1){
                if(t) cout << "! 1" << endl;
                else cout << "! 0" << endl;
                return 0;
        }
        if(n%2 == 0) {
                for(ll i=1;i<=n;i++) {
                        ll N = getR(i , i, 0);
                        sum[i] = (i + t - N)/2;
                        N = getR(i, i, 0);
                }
        }else {
                ll N = getR(2 , n, 1);
                sum[1] = (t + N - n + 1)/2;
                N = getR(2,n,1);
                for(ll i=1;i<n;i++) {
                        N = getR(i,i+1, 0);
                        sum[i+1] = (i + t - N + 1)/2;
                        N = getR(i,i+1,0);
                }
        }
        cout <<"! ";
        for(ll i=1;i<=n;i++) {
                if(sum[i] - sum[i-1] > 0) cout << "1";
                else cout << "0";
        }
        cout << endl;
        return 0;
}
