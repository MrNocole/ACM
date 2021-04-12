//to --终点 cap --容量  rev --反向边
struct edge{
    int to , cap , rev;
};
//领接表图
vector<edge> g[max_v];
bool used[max_v];

void add_edge(int from , int to , int cap){
    g[from].push_back((edge){to,cap,(int)g[to].size()});
    g[to].push_back((edge){from,0,(int)g[from].size()-1});
}

int dfs(int v ,int t ,int f){
    if (v==t)return f;
    used[v] = true;
    for (int i = 0 ; i < g[v].size() ; i ++){
        edge &e = g[v][i];
        if (!used[e.to] && e.cap>0){
            int d = dfs(e.to,t,min(f,e.cap));
            if (d > 0){
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow (int s , int t){
    int flow = 0;
    for (;;){
        memset(used,0,sizeof used);
        int f = dfs(s,t,INF);
        if (f==0)return flow;
        flow += f;
    }
}


//Dinic
struct Dinic
{
    struct Edge
    {
        int from, to, cap, flow;
    };
    int s, t; //节点数,边数,源点编号,汇点编号
    vector<Edge> edges; //边表,edges[e]和edges[e^1]互为反向弧
    vector<int> G[M]; //邻接表,G[i][j]表示节点i的第j条边在e中的序号
    bool vis[M]; //bfs用
    int d[M]; //从起点到i的距离
    int cur[M]; //当前弧下标
    void addEdge(int from, int to, int cap)
    {
        edges.push_back({from, to, cap, 0});
        edges.push_back({to, from, 0, 0});
        G[from].push_back(edges.size() - 2);
        G[to].push_back(edges.size() - 1);
    }
    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int id : G[u])
            {
                Edge &e = edges[id];
                if(!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int DFS(int u, int a)
    {
        if(u == t || a == 0) return a;
        int flow = 0, f;
        for(int &i = cur[u]; i < (int)G[u].size(); ++i)
        {
            Edge &e = edges[G[u][i]];
            if(d[u] + 1 == d[e.to] && 
                (f = DFS(e.to, min(a, e.cap - e.flow))) > 0)
            {
                e.flow += f;
                edges[G[u][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }
    int maxflow(int _s, int _t)
    {
        s = _s;
        t = _t;
        int flow = 0;
        while(BFS())
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
}dinic;
