/*
2022.12.19
(约束条件)
s[i]表示前i个小时选的人数，
ans表示选的人数，
r[i]表示第i个小时需要的人数,
h[i]表示第i个小时可以雇佣的人数:

r[i]>=s[i]-s[i-1]>=0
s[i]-s[i-8]>=r[i](i>8)
s[24]-s[0]>=ans
ans+s[i]-s[i+16]>=r[i](i<=8)
*/
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
#define MAXN 30
#define MAXE 1010
int s[MAXN], r[MAXN], h[MAXN];
struct Edge
{
	int v, next, w;
}edge[MAXE<<4];
int head[MAXE], cnt;
int dis[MAXN], visit[MAXN], in[MAXN];
queue<int>q;
//加边
void add_edge(int u, int v, int w)
{
	edge[++cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
int spfa()
{
	while (!q.empty())
		q.pop();//清队
	memset(in, 0, sizeof(in));
	memset(dis, -0x3f, sizeof(dis));
	memset(visit, 0, sizeof(visit));
	dis[0] = 0;
	visit[0] = 1;
	q.push(0);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		visit[u] = 0;
		for (int i = head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			if (dis[v] < dis[u] + edge[i].w)
			{
				dis[v] = dis[u] + edge[i].w;
				if (!visit[v])
				{
					visit[v] = 1;
					q.push(v);
					in[v]++;
					if (in[v] > 24)
						return 0;
				}
			}
		}
	}
	return 1;
}
int f(int ans)
{
	cnt = 0;
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= 24; i++)
	{
		add_edge(i, i - 1, -h[i]);
		add_edge(i - 1, i, 0);
	}
	for (int i = 9; i <= 24; i++)
	{
		add_edge(i - 8, i, r[i]);
	}
	add_edge(0, 24, ans);
	add_edge(24, 0, -ans);
	for (int i = 1; i <= 8; i++)
	{
		add_edge(i + 16, i, r[i] - ans);
	}
	return spfa();
}
int main(void)
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		memset(r, 0, sizeof(r));
		memset(h, 0, sizeof(h));
		for (int i = 1; i <= 24; i++)
			scanf("%d", &r[i]);
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			int m; scanf("%d", &m);
			h[m + 1]++;
		}
		int j;
		for (j = 0; j <= n; j++)
		{
			if (f(j))
				break;
		}
		if (j <= n)
			printf("%d\n", j);
		else
			printf("No Solution\n");
	}
	return 0;
}