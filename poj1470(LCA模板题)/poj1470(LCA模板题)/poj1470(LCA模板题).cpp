//2022.11.30
#include<stdio.h>
#include<cmath>
#define MAXN 901
int first[MAXN<<1], node[MAXN<<1], depth[MAXN<<1], dp[MAXN << 1][25];
int ans[MAXN], vis[MAXN];
struct EDGE
{
	int v;
	int next;
}edge[MAXN];
int head[MAXN], cnt, tot, in[MAXN];
//建树
void add_vec(int u, int v);
//利用dfs构造欧拉序列
void dfs(int u, int d);
//预处理st表
void rmq_init(int n);
//利用rmq算法
int rmq(int x, int y);
//找最近公共祖先
int lca(int a, int b);
//主函数
int main(void)
{
	int n, q;
	while (scanf("%d",&n)!=EOF)
	{
		for (int i = 0; i < MAXN; i++)
		{
			ans[i] = vis[i] = in[i] = 0;
			head[i] = -1;
		}
		tot = cnt = 0;
		int u, v, m;
		for (int i = 0; i < n; i++) //输入
		{
			scanf("%d:(%d)", &u, &m);
			for (int j = 0; j < m; j++)
			{
				scanf("%d", &v);
				in[v]++;
				add_vec(u, v);
			}
		}
		for (int i = 1; i <= n; i++)
			if (!in[i])//从根开始
				dfs(i, 1);//从深度为1开始
		rmq_init(tot);//tot即欧拉序列长度
		scanf("%d", &q);
		while (q--)
		{
			while (getchar() != '(');
            scanf("%d%d", &u, &v);
            int h = lca(u, v);
            ans[h] += 1;
            while (getchar() != ')');
		}
		for (int i = 1; i <= n; i++)
			if (ans[i]) printf("%d:%d\n", i, ans[i]);
	}
}

void add_vec(int u, int v)
{
	edge[cnt].v = v;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}
void dfs(int u, int d)
{
	node[++tot] = u;//将u加入欧拉序中
	depth[tot] = d;
	vis[u] = 1;
	first[u] = tot;//记录u第一次出现的位置
	for (int i = head[u]; i != -1; i = edge[i].next)
	{
		if (vis[edge[i].v] == 0)
		{
			dfs(edge[i].v, d + 1); //继续dfs，深度加1
			node[++tot] = u;//回溯时也需要加入欧拉序中
			depth[tot] = d;
		}
	}
}
void rmq_init(int n)//预处理st表
{
	int k = log2(n);
	for (int i = 1; i <= n; i++)
		dp[i][0] = i;
	for (int j = 1; j <= k; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			int a = dp[i][j - 1];
			int b = dp[i + (1 << j - 1)][j - 1];//dp[i][j]即长度为2^(j-1)，起始位置为为i的段的最小深度对应的下标。
			if (depth[a] < depth[b])
				dp[i][j] = a;
			else
				dp[i][j] = b;
		}
	}
}
int rmq(int x, int y)
{
	int k = log2(y - x + 1);
	int a = dp[x][k];
	int b = dp[y - (1 << k) + 1][k];
	if (depth[a] < depth[b]) return a;
	return b;
}
int lca(int a, int b)
{
	int x = first[a];
	int y = first[b];
	int k;
	if (x <= y)
	{
		k = rmq(x, y);
		return node[k];
	}
	else
	{
		k = rmq(y, x);
		return node[k];
	}
}