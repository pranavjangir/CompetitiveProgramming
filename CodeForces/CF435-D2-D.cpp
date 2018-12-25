// Editorial solution, easy DP problem, not even DP just prefix sums!

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define fi first
#define se second
#define pb push_back

const int N = 405;
char s[N][N],temp[N][N];
int pre[N][N],pre1[N][N],n,m,ans;
bool check(int i,int j)
{
    return i>=1 && i<=n && j>=1 && j<=m;
}
void rotate()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            temp[j][n-i+1] = s[i][j];
        }
    swap(n,m);
    for(int i=1;i<=n;i++)
    {
    for(int j=1;j<=m;j++)
    {
        s[i][j]=temp[i][j];
        pre[i][j]=(s[i][j]-'0')+pre[i-1][j];
    }
    }
    for(int i=1;i<=n;i++)
        pre1[i][m+1] = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            pre1[i][j]=(s[i][j]-'0')+pre1[i-1][j+1];
        }
}
void solve()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(s[i][j]=='0')
            for(int r=1;;r++)
            {
                if(!check(i-r,j+r) || !check(i+r,j+r))
                    break;
                if(s[i-r][j+r]=='1' || s[i+r][j+r]=='1')
                    break;
                if(pre[i+r][j+r]-pre[i-r][j+r]==0)
                {
                ans++;
                }
            }
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(s[i][j]=='0')
            {
                for(int r=1;;r++)
                {
                    if(!check(i,j+r) || !check(i+r,j))
                        break;
                    if(s[i][j+r]=='1' || s[i+r][j]=='1')
                        break;
                    if(pre1[i+r][j]-pre1[i][j+r]==0)
                       ans++;
                }
            }
        }
}
main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    rotate();
    solve();
    rotate();
    solve();
    rotate();
    solve();
    rotate();
    solve();
    printf("%d",ans);
    return 0;
}
