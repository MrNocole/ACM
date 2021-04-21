
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


//Tarjan 算法
const int max_v = 10000;
vector<int> g[max_v];
//low是表示强联通分量的头
int tot , low[max_v] , time[max_v] , vis[max_v] , v , m;

void add_edge(int f ,int t){
    g[f].push_back(t);
}

void dfs(int idx){
    if (low[idx] == 0) {
        low[idx] = time[idx] = ++tot;
        vis[idx] = 1;
    }
    for (int i : g[idx]){
        if (vis[i]) {
            low[idx] = min(low[idx],time[i]);
        } else {
            dfs(i);
            low[idx] = low[i];
        }
    }
}
void tarjan(){
    for (int i = 1 ; i <= v ; i ++){
        if (!vis[i]) {
            low[i] = time[i] = ++tot;
            vis[i] = 1;
            for (int j : g[i]){
                dfs(j);
            }
        }
    }
}
