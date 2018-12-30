/*
  Just do as they say in problem, ultra easy
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll a,b,c,d;
int main()
{
        cin >> a >> b >> c >> d;
        if(a >= c) {
                cout << a << endl; return 0;
        }
        while(1) {
              a += b;
                if(a >= c) {
                cout << c << endl; return 0;
        }
                c -= d;
                if(a >= c) {
                cout << a << endl; return 0;
        }
        }
        return 0;
}
