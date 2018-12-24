#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n , q;
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> q;
        for(ll i=1;i<=q;i++) {
                ll x;
                cin >> x;
                while(x%2 == 0 && x <= n+n-1) {
                        x += n - (x/2);
                }
                if(x%2 == 0) assert(true == false);
                cout << (x+1)/2 << endl;
        }
        return 0;
}
