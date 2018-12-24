#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
vector< ll > v;
ll n;
ll a[100005];
ll k[100005];
ll xx[2000006];
int main()
{
        for(ll i=1;i<=1000;i++) {
                v.pb(i*i);
                xx[i*i] = i;
        }
        cin >> n;
        for(ll i=2; i<=n;i += 2) {
                cin >> a[i];
        }
        if(a[2]%2 == 1) {
                k[1] = (a[2] - 1)/2;
                k[2] = (a[2] + 1)/2;
                a[1] = (k[1])*k[1];
        }else if(a[2]%4 != 0) {cout << "No\n"; return 0;}
        else {
                k[1] = (a[2]/4)-1;
                k[2] = (a[2]/4)+1;
                a[1] = k[1]*k[1];
        }
        for(ll i=3;i<=n;i+=2){
                if(a[i+1]%2 == 1) {
                        k[i] = (a[i+1] - 1)/2;
                        k[i+1] = (a[i+1] + 1)/2;
                        a[i] = (k[i] - k[i-1])*(k[i] + k[i-1]);
                }else {
                        if(a[i+1]%4 != 0) {
                                cout << "No\n"; return 0;
                        }else {
                                k[i] = (a[i+1]/4) - 1;
                                k[i+1] = (a[i+1]/4) + 1;
                                a[i] = (k[i] - k[i-1])*(k[i] + k[i-1]);
                        }
                }
        }
        cout << "Yes\n";
        for(ll i=1;i<=n;i++) cout <<a[i]<<" ";
        return 0;
}
