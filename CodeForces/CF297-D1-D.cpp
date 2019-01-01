#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n, m, k;
ll r[2002][2002];
ll c[2002][2002];
ll nr[2002][2002];
ll nc[2002][2002];
bool swp;
void mirror()
{
        for(ll i=1;i<=m;i++) {

                for(ll j=1;j<=n;j++) {

                        nr[i][j] = c[j][i];
                }
        }
        for(ll i=1;i<m;i++) {

                for(ll j=1;j<=n;j++) {

                        nc[i][j] = r[j][i];
                }
        }
        for(ll i=1;i<=m;i++) {
                for(ll j=1;j<=n;j++) {
                        r[i][j] = nr[i][j];
                }
        }
        for(ll i=1;i<=m;i++) {
                for(ll j=1;j<=n;j++) {
                        c[i][j] = nc[i][j];
                }
        }
        swap(n,m);
        swp=true;
}
ll col[2002][2002];
ll nega=0;
bool check()
{
        ll tt = n*m + n*m - (n+m);
        ll ma = tt/4;
        return (nega <= ma);
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> m >> k;
        for(ll i = 1 ; i < n; i++) {

                string s;
                cin >> s;
                for(ll j=0;j<s.length();j++) {

                        r[i][j+1] = (s[j] == 'E');
                        if(s[j]=='N') nega++;
                }
                cin >> s;
                for(ll j=0;j<s.length();j++) {

                        c[i][j+1] = (s[j] == 'E');
                        if(s[j]=='N') nega++;
                }
        }
        string s;
        cin >> s;
        for(ll j=0;j<s.length();j++) {

                r[n][j+1] = (s[j] == 'E');
                if(s[j] == 'N') nega++;
        }
        if(k==1) {
                if(check()){
                        cout << "YES\n";
                        for(ll i=1;i<=n;i++) {
                                for(ll j=1;j<=m;j++) cout << "1 ";
                                cout << "\n";
                        }
                        return 0;
                }else {
                        cout << "NO\n";
                }
                return 0;
        }
        if(n > m) {

                mirror();
        }
        memset(col,-1,sizeof col);
        col[1][1] = 0;
        for(ll j=2;j<=m;j++) {
                if(r[1][j-1]) col[1][j] = col[1][j-1];
                else col[1][j] = 1 - col[1][j-1];
        }
        for(ll i=2;i<=n;i++) {

                ll mist = 0;
                ll all = m/2;
                col[i][1] = 0;
                for(ll j=2;j<=m;j++) {

                        if(r[i][j-1]) col[i][j] = col[i][j-1];
                        else col[i][j] = 1 - col[i][j-1];
                }
                for(ll j=1;j<=m;j++) {

                        if(c[i-1][j] && (col[i][j] != col[i-1][j])) mist++;
                        if(!c[i-1][j] && (col[i][j] == col[i-1][j])) mist++;
                }
                if(mist > all) {

                        for(ll j=1;j<=m;j++) col[i][j] = 1 - col[i][j];
                }
        }
        cout << "YES\n";
        if(!swp){
        for(ll i=1;i<=n;i++) {
                for(ll j=1;j<=m;j++) {
                        cout << 1 + col[i][j] << " ";
                }
                cout << "\n";
        }
        }else {
                for(ll i=1;i<=m;i++) {
                for(ll j=1;j<=n;j++) {
                        cout << 1 + col[j][i] << " ";
                }
                cout << "\n";
        }

        }
        return 0;
}
