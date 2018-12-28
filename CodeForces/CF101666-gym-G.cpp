/*
  Main idea --> It's always possible to form a tree, so answer is upper bounded by 'n-1' where n is number of people
                If its possible to break the people into 's' disjoint subsets such that all these 's' subsets have a net balance of zero,
                then our answer is 'n - s'
                so our problem is now to find max 's' such that we can break people into s subsets , disjoint, such that total balance of
                each 's' subsets = 0..
                This can very easily be done using DP with bitmasks!
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,m;
ll tot[1LL << 21];
ll dp[1LL << 21];
int main()
{
        cin >> n >> m;
        for(ll i=1;i<=m;i++) {

                ll u,v,w;
                cin >> u >> v >> w;
                tot[1LL << v] -= w;
                tot[1LL<<u] += w;
        }
        dp[0]=0;
        for(ll i=0;i < (1LL << n); i++) {

                for(ll j=0;j<n;j++) {
                        if(i&(1LL<<j)) {

                                tot[i] = tot[(i^(1LL << j))] + tot[1LL << j];
                                dp[i] = max(dp[i] , dp[(i^(1LL << j))] + (tot[i] == 0));
                        }
                }
        }
        cout << n - dp[(1LL << n) - 1] << "\n";
        return 0;
}
