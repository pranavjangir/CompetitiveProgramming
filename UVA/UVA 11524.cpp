#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef long double ld;
ll T;
ld r , m1, m2, n1, n2, m3, n3;
void solve()
{
        cin >> r >> m1 >> n1 >> m2 >> n2 >> m3 >> n3;
        ld s = (n1 + m1 + (n1*n2 / m2));
        ld k = r*s / (sqrt(s*n2*n1*m1*n1/m2));
        ld ret = k*k*sqrt(s*n2*n1*m1*n1/m2);
        cout << ret << endl;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cout << setprecision(8) << fixed;
        cin >> T;
        while(T--){
                solve();
        }
        return 0;
}
