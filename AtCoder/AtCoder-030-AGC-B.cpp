#include <bits/stdc++.h>
typedef long long ll;
#define pb push_back
using namespace std;
ll L , n;
ll a[200005];
ll p[200005];
ll s[200005];
ll solve()
{
        ll ans = 0;
        for(ll i=1;i<=n;i++) p[i] = a[i] + p[i-1];
        for(ll i=n;i>=0;i--) s[i] = s[i+1] + a[i];
        for(ll i=1;i <= n; i++) {
                ll ret = 0;
                ll len = n - i;
                ll tails = (len + 1)/2;
                tails = n - tails + 1;
                ret = len*L;
                if(len%2 == 1) {

                        ret += 2*(p[tails-1] - p[i-1]);
                        ret -= 2*(s[tails]) - a[tails];
                }else {
                        ret += 2*(p[tails-1] - p[i-1]) - a[tails-1];
                        ret -= 2*(s[tails]);
                }
                ans = max(ans, ret);

        }
        return ans;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> L >> n;
        for(ll i=1;i<=n;i++) cin >> a[i];
        ll ans = solve();
        for(ll i=1;i<=n;i++) a[i] = L - a[i];
        sort(a+1, a+n+1);
        ans = max(ans , solve());
        cout << ans << endl;
        return 0;
}
