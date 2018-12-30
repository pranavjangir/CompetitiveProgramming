#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll n, k, H;
vector< ll > v;
ll a[2002];
ll L1, L2;
ll asks(ll x, ll y, ll z)
{
        cout << "? " << x << " " << y << " " << z << endl;
        string s;
        cin >> s;
        return (s == "Yes");
}
void prints(ll x)
{
        cout << "! " << x << endl; return;
}
ll findleaf()
{
        while(1) {

                shuffle(a+1 , a+n+1 , rng);
                ll lef = a[1];
                ll rnd = a[2];
                ll ok = 1;
                for(ll i=3;i<=n;i++) {
                        ok &= (asks(rnd, lef, a[i]) == 0);
                        if(ok==0) {
                                break;
                        }
                }
                if(!ok) continue;
                return lef;
        }
}
ll findleaf2()
{
        while(1)
        {       v.clear();
                shuffle(a+1,a+n+1, rng);
                ll lef = a[1];
                if(lef == L1) continue;
                ll sz = 0;
                for(ll i=2;i<=n;i++) {
                        if(a[i] == L1) continue;
                        if(asks(L1, a[i], lef)) {
                                sz++;
                                v.pb(a[i]);
                        }
                }
                if(sz == H + H - 1) {
                        return lef;
                }
        }
}
void roots()
{
        vector< ll > path;
        path.clear();
        path.pb(L1);
        path.pb(v[0]);
        path.pb(L2);
        for(ll i=1;i<v.size();i++) {
                ll cur = v[i];
                vector< ll > np;
                np.clear();
                np.pb(path[0]);
                for(ll j=0;j < path.size()-1; j++) {

                        if(asks(path[j] , cur , path[j+1])) {
                                np.pb(cur);
                        }
                        np.pb(path[j+1]);
                }
                path = np;
        }
        prints(path[H]);
}
int main()
{
        cin >> n >> k;
        if(n==1) {
                prints(1); return 0;
        }
        H = -1;
        ll cur = 1;
        ll tot = 0;
        while(tot < n) {

                tot += cur;
                cur = cur * k;
                H++;
        }
        for(ll i=1;i<=n;i++) a[i]=i;
        L1 = findleaf();
        L2 = findleaf2();
        roots();
        return 0;
}
