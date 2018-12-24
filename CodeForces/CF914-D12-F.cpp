/*
  Bitset solution: just keep a bitet for each character a to z, where for a character's bitset, 'i' is set if s[i] = 1
                   Now, updates are just O(1)
                   for query, after we take the string, we will initilize our ans bitset with all bits set
                   next , we will take bitwise AND with corresponding character bitsets of our query string, but we do this smartly,
                   We shift the character bitsets according to it;s position in query string.
                   This way an instance of string is recorded as a '1' in ans bitset, where this '1' is at the position where
                   the query string starts in our orignal string..
                   Now we can simply sum amounts of set bits in [l , r-len+1] (( len = query string length ))
                   Total complexity = O(N*(N/64))
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n, q;
string s;
bitset<100101> A[30] , ones, ans;
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> s;
        s = "#" + s;
        n = s.length() - 1;
        cin >> q;
        ones[0]=1;
        for(ll i=1;i<=n;i++) {
                A[s[i]-'a'][i] = 1;
                ones[i]=1;
        }
        ones[n]=0;
        while(q--) {
                ll ty;
                cin >> ty;
                if(ty==1) {
                        ll pos;
                        char x;
                        cin >> pos >> x;
                        ll k = (x - 'a');
                        A[s[pos] - 'a'][pos] = 0;
                        A[k][pos] = 1;
                        s[pos] = x; continue;
                }
                ll l, r; string t;
                cin >> l >> r >> t;
                ll len = t.length(); t = "#" + t;
                if(r-l+1 < len) {
                        cout << "0\n"; continue;
                }
                ans = ones;
                for(ll i=1;i<=len;i++) {
                        ans &= (A[t[i]-'a'] >> i);
                }
                ll ret = 0;
                ans >>= l-1;
                ret  += ans.count();
                ans >>= (r-len+1) - l + 1;
                ret -= ans.count();
                cout << ret << "\n";
        }
        return 0;
}
