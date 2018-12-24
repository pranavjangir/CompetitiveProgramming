/*
  Editorial solution : https://codeforces.com/blog/entry/44093
*/

#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n,m ,k;
map< ll , vector<ll> > pts;
ll p[1000005];
ll sz[1000005];
ll a[1002][1002];
ll ax, ay;
ll fs(ll x)
{
        return p[x] == x ? x : p[x] = fs(p[x]);
}
void ms(ll x, ll y)
{
        x = fs(x); y = fs(y);
        if(x == y) {
                p[y] = x; return;
        }
        sz[x] += sz[y];
        p[y] = x;
}
ll geti(ll x, ll y)
{
        return (x*m + y);
}
void adds(ll x, ll y)
{
        if(x-1 >= 0) {
                if(a[x-1][y] >= a[x][y]) {
                        ms(geti(x-1,y), geti(x,y));
                }
        }

        if(y-1 >= 0) {
                if(a[x][y-1] >= a[x][y]) {
                        ms(geti(x,y-1), geti(x,y));
                }
        }

        if(x+1 < n) {
                if(a[x+1][y] >= a[x][y]) {
                        ms(geti(x+1,y), geti(x,y));
                }
        }

        if(y+1 < m) {
                if(a[x][y + 1] >= a[x][y]) {
                        ms(geti(x,y + 1), geti(x,y));
                }
        }
}
void go()
{
        auto it = pts.end();
        while(it != pts.begin()) {
                it--;
                //if(it == pts.begin()) break;
                ll nums = it->first;
                //cout << nums << endl;
                ll RE = 1e14;
                if(k%nums == 0) RE = k/nums;
                vector< ll > pos = it->second;
                for(auto j : pos) {
                        ll X = j/m;
                        ll Y = j%m;
                        adds(X, Y);
                        //cout << X << " --- " << Y << endl;
                        //cout << sz[fs(j)] << endl << endl;
                        if(sz[fs(j)] >= RE) {
                                ax = X;
                                ay = Y;
                                return;
                        }
                }
        }
                /*ll nums = it->first;
                ll RE = 1e14;
                if(k%nums == 0) RE = k/nums;
                vector< ll > pos = it->second;
                for(auto j : pos) {
                        ll X = j/n;
                        ll Y = j%m;
                        adds(X, Y);
                        if(sz[fs(j)] >= RE) {
                                ax = X;
                                ay = Y;
                                return;
                        }
                }*/

        cout << "NO\n"; exit(0);
}
bool vis[1002][1002];
ll tod;
ll dx[] = {-1, 1, 0, 0};
ll dy[] = {0 ,0 , 1 , -1};
void dfs(ll s, ll t)
{
        if(tod <= 0) return;
        if(a[s][t] < a[ax][ay]) return;
        if(s < 0 || s >= n || t < 0 || t >= m) return;
        if(vis[s][t]) return;
        vis[s][t] = true;
        tod--;
        for(ll i=0;i<4;i++) {
                ll xx = s + dx[i];
                ll yy = t + dy[i];
                dfs(xx, yy);
        }

}
void doit()
{
        tod = k/(a[ax][ay]);
        dfs(ax, ay);
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> m >> k;
        for(ll i=0;i<=n*m;i++) {
                p[i]=i;
                sz[i]=1;
        }
        for(ll i=0;i<n;i++) {
                for(ll j=0;j<m;j++) {
                        cin >> a[i][j];
                        pts[ a[i][j] ].pb(i*m + j);
                }
        }
        go();
        cout << "YES\n";
        doit();
        for(ll i=0;i<n;i++) {
                for(ll j=0;j<m;j++) {
                        if(vis[i][j]) cout << a[ax][ay] << " ";
                        else cout << "0 ";
                }
                cout << "\n";
        }
        cout << "\n";
        return 0;
}
