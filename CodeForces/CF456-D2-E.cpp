/*
  Editorial solution: https://codeforces.com/blog/entry/13336
*/
#include<bits/stdc++.h>
#define pii pair<int,int>
#define F first
#define S second
#define rep(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int nextInt() {
    int x = 0, p = 1;
    char c;
    do {
        c = getchar();
    } while (c <= 32);
    if (c == '-') {
        p = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * p;
}
int n,m,q,par[300005],dis[300005],sz[300005],maxi,maxiV;
vector<int> v[300005];
bool mark[300005];
/*void dfs(int st){
    mark[st]=1;
    sz[par[st]]++;
    rep(j,0,v[st].size()){
        if(mark[v[st][j]]) continue;
        par[v[st][j]]=par[st];
        dfs(v[st][j]);
    }
}*/
/*pii dfs1(int st,int prst){
    int val=0,val1=st;
    rep(j,0,v[st].size()){
        if(v[st][j]==prst) continue;
        if(dfs1(v[st][j],st).F+1>val){
            val=dfs1(v[st][j],st).F+1;
            val1=dfs1(v[st][j],st).S;
        }
    }
    return make_pair(val,val1);
}*/
void dfs(int st, int depth, int p) {
    if (depth > maxi) {
        maxi = depth;
        maxiV = st;
    }
    for (int i = 0; i < v[st].size(); i++) {
        int to = v[st][i];
        if (to != p) dfs(to, depth + 1, st);
    }
}

int findLongestWay(int v) {
    maxi = -1;
    dfs(v, 0, -1);
    maxi = -1;
    dfs(maxiV, 0, -1);
    return maxi;
}

int par_find(int vert){
    if(par[vert]==vert) return vert;
    par[vert]=par_find(par[vert]);
    return par[vert];
}
int main()
{
    n = nextInt();
    m = nextInt();
    q = nextInt();
    rep(i,1,n+1) par[i]=i;
    rep(i,0,m){
        int v1,v2;
        v1 = nextInt();
        v2 = nextInt();
        v[v1].push_back(v2);
        v[v2].push_back(v1);
        if(!mark[v1]&&!mark[v2]){
            par[v1]=v1;
            par[v2]=v1;
            sz[v1]=2;
        }
        else if(mark[v1]&&!mark[v2]){
            v1=par_find(v1);
            par[v2]=v1;
            sz[v1]++;
        }
        else if(mark[v2]&&!mark[v1]){
            v2=par_find(v2);
            par[v1]=v2;
            sz[v2]++;
        }
        else{
            v1=par_find(v1);
            v2=par_find(v2);
            if(v1==v2) continue;
            if(sz[v1]>sz[v2]){
                par[v2]=v1;
                sz[v1]+=(sz[v2]);
            }
            else{
                par[v1]=v2;
                sz[v2]+=(sz[v1]);
            }
        }
        mark[v1]=1;mark[v2]=1;
    }
    /*rep(i,1,n+1){
        if(mark[i]) continue;
        par[i]=i;
        sz[i]=0;
        dfs(i);
    }*/
    rep(i,1,n+1){
        if(par[i]!=i) continue;
        /*pii mn=dfs1(i,i);
        if(mn.S==i) dis[i]=0;
        else dis[i]=dfs1(mn.S,mn.S).F;*/
        dis[i] = findLongestWay(i);
    }
    rep(i,0,q){
        int ty;
        ty = nextInt();
        if(ty==1){
            int x;
            x = nextInt();
            x=par_find(x);
            printf("%d\n",dis[x]);
            continue;
        }
        int x,y;
        x = nextInt();
        y = nextInt();
        x=par_find(x);y=par_find(y);
        if(x==y) continue;
        if(sz[x]>sz[y]){
            par[y]=x;
            dis[x]=max(dis[x],max(dis[y],(dis[x]%2==1?(dis[x]/2)+1:(dis[x]/2))+(dis[y]%2==1?(dis[y]/2)+1:(dis[y]/2))+1));
            sz[x]+=sz[y];
        }
        else{
            par[x]=y;
            dis[y]=max(dis[x],max(dis[y],(dis[x]%2==1?(dis[x]/2)+1:(dis[x]/2))+(dis[y]%2==1?(dis[y]/2)+1:(dis[y]/2))+1));
            sz[y]+=sz[x];
        }
    }
    return 0;
}
