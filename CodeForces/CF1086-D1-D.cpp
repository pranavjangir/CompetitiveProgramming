#include <bits/stdc++.h>
typedef long long ll;
#define pb push_back
using namespace std;
set<ll> s[3];
ll n , q;
string ss;
map<char ,ll> mp;
vector< ll > v[3];
const ll inf = 1e16;
class BIT
{
public:
        vector<ll> tree;
        BIT()
        {
                tree.resize(400005, 0LL);
        }
        void upd(ll x,ll v)
        {
                for(;x<=n;x += (x&(-x))) tree[x] += v;
        }
        ll qry(ll x)
        {
                ll ret =0;
                for(;x>0;x -= (x&(-x))) ret += tree[x];
                return ret;
        }
};
BIT ft[3];
ll getMin(ll id)
{
        if(s[id].empty()) return inf;
        return *s[id].begin();
}
ll getMax(ll id)
{
        if(s[id].empty()) return -inf;
        auto it = s[id].end(); it--;
        return *it;
}
ll getsum(ll id,ll l,ll r)
{
        return (ft[id].qry(r) - ft[id].qry(l-1));
}
bool inRange(ll x)
{
        return (x <= n && x >= 1);
}
ll GET(ll id)
{
        ll cur = v[id][0];
        ll loser = v[id][1];
        ll master = v[id][2];
        ll L = getMin(loser);
        ll R = getMax(loser);
        ll ret = 0;
        if(inRange(L) && inRange(R)) {
                ret += getsum(cur, L, R);
                ll lm = getMin(master);
                ll rm = getMax(master);
                if(!inRange(lm) || !inRange(rm)) return ft[cur].qry(n);
                if(lm > L) {
                        ret += getsum(cur, 1 , L);
                }else {
                        ret += getsum(cur, 1 , lm);
                }
                if(rm < R) {
                        ret += getsum(cur , R , n);
                }else {
                        ret += getsum(cur , rm, n);
                }
                return ret;
        }else {
                if(ft[cur].qry(n) == n) return n;

                return 0;
        }
}
ll prefs[200005];
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> q;
        mp['R'] = 0;
        mp['P'] = 1;
        mp['S'] = 2;
        v[0] = {0,2,1};
        v[1] = {1,0,2};
        v[2] = {2,1,0};
        cin >> ss;
        for(ll i=1;i<=n;i++) {
                ll ka = mp[ss[i-1]];
                prefs[i] = ka;
                ft[ka].upd(i, 1);
                s[ka].insert(i);
        }
        ll ans = 0;
        for(ll i=0;i<3;i++) {
                ll y = GET(i);
                ans += y;
        }
        cout << ans << "\n";
        while(q--) {

                ll pos;
                char x;
                cin >> pos >> x;
                ll ka = mp[x];
                s[prefs[pos]].erase(pos);
                ft[prefs[pos]].upd(pos, -1);
                prefs[pos] = ka;
                s[ka].insert(pos);
                ft[ka].upd(pos, 1);
                ans = 0;
        for(ll i=0;i<3;i++) {
                ll y = GET(i);
                ans += y;
        }
        cout << ans << "\n";
        }
        return 0;
}
