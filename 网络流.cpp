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
const ll INF = 1e9+7;
const int N = 11000 , E = 210000;
int n , m , s , t;
ll cnt = 1 , first[N] , nxt[E] , to[E] , val[E];

inline void addEdge(int u , int v , ll w){
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = first[u];
    first[u] = cnt;
}
int dep[N] , q[N] , l ,r;
bool bfs(){
    memset(dep,0,sizeof dep);
    q[l=r=1] = s;
    dep[s] = 1;
    while (l <= r){
        int u = q[l++];
        for (int p = first[u] ; p ; p = nxt[p]){
            int v = to[p];
            if (val[p] and !dep[v]){
                dep[v] = dep[u] + 1;
                q[++r] = v;
            }
        }
    }
    return dep[t];
}
ll dfs(int u , ll in){
    if (u==t)return in;
    ll out = 0;
    for (int p = first[u]  ; p and in ; p = nxt[p]) {
        int v = to[p];
        if (val[p] and dep[v] == dep[u] + 1){
            ll res = dfs(v,min(val[p],in));
            val[p] -= res;
            val[p^1] += res;
            in -= res;
            out += res;
        }
    }
    if (out == 0){
        dep[u] = 0;
    }
    return out;
}

ll max_flow(){
    ll ret = 0;
    while (bfs())ret+=dfs(s,std::numeric_limits<ll>::max());
    return ret;
}
//建边 要建双向边
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i = 1 ; i <= m ; i ++){
        int u , v;
        ll w;
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,0);
    }
    printf("%lld\n",max_flow());
}
