/*
  This is the editorial solution
  fist note k <= 10..
  we need some transformation, if bulb[i] and bul[i + 1] are not same, then make b[i] = 1..
  this way we have a new array with at most 20 '1' entries..
  Now we can look at this problem via tree analogy, consider we have n+1 vertices representing 0..n, one for each bulb
  and we have at most 20 tokens on some of these vertices, we need to move tokens so that they meet and disappear, 
  
  for this we can first find all the distances b/w all the tokens with bfs
  
  and then after that do a DP with bitmask! see the code
  
  Editorial : https://codeforces.com/blog/entry/1839
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n , k, l;
ll a[2002];
ll L[2002];
ll ons[10005];
ll m;
vector< ll > b;
ll d[50][50];
const ll inf = 1e16;
void bfs(ll id)
{
        for(ll i=0;i<m;i++) d[id][i] = inf;
        queue< ll > q;
        q.push(b[id]);
        vector< ll > dist(n+5, inf);
        dist[b[id] ] = 0;
        d[id][id] = 0;
        while(q.empty() == false) {

                ll u = q.front();
                q.pop();
                for(ll i=1;i<=l;i++) {

                        ll fr = u + L[i];
                        ll bk = u - L[i];
                        if(fr <= n) {
                                if(dist[fr] == inf) {
                                        dist[fr] = dist[u] + 1;
                                        q.push(fr);
                                }
                        }
                        if(bk >= 0) {
                                if(dist[bk] == inf) {
                                        dist[bk] = dist[u] + 1;
                                        q.push(bk);
                                }
                        }
                }
        }
        for(ll i=0;i<m;i++) {
                d[id][i] = dist[ b[i] ];
                //cout << d[id][i] << " ";
        }
        //cout << endl;
}
ll dp[1LL << 21];
int main()
{
        cin >> n >> k >> l;
        for(ll i=1;i<=k;i++) {
                cin >> a[i];
                ons[ a[i] ] = 1;
        }
        for(ll i=1;i<=l;i++) cin >> L[i];
        for(ll i=0;i <= n;i++) {
                if(ons[i] != ons[i + 1]) {
                        b.push_back(i);
                        //cout << "****" << i << endl;
                }
        }
        m = b.size();
        for(ll i=0;i<m;i++) {
                bfs(i);
        }
        dp[0] = 0;
        ll lim = (1LL << m) - 1;
        for(ll i=1;i<=lim;i++) {
                ll cnt = __builtin_popcountll(i);
                if(cnt%2 == 1) {
                        dp[i]=inf;
                        continue;
                }
                dp[i] = inf;
                ll j = 0;
                while(((i >> j)&1) == 0) j++;
                ll hh = j;
                j++;
                for(;j<m;j++){
                        if((i >> j)&1){
                        ll nw = i^(1LL << hh);
                        nw = nw ^ (1LL << j);
                        dp[i] = min(dp[i], dp[nw] + min(d[hh][j], d[j][hh]));
                        }
                }
        }
        if(dp[lim] >= inf) dp[lim] = -1;
        cout << dp[lim] << "\n";
        return 0;
}
