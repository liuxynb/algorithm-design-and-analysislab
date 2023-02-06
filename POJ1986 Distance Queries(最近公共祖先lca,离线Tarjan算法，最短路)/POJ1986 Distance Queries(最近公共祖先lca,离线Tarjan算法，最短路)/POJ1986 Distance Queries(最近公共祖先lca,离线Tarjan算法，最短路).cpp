/*2022.11.30*/
#include<stdio.h>
#include<string.h>
typedef long long ll;
const int MAXN = 400001;
int pre[MAXN], head[MAXN], head2[MAXN];
int tot, tot2;
bool vis[MAXN], vis2[MAXN];
int n;
int dis[MAXN], ans[MAXN];
struct Edge
{
    int v, w, next;/*w是权值*/
} edge[MAXN];
struct Query
{
    int v, next, id;
} query[MAXN];
/*加边*/
void add_edge(int u, int v, int w);
void add_query(int u, int v, int id);
/*找爸爸,并查集中的查找函数*/
int find_f(int x);
/*求各个节点在树中的深度。*/
void dfs(int u, int len);
/*f即父亲节点*/
void lca(int u, int f);
int main(void)
{
    int m, q;    
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; i++)
		    pre[i] = i;
		memset(head, -1, sizeof(head));
		memset(head2, -1, sizeof(head2));
		memset(vis, 0, sizeof(vis));
		memset(vis2, 0, sizeof(vis2));
		memset(dis, 0, sizeof(dis));
		tot = tot2 = 0;/*初始化链式前项星*/
        int u, v, w;
        char c[5];
        for (int i = 1; i <= m; i++)
        {           
            scanf("%d%d%d%s", &u, &v, &w, c);
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
        scanf("%d", &q);
        for (int i = 1; i <= q; i++)
        {
            scanf("%d%d", &u, &v);
            add_query(u, v, i);
            add_query(v, u, i);
        }
        dfs(1, 0);lca(1, 1);
        for (int i = 1; i <= q; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}
void add_edge(int u, int v, int w)
{
    edge[tot].v = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}
void add_query(int u, int v, int id)
{
    query[tot2].id = id;
    query[tot2].v = v;
    query[tot2].next = head2[u];
    head2[u] = tot2++;
}
int find_f(int x)
{
    return x == pre[x] ? x : pre[x] = find_f(pre[x]);
}
void dfs(int u, int len)/*求各个节点在树中的深度。*/
{
    vis2[u] = 1;
    dis[u] = len;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v, w = edge[i].w;
        if (!vis2[v])
            dfs(v, len + w);
    }
}
void lca(int u, int f)/*f即父亲节点*/
{
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if (v == f) continue;
        lca(v, u);
        pre[v] = u;
    }
    vis[u] = 1;
    for (int i = head2[u]; ~i; i = query[i].next)
    {
        int v = query[i].v;
        if (vis[v])
        {
            int id = query[i].id;
            ans[id] = dis[u] + dis[v] - 2 * dis[find_f(v)];
        }
    }
}

