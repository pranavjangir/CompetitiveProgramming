#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n;
ll a[300005];
vector< ll > g[300005];
ll ans , K;
ll dp[300005];
void dfs(ll s, ll pr)
{
        dp[s] = a[s];
        for(auto i : g[s]) {
                if(i == pr) continue;
                dfs(i ,s);
                if(dp[i] > 0) dp[s] += dp[i];
        }
        ans = max(ans , dp[s]);
}
void dfs2(ll s, ll pr)
{
        dp[s] = a[s];
        for(auto i : g[s]) {
                if(i == pr) continue;
                dfs2(i ,s);
                if(dp[i]>0) dp[s] += dp[i];
        }
        if(dp[s] == ans) {
                dp[s]=0;
                K++;
        }
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n;
        for(ll i=1;i<=n;i++) cin >> a[i];
        for(ll i=1;i<n;i++) {
                ll x, y;
                cin >> x >> y;
                g[x].push_back(y);g[y].push_back(x);
        }
        ans = -1e16;
        dfs(1, -1);
        dfs2(1, -1);
        cout << ans*K << " " << K << endl;
        return 0;
}
