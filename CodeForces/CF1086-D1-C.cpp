/*
  Trick used here --> https://codeforces.com/blog/entry/64006?#comment-478340
*/
#include <bits/stdc++.h>
typedef long long ll;
#define pb push_back
using namespace std;
string s ,a,b;
ll T , n , k, S[1000005] , A[1000005] , B[1000005];
bool used[30];
ll p[30];
ll tmp[1000005];
ll pp[30];
bool uu[30];
ll cmp(ll x[] , ll y[])
{
        for(ll i=1;i<=n;i++) {
                if(x[i] == y[i]) continue;
                if(x[i] < y[i]) return -1;
                return 1;
        }
        return 0;
}
bool Extend()
{
        ll pos = 1;
        for(ll i=1;i<=k;i++) pp[i] = p[i];
        for(ll i=1;i<=k;i++) uu[i] = used[i];
        while(true) {
                while(pos <= n && pp[S[pos]] > 0) pos++;
                if(pos > n) break;
                for(ll i=k;i>0;i--) {
                        if(!uu[i]) {

                                pp[S[pos]] = i;
                                uu[i] = true;
                                break;
                        }
                }
        }
        for(ll i=1;i<=n;i++) tmp[i] = pp[S[i]];
        return (cmp(tmp, A) >= 0);
}
void solve()
{
        cin >> k >> s >> a >> b;
        n = s.length();
        for(ll i=1;i<=n;i++) {
                S[i] = (s[i - 1] - 'a') + 1;
                A[i] = (a[i - 1] - 'a') + 1;
                B[i] = (b[i - 1] - 'a') + 1;
        }
        ll pos = 1;
        memset(used, false, sizeof used);
        memset(p, 0, sizeof p);
        if(!Extend()) {
                cout << "NO\n"; return;
        }
        while(true) {
                //ll pos = 0;
                while(pos <= n && p[S[pos]] > 0) pos++;
                if(pos > n) break;
                ll col = -1;
                for(ll i=1;i<=k;i++) {
                        if(used[i]==false) {
                                col = i;
                                assert(col > 0);
                                used[col]=true;
                                p[S[pos]] = col;
                                if(Extend()) {
                                        break;
                                }
                                used[col]=false;
                                p[S[pos]] = 0;
                        }
                }
        }
        for(ll i=1;i<=k;i++) {
                if(p[i] == 0) {
                        for(ll j=1;j<=k;j++) {
                                if(used[j]==false) {
                                        p[i] = j;
                                        used[j]=true;
                                        break;
                                }
                        }
                }
        }
        for(ll i=1;i<=k;i++) assert(p[i]>0);
        for(ll i=1;i<=n;i++) tmp[i] = p[S[i]];
        if(cmp(tmp, B) > 0) {
                cout <<"NO\n"; return;
        }else if(cmp(tmp, A) < 0) {
                cout << "NO\n"; return;
        }
        cout << "YES\n";
        for(ll i=1;i<=k;i++) cout << (char)(p[i] - 1 + 'a'); cout << "\n";
}
int main()
{
        ios_base::sync_with_stdio(false); cin.tie(NULL);
        cout.tie(NULL);
        cin >> T;
        while(T--) {
                solve();
        }
}
