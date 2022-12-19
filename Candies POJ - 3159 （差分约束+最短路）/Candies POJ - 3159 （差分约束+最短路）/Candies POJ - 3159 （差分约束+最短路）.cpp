//2022.12.18
#include<stdio.h>
#include<string.h>

#define MAXN 30010
#define MAXE 150010
const int INF = 0x3f3f3f3f;
int first[MAXN];
int visit[MAXN];
int stack[MAXN];//栈
int dis[MAXN];
struct Edge
{
	int to, w, next;
}edge[MAXE];
int cnt;
//加边
void add_edge(int a, int b, int v)
{
	edge[cnt].to = b;
	edge[cnt].w = v;
	edge[cnt].next = first[a];
	first[a] = cnt++;
}
//差分约束
void spfa(int st, int n)
{
	int top = -1;
	memset(dis, INF, sizeof(dis));
	memset(visit, 0, sizeof(visit));
	dis[st] = 0;
	visit[st] = 1;
	stack[++top] = st;
	while (top > -1)
	{
		int u = stack[top--];
		visit[u] = 0;
		int i;
		for (i = first[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].to;
			if (dis[v] > dis[u] + edge[i].w)
			{
				dis[v] = dis[u] + edge[i].w;
				if (!visit[v])
				{
					visit[v] = 1;
					stack[++top] = v;
				}
			}
		}
	}
}
int main(void)
{
	int n, m;
	int a, b, v;
	while (~scanf("%d%d", &n, &m))
	{
		cnt = 0;
		memset(first, -1, sizeof(first));
		while (m--)
		{
			scanf("%d%d%d", &a, &b, &v);
			add_edge(a, b, v);
		}
		spfa(1, n);
		printf("%d", dis[n]);
	}
	return 0;
}

