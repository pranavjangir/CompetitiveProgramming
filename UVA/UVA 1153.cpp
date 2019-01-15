/*
  Idea: DP idea doesn't work, so we try greedy,
        Take every job if you can , and put the value of 'q' of this job in priority queue (PQ), increase answer
        Now if comes a job you can't accept, we can do 2 things
          1) look at the maximum element in PQ , let it be X, 
              if X > current 'q' and if releasing that 'X' makes it possible to accept this job,
              then clearly its optimal to excahnge X with current 'q' .. this doest increase our answer
              
          2) if 1) fails , then we cant accept this job no matter what, so we ignore this one!
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pb push_back
typedef pair<ll,ll> pll;
ll T;
ll n;
vector< pll > v;
ll p[800005];
void solve()
{
        cin >> n;v.clear();
        for(ll i=1;i<=n;i++) {
                ll q , d;
                cin >> q >> d;
                v.pb(make_pair(d, q));

        }
        sort(v.begin(), v.end());
        priority_queue<ll> pq;
        p[0] = v[0].second;
        for(ll i=1;i<v.size();i++) {
                p[i] = p[i-1] + v[i].second;
        }
        for(ll i=0;i<v.size();i++) {
                v[i].first -= p[i];
        }
        ll toadd=0;
        ll ans=0;
        ll cur=0;
        if(v[0].first >= 0) {
                cur=1;
                pq.push(v[0].second);
        }else {
                cur=0;
                toadd = v[0].second;
        }
        for(ll i=1;i<v.size();i++) {

                ll D = v[i].first;
                ll Q = v[i].second;
                if(D + toadd >= 0) {
                        cur++;
                        pq.push(Q);
                        continue;
                }else {
                        if(pq.empty()) {
                                toadd += Q;
                                continue;
                        }
                        ll X = pq.top();
                        if(X + D + toadd >= 0 && (X > Q)) {

                                pq.pop();
                                pq.push(Q);
                                toadd += X;
                        }else {

                                toadd += Q;
                        }

                }
        }
        cout << cur << "\n";
        if(T != 0) cout << "\n";
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> T;
        while(T--) {

                solve();
        }
        return 0;
}
