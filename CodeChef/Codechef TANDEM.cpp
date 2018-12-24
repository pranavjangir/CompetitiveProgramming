/*
        Editorial : https://discuss.codechef.com/questions/81590/tandem-editorial
*/
#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
ll n;
string s;
string sr;
vector< vector<ll> > suf;
vector< vector<ll> > rsuf;
class node
{
public:
        ll id, f , se;
        node(){}
        bool operator< (const node &ot)
        {
                if(f < ot.f) return true;
                else if(f > ot.f) return false;

                return (se < ot.se);
        }
};
node tmp[200005];
bool sames(node &A, node &B)
{
        bool ret = (A.f == B.f);
        bool r = (A.se == B.se);
        return (ret && r);
}
vector< vector<ll> > getSuffix(string &t)
{
        vector< vector<ll> > P;
        P.resize(19);
        for(ll i=0;i<19;i++) P[i].resize(n+2, 0LL);
        for(ll i=0;i<n;i++) {
                P[0][i] = t[i] - 'a';
        }
        ll cnt = 1LL;
        for(ll i=1;i<=18;i++) {
                for(ll j=0;j<n;j++) {
                        tmp[j].f = P[i-1][j];
                        tmp[j].se = -1;
                        if(j+cnt < n) tmp[j].se = P[i-1][j+cnt];
                        tmp[j].id = j;
                }
                sort(tmp, tmp+n);
                for(ll j=0;j<n;j++) {
                        if(j && sames(tmp[j], tmp[j-1])) P[i][tmp[j].id] = P[i][tmp[j-1].id];
                        else P[i][tmp[j].id] = j;
                }
                cnt = cnt * 2LL;
        }
        return P;
}
ll LCP(vector<vector<ll> > &A, ll x, ll y)
{
        ll ret = 0;
        if(x == y) return n-x;
        for(ll k = 18; k >= 0 && (x < n) && (y < n); k--) {
                if(A[k][x] == A[k][y]) {
                        x += (1LL << k);
                        y += (1LL << k);
                        ret += (1LL << k);
                }
        }
        return ret;
}
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> sr;
        n = sr.length();
        s = sr;
        reverse(sr.begin(), sr.end());
        suf = getSuffix(s);
        rsuf = getSuffix(sr);
        ll tots = 0;
        ll boring = 0;
        s = s + "$";
        for(ll L=1;L <= (n/3); L++) {

                for(ll i=0;i + L + L < n; i += L) {
                        ll j = i + L;
                        ll k = i + L + L;
                        ll aa = LCP(suf, i,j);
                        aa = min(aa, LCP(suf,j,k));
                        aa = min(aa, LCP(suf, i,k));
                        ll bb = LCP(rsuf , n-1-i, n-1-j);
                        bb = min(bb , LCP(rsuf , n-1-i, n-1-k));
                        bb = min(bb , LCP(rsuf , n-1-j, n-1-k));
                        ll yo = min(aa, L) + min(bb,L) - 1;
                        if(yo >= L) {
                                if(aa > L) {
                                        boring += yo - L + 1;
                                }else {
                                        boring += yo - L;
                                        tots += 1;
                                }
                        }
                }
        }
        cout << tots  << " " << boring << endl;
        return 0;
}
