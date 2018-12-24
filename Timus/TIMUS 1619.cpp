/*
        This problem is a direct application of Bertrand's ballot theorem, 
        for (k,m), ans is (k-m+1)/(k+1)
        proof : https://en.wikipedia.org/wiki/Bertrand's_ballot_theorem#Variant:_ties_allowed
*/

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
int main()
{
        cout << setprecision(8) << fixed;
        ll t;
        cin >> t;
        while(t--) {
                ll a,b;
                cin >> a >> b;
                if(b > a){
                        cout << "0\n"; continue;
                }else{
                        ld ans = 1.0;
                        if(b == 0 && a == 0) {
                                cout << "1\n"; continue;
                        }
                        if(a == b) {
                                cout << 1.0/(1.0 + 1.0*a) << "\n"; continue;
                        }
                        ans = a-b+1;
                        ans /= (ld)(1.0*a + 1.0);
                        cout << ans << "\n";
                }
        }
        return 0;
}
