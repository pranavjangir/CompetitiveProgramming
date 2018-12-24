#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
typedef pair<ll,ll> pll;
ll n;
vector< ll > g[200005];
ll d[2][200005];
pll dfs(ll s ,ll pr)
{
        ll son = s;
        ll maxm = 0;
        for(auto i : g[s]) {
                if(i == pr) continue;
                pll X = dfs(i, s);
                if(X.second > maxm) {
                        son = X.first;
                        maxm = X.second;
                }
        }
        return make_pair(son, maxm + 1);
}

void bfs(ll s)
{
        for(ll i=0;i<=n;i++) d[0][i] = 1e15;
        d[0][s] = 0;
        queue< ll > q;
        q.push(s);
        while(q.empty() == false) {

                ll u = q.front();
                q.pop();
                for(auto i : g[u]) {
                        if(d[0][i] >= 1e15) {
                                d[0][i] = d[0][u] + 1;
                                q.push(i);
                        }
                }
        }
}
ll par[200005];
bool used[200005];
void bfs2(ll s)
{
        for(ll i=0;i<=n;i++) d[1][i] = 1e15;
        d[1][s] = 0;
        queue< ll > q;
        par[s] = -1;
        q.push(s);
        while(q.empty() == false) {

                ll u = q.front();
                q.pop();
                for(auto i : g[u]) {
                        if(d[1][i] >= 1e15) {
                                d[1][i] = d[1][u] + 1;
                                q.push(i);
                                par[i] = u;
                        }
                }
        }
}
void marks(ll X, ll Y)
{
        if(X == Y){
                used[X] = true; return;
        }
        used[X] = true;
        marks(par[X], Y);
}
class node
{
public:
        ll aa, bb, cc;
        node()
        {
                aa = bb = cc = 0;
        }
        void fills(ll a, ll b ,ll c)
        {
                aa = a;
                bb = b;
                cc = c;
        }
};
void go(ll X, ll Y, ll dd)
{
        if(X == Y) return;
        cout << X << " " << Y << " " << X << "\n";
        go(par[X], Y, dd-1);
}
ll deg[200005];
queue< ll > qq;
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        cin >> n;
        for(ll i=1;i<n;i++) {
                ll a,b;
                cin >> a >> b;
                g[a].pb(b);
                g[b].pb(a);
        }
        ll A = dfs(1, -1).first;
        ll B = dfs(A, -1).first;
        bfs(A);
        bfs2(B);
        marks(A, B); ll ans = 0;
        for(ll i=1;i<=n;i++) {
                deg[i] = g[i].size();
                if(deg[i] == 1 && !used[i]) qq.push(i);
        }
        vector< node > e;
        e.clear();
        while(qq.empty()==false) {

                ll i = qq.front();
                qq.pop();
                if(!used[i]) {
                        if(d[0][i] > d[1][i]) {
                                node nw;
                                nw.fills(i, A, i);
                                e.pb(nw);
                                ans += d[0][i];
                        }else {
                                node nw;
                                nw.fills(i, B, i);
                                e.pb(nw);
                                ans += d[1][i];
                        }
                }
                for(auto j : g[i]) {
                        deg[j]--;
                        if(deg[j] == 1 && !used[j]) qq.push(j);
                }
        }
        ll k = d[0][B];
        ans += (k*(k+1))/2;
        cout << ans << endl;
        for(auto &i : e) cout << i.aa << " " << i.bb << " " << i.cc << "\n";
        go(A, B, k);
        return 0;
}
