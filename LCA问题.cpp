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
