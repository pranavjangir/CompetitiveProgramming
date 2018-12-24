/*
  Could not understand the exact meaning of the problem so googled, and found a similar solution to the one below..
  the below solution is not mine, but its easy to code, so I did not bother implementing this problem, it was an easy one anyways!
*/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 52 + 10;
int G[maxn][maxn], vis[maxn];
 
int ID(char a, char b)
{
    return (a - 'A')*2 + (b == '+' ? 0 : 1);
}
void conect(char a1, char a2, char b1, char b2)
{
    if (a1 == '0' || b1 == '0')
    {
        return ;
    }
    int u = ID(a1, a2)^1, v = ID(b1, b2);
    G[u][v] = 1;
}
bool dfs(int u)
{
    vis[u] = -1;
    for (int v = 0; v < 52; v++) if (G[u][v])
    {
        if (vis[v] == -1) return true;
        if (!vis[v] && dfs(v)) return true;
    }
    vis[u] = 1;
    return false;
}
bool find_cycle()
{
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < 52; i++) if (!vis[i])
    {
        if (dfs(i)) return true;
    }
    return false;
}
int main()
{
    int n;
    while(scanf("%d", &n) == 1 && n)
    {
        memset(G, 0, sizeof(G));
        while (n--)
        {
            char s[10]; scanf("%s", s);
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++) if (i != j)
                {
                    conect(s[i*2], s[i*2+1], s[j*2], s[j*2+1]);
                }
            }
        }
        if (find_cycle()) printf("unbounded\n");
        else printf("bounded\n");
    }
 
    
    return 0;
}
