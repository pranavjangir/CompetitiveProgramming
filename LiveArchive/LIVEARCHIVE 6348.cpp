/*
        Just a simple line sweep algorithm done on the rectangles
        the trick was that if we dont find a rectangle at position (1) ,
        then this means that our answer is same as some other rectangle that is
        just below our rectangle!
        This is true because of problem constraints which says that --
        NO two rectangles TOUCH or INTERSECT with each other!
*/
#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
typedef pair<ll,ll> pll;
struct event
{
        ll x;
        ll type;
        ll id;
        event() {}
        event(ll xx,ll tt, ll idd) {
                x = xx;
                type = tt;
                id = idd;
        }
        bool operator< (const event &ot) const{
                if(x != ot.x) return x < ot.x;
                return type < ot.type;
        }
};
ll n;
ll X1[100005] , Y1[100005] , X2[100005] , Y2[100005];
vector< event > e;
set< pll > lower;
set< pll > upper;
ll ans[100005];
ll solve(ll yl, ll yr)
{
        if(lower.size() == 0) return -1;
        auto it = lower.lower_bound(make_pair(yl, -1));
        if(it == lower.begin()) return -1;
        it--;
        ll idx = it->second;
        if(Y1[idx] < yl && Y2[idx] > yr) return idx;  // ------- (1)
        if(upper.size() == 0) return -1;
        it = upper.lower_bound(make_pair(yl, -1));
        if(it == upper.begin()) return -1;
        it--;
        return ans[it->second];

}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n;
        for(ll i=0;i<n;i++) {
                cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
                event nw(X1[i] , 0 , i);
                event nw2(X2[i], 1, i);
                e.pb(nw);
                e.pb(nw2);
        }
        sort(e.begin(), e.end());
        for(auto i : e) {

                ll id = i.id;
                if(i.type == 0) {

                        ans[id] = solve(Y1[id], Y2[id]);
                        upper.insert(make_pair(Y2[id], id));
                        lower.insert(make_pair(Y1[id], id));
                }else {
                        upper.erase(make_pair(Y2[id], id));
                        lower.erase(make_pair(Y1[id], id));
                }
        }
        for(ll i=0;i<n;i++) cout << ans[i] << "\n";
        return 0;
}
