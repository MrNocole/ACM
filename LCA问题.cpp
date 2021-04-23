//只求两点LCA方法，复杂度O(n)
const int max_v = 1000;
vector<int> g[max_v];
int parent[max_v] , depth[max_v] , root;
void dfs(int v ,int p , int d){
    parent[v] = p;
    depth[v] = d;
    for (int i = 0 ; i < g[v].size() ; i ++){
        if (g[v][i] != p)dfs(g[v][i],v,d+1);
    }
}
//预处理出parent和depth数组
void init(){
    dfs(root,-1,0);
}
int lca(int u , int v){
    while (depth[u] > depth[v]) u = parent[u];
    while (depth[v] > depth[u]) v = parent[v];
    while (u != v){
        u = parent[u];
        v = parent[v];
    }
    return u;
}

//多次查询LCA算法，预处理复杂度nlogn,每次查询都是logn
const int max_v = 1000 , max_log_v = 100;
vector<int> g[max_v];
int parent[max_log_v][max_v]; // 向上走2^k步所到的节点 (超过根时计-1)
int depth[max_v] , root , V;
void dfs(int v ,int p , int d){
    parent[0][v] = p;
    depth[v] = d;
    for (int i = 0 ; i < g[v].size() ; i ++){
        if (g[v][i] != p)dfs(g[v][i],v,d+1);
    }
}


//预处理出parent和depth数组
//倍增的做法
void init(){
    dfs(root,-1,0);
    for (int k = 0 ; k +1 < max_log_v ; k ++){
        for (int v = 0 ; v < V ; v ++){
            if (parent[k][v] < 0) parent[k+1][v] = -1;
            else parent[k+1][v] = parent[k][parent[k][v]];
        }
    }
}
int lca(int u , int v){
    if (depth[u] > depth[v]) swap(u,v);
    for (int k = 0 ; k < max_log_v ; k ++){
        if ((depth[v]-depth[u])>>k &1){
            v = parent[k][v];
        }
    }
    if (u==v) return u;
    for (int k = max_log_v-1 ; k >= 0 ; k --){
        if (parent[k][u] != parent[k][v]) {
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

//Tarjan离线算法
using namespace std;
const int MAXN = 10005;
vector<int> vec[MAXN];
bool vis[MAXN];
int per[MAXN],head[MAXN],in_num[MAXN];
//in_num统计每个点的入度，为了求根节点，per和并查集中的作用相同，head配合结构体前向星
int cnt,n,m;
 
struct Node
{
    int c,next;
}edge[MAXN];
 
void Init()
{
    cnt = 0;
    memset(in_num,0,sizeof(in_num));
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    for(int i =1;i <= n;i++)
    {
        vec[i].clear();
        per[i] = i;
    }
}
 
void add(int x,int y)
{
    edge[++cnt].next = head[x];
    edge[cnt].c = y;
    head[x] = cnt;
}
 
int Find(int x)
{
    if(per[x] != x)
        per[x] = Find(per[x]);
    return per[x];
}
 
void Union(int x,int y)
{
    x = Find(x);y = Find(y);
    if(x == y)
        return ;
    per[x] = y;
}
 
void Tarjan(int x)
{
    for(int i = head[x];i != -1; i =edge[i].next)
    {
        int v = edge[i].c;
        Tarjan(v);
        Union(v,x);//首先要一直遍历的叶子节点
    }
    vis[x] = 1; // 当这个节点的所有子节点都已经遍历到了，就标记这个节点
    for(int i = 0;i < vec[x].size();i ++)
        if(vis[vec[x][i]])//然后在问题中寻找是否有关于这两个节点都已经标记过的了
            printf("%d 和 %d 的LAC是 %d\n",x,vec[x][i],Find(vec[x][i]));
}
int main()
{
    int x,y;
    scanf("%d%d",&n,&m);
    Init();
    for(int i = 1;i < n;i++)
    {
        scanf("%d%d",&x,&y);
        add(x,y);
        in_num[y] ++;
    }
    for(int i = 0;i < m;i ++)
    {
        scanf("%d%d",&x,&y);
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    int root;
    for(int i = 1;i <= n;i ++)
        if(in_num[i] == 0)
            root = i;
    Tarjan(root);
}
