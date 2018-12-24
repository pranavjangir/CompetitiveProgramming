#include <bits/stdc++.h>
typedef long long ll;
#define pb push_back
using namespace std;
ll n;
ll a[100005] , b[100005];
ll dp[100005];
const ll inf = 1e9 + 7;
struct Line {
	ll k, b;

	Line() : k(), b() {}
	Line(ll _k, ll _b) : k(_k), b(_b) {}

	ll getVal(ll x) {
		return k * x + b;
	}
};
class Hull
{
public:
        vector< Line > lines;
        vector< ll > its;
        Hull()
        {
                lines.clear();
                its.clear();
        }
        void addLine(Line L)
        {
                while(lines.size() > 0) {

                        if(L.getVal(its.back()) <= lines.back().getVal(its.back())){
                                lines.pop_back();
                                its.pop_back();
                        }else break;
                }
                if(lines.size() == 0) {
                        lines.push_back(L);
                        its.push_back(-inf);
                }else {
                        ll lo = its.back();
                        ll hi = inf;
                        bool ok = false;
                        while(hi > lo) {

                                ll mid = lo + (hi - lo )/2;
                                if(L.getVal(mid) <= lines.back().getVal(mid)) {
                                        hi = mid;
                                        ok = true;
                                }else lo = mid + 1;
                        }
                        if(lo < inf){
                                its.push_back(lo);
                                lines.push_back(L);
                        }

                }
        }

        ll getVal(ll X)
        {
                auto id = (upper_bound(its.begin(), its.end(), X) - its.begin() ) - 1;
                return lines[id].getVal(X);
        }
};
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n;
        for(ll i=1;i<=n;i++) {
                cin >> a[i];
        }
        for(ll i=1;i<=n;i++) {
                cin >> b[i];
        }
        Hull hull;
        dp[1] = 0;
        //hull.addLine(Line(0,0));
        hull.addLine(Line(b[1],0));
        ll ans = 0;
        for(ll i=2;i<=n;i++) {
                ll cost = hull.getVal(a[i]);
                //cout << cost << endl;
                hull.addLine(Line(b[i], cost));
                if(i==n) ans = cost;
        }
        cout << ans << endl;
        return 0;
}
