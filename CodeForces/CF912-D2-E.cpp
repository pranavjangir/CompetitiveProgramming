#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n, k;
ll a[20];
vector< ll > P , Q;
ll inf = 2e18;
ll cnt(ll x)
{
        ll p = P.size()-1;
        ll q = 0;
        ll ret = 0;
        while(p >= 0) {
                while(q < Q.size() && P[p] <= (x / Q[q])) q++;
                ret += q;
                p--;
        }
        return ret;
}
void solve(ll id,vector<ll> &primes, vector<ll> &X, ll cur,ll ch)
{
        if(id >= primes.size()) {
                if(ch==0) X.pb(cur);
                return;
        }
        if(ch==0) {
                X.pb(cur);
        }
        solve(id+1, primes, X, cur, 1);
        ll yo = primes[id];
        for(ll i=1;i<=60;i++) {
                if(cur <= (inf / yo)) {
                        solve(id+1, primes, X, cur*yo, 0);
                        yo = yo * primes[id];
                }else {
                        return;
                }
        }
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n;
        for(ll i=1;i<=n;i++) {
                cin >> a[i];
        }
        cin >> k;
        if(k==1) {
                cout << k << endl; return 0;
        }
        if(n==1) {
                ll ans = 1LL; k--;
                while(k--) ans *= a[1];
                cout << ans << "\n"; return 0;
        }
        sort(a+1, a + n + 1);
        vector< ll > A;
        A.clear();
        for(ll i=1;i<=n;i += 2) A.pb(a[i]);
        vector< ll > B;
        B.clear();
        for(ll i=2;i<=n;i += 2) B.pb(a[i]);
        if(A.size()) solve(0, A, P, 1LL, 0);
        if(B.size()) solve(0, B, Q, 1LL, 0);
        if(P.size()) sort(P.begin(), P.end());
        if(Q.size()) sort(Q.begin(), Q.end());
        ll lo = 1;
        ll hi = 1e18;
        while(hi > lo) {
                ll mid = lo +(hi - lo + 1)/2;
                if(cnt(mid) < k) lo = mid;
                else hi = mid - 1;
        }
        cout << hi+1 << endl;
        return 0;
}
