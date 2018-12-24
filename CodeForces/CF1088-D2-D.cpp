#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
bool swp;
ll a,b;
ll A,B;
ll asks(ll x, ll y)
{
        cout << "? " << x << " " << y << endl;
        ll an;
        cin >> an;
        return an;
}

int main()
{
        A = 0;
        B = 0;
        ll g;
        ll dd = asks(0,0);
        if(dd >= 0) g = 1;
        else g = 0;
        for(ll i=29;i>=0;i--) {
                ll h = 1LL << i;
                ll x = asks(A^h, B);
                ll y = asks(A, B^h);
                if(x == y) {
                        if(g){
                                A += h;
                        }else B += h;

                        if(y == -1) g = 0;
                        else g = 1;
                }else {
                        if(y == 1) {
                                A += h;
                                B += h;
                        }
                }
        }
        cout << "! " << A << " " << B << endl;
        return 0;
}
