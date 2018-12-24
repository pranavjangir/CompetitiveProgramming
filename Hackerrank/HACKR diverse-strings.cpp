/*
  Editorial solution:
  first observation : the count of 'a' will be the largest!
  second observation : for every 'k' there exists a nk, 'nk' is the smallest diverse seq with k distinct letters.
  third observation : for n > nk, we can append n-nk 'a' at the start to get desired string! for n < nk, return "NONE"
  
  for any k,if we delete occurence of 'a' from the string then we get string for k-1, hence
  nk = f(k) + nk-1
  f(k) by induction is 3*k-2
  we get nk = k*(3*k-2)/2
  Now we can construct easily! see examples of construction from this editorial!
  editorial : https://www.hackerrank.com/contests/hourrank-30/challenges/diverse-strings/editorial
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n, k;
string forms(ll kk)
{
        char nw = (char)('a' + (k-kk));
        if(kk == 1) {

                string ret = "";
                ret = ret + nw;
                return ret;
        }
        ll occ = 3*kk - 2;
        string ret = forms(kk-1);
        char prv = (char)('a' + (k-kk + 1));
        ret = nw + ret;
        ret = nw + ret;
        ret = ret + nw;
        string ans = "";
        for(ll i=0;i<ret.length();i++) {
                if(ret[i] == prv) {
                        ans = ans + ret[i];
                        ans = ans + nw;
                }else ans = ans + ret[i];
        }
        return ans;
}
string solve(ll N, ll K)
{
        ll mins = (k*(3*k - 1))/2;
        if(n < mins) {
                return "NONE";
        }
        string ret = forms(k);
        //cout << ret << endl;
        for(ll i=0;i<n-mins;i++) {
                ret = "a" + ret;
        }
        return ret;
}
int main()
{
        ll q;
        cin >> q;
        while(q--){
        cin >> n >> k;
        string ans = solve(n,k);
        cout << ans << endl;
        }
        return 0;
}
