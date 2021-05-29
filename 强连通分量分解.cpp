
//Korasaju算法
const int MAX_V = 1000;
int V; //顶点数
vector<int> G[MAX_V]; //图的邻接图
vector<int> rG[MAX_V]; //把边反向后的图
vector<int> vs; //后序遍历顺序的顶点列表
bool used[MAX_V]; // 访问标记
int cmp[MAX_V]; //所属联通分量的拓扑序
void add_edge(int from ,int to){
    G[from].push_back(to);
    rG[to].push_back(from);
}
void dfs(int v){
    used[v] = true;
    for (int i = 0 ; i < G[v].size() ; i ++){
        if (!used[G[v][i]]) dfs(G[v][i]);
    }
    vs.push_back(v);
}
void rdfs(int v , int k){
    used[v] = true;
    cmp[v] = k;
    for (int i = 0 ; i < rG[v].size() ; i ++){
        if (!used[rG[v][i]]) rdfs(rG[v][i],k);
    }
}
int scc(){
    memset(used,0,sizeof used);
    vs.clear();
    for (int v = 0 ; v < V ; v ++){
        if (!used[v])dfs(v);
    }
    memset(used,0,sizeof used);
    int k = 0;
    for (int i = vs.size()-1 ; i >= 0 ; i --){
        if (!used[vs[i]]) rdfs(vs[i],k++);
    }
    return k;
}



//tarjan
void dfs(int u){
    stack[top++] = u;
    low[u] = num[u] = ++cnt;
    for (int i = 0 ; i < g[u].size() ; i ++){
        int v = g[u][i];
        if (!num[v]) {
            dfs(v);
            low[u] = min(low[v],low[u]);
        } else if (!sccno[v]) {
            low[u] = min(low[v],low[u]);
        }
    }
    if (low[u]==num[u]) {
        cnt ++;
        while (1) {
            int v = stack[--top];
            sccno[v] = cnt;
            if (u==v)break;
        }
    }
}

void tarjan(int n){
    cnt = top = dfn = 0;
    memset(sccno,0,sizeof sccno);
    memset(num,1,sizeof num);
    memset(low,0,sizeof low);
    for (int i = 1 ; i <= n ; i ++){
        if (num[i]) dfs(i);
    }
}
