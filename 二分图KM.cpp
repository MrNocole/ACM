//on^3
const int N = 310, T = 101000 , maxn = 1e6+100 , M = 3100;


int n,p[N];
bool vis1[N],vis2[N];
ll ans=0,ex1[N],ex2[N],slack[N],cost[N][N];
bool dfs(int x){
    int i; ll z;
    vis1[x]=1;
    for (i=1;i<=n;i++)
    if (!vis2[i]){
        z=ex1[x]+ex2[i]-cost[x][i];
        if (!z){
            vis2[i]=1;
            if (!p[i]||dfs(p[i])){
                p[i]=x;
                return 1;
            }
        }
        else slack[i]=min(slack[i],z);
    }
    return 0;
}
void km(){
    int i,j; ll x;
    memset(p,0,sizeof(p));
    memset(ex2,0,sizeof(ex2));
    for (i=1;i<=n;i++) ex1[i]=cost[i][1];
    for (i=1;i<=n;i++){
        memset(slack,63,sizeof(slack));
        while (1){
            memset(vis1,0,sizeof(vis1));
            memset(vis2,0,sizeof(vis2));
            if (dfs(i)) break;
            x=INF;
            for (j=1;j<=n;j++)
            if (!vis2[j]) x=min(x,slack[j]);
            for (j=1;j<=n;j++){
                if (vis1[j]) ex1[j]-=x;
                if (vis2[j]) ex2[j]+=x;
                else slack[j]-=x;
            }
        }
    }
    for (i=1;i<=n;i++) ans-=cost[p[i]][i];
}
