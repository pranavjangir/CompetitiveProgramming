#include <bits/stdc++.h>
#define ll int
using namespace std;
typedef pair<ll,ll> pll;
ll n;
ll a[1005][1005];
ll tt[1005][1005];
ll ff[1005][1005];
pll dp1[1005][1005];
pll dp2[1005][1005];
const ll inf = 1e9;
int main()
{
        cin>>n;
        for(ll i=1;i<=n;i++) {
                for(ll j=1;j<=n;j++) {
                        ll x;
                        cin >> x;
                        a[i][j]=x;
                        while(x%2==0) {
                                tt[i][j]++;
                                x /= 2;
                        }
                        while(x%5==0) {
                                ff[i][j]++;
                                x /= 5;
                        }
                        //cout << tt[i][j] << " " << ff[i][j] << endl;
                }
        }
        dp1[n][n] = make_pair(tt[n][n], ff[n][n]);
        dp2[n][n] = dp1[n][n];
        for(ll i=1;i<=n;i++){
                dp1[i][n+1] = make_pair(inf,inf);
                dp2[i][n+1] = make_pair(inf,inf);

                dp1[n+1][i] = make_pair(inf,inf);
                dp2[n+1][i] = make_pair(inf,inf);
        }
        for(ll i=n-1;i>=1;i--) {

                dp1[n][i] = dp1[n][i+1];
                dp1[n][i].first += tt[n][i];
                dp1[n][i].second += ff[n][i];

                dp2[n][i] = dp2[n][i+1];
                dp2[n][i].first += tt[n][i];
                dp2[n][i].second += ff[n][i];

                //cout<<i << "-- " << dp1[n][i].first << " " << dp1[n][i].second << endl;
        }
        for(ll i=n-1;i>=1;i--) {
                for(ll j=n;j>=1;j--) {

                        if(dp1[i+1][j].first < dp1[i][j+1].first) {
                                dp1[i][j] = dp1[i+1][j];
                        }else dp1[i][j] = dp1[i][j+1];

                        dp1[i][j].first += tt[i][j];
                        dp1[i][j].second += ff[i][j];

                        if(dp2[i+1][j].second < dp2[i][j+1].second) {
                                dp2[i][j] = dp2[i+1][j];
                        }else dp2[i][j] = dp2[i][j+1];

                        dp2[i][j].first += tt[i][j];
                        dp2[i][j].second += ff[i][j];
                        //cout<<i << "... " << j << "-- " << dp2[i][j].first << " " << dp2[i][j].second << endl;

                }
        }
        ll ans = inf;
        ans = min(ans, dp1[1][1].first);
        ans = min(ans, dp1[1][1].second);
        ans = min(ans, dp2[1][1].first);
        ans = min(ans, dp2[1][1].second);
        ll X=1;
        ll Y =1;
        cout << ans << endl;
        while(X != n || Y != n) {

                ll h = min(dp1[X][Y].first, dp1[X][Y].second);
                ll g = h;
                g = min(g, min(dp2[X][Y].first, dp2[X][Y].second));
                if(h == g){
                        if(dp1[X+1][Y].first < dp1[X][Y+1].first) {
                                cout << "D";
                                X = X+1; continue;
                        }else {
                                cout << "R";
                                Y = Y+1; continue;
                        }
                }else {
                        if(dp2[X+1][Y].second < dp2[X][Y+1].second) {
                                cout << "D";
                                X = X+1; continue;
                        }else {
                                cout << "R";
                                Y = Y+1; continue;
                        }


                }
        }
        return 0;
}
