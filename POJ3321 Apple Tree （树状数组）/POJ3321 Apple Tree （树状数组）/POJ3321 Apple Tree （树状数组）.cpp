//树状数组（BIT）poj3321
//2022.11.23
#include<stdio.h>
#define MAXN 1000001
int n, x, y, cnt; //cnt用于计数。
int tre[MAXN];    //tre即为树状数组
int start[MAXN], out[MAXN];
int edge[MAXN], next[MAXN], head[MAXN];
int exist[MAXN];     //储存是否有苹果。

void Add_edge(int x, int y)//加双向边，链式前向星
{
	edge[++cnt] = x; next[cnt] = head[y]; head[y] = cnt;
	edge[++cnt] = y; next[cnt] = head[x]; head[x] = cnt;
}
int Lowbit(int x)// BIT中重要的概念
{
	return x & (-x);
}
void Modify(int x, int rank)//更新BIT数组状态
{
	while (x<=n)
	{
		tre[x] = tre[x] + rank;
		x = x + Lowbit(x); //自底向上
	}
}
int Get_sum(int t)
{
	int sum = 0;
	while (t > 0)
	{
		sum += tre[t];
		t -= Lowbit(t);
	}
	return sum;
}
int Get_branch(int x, int y)
{
	return Get_sum(y) - Get_sum(x - 1);
}
void Dfs(int now, int last) //类似先序遍历
{
	start[now] = ++cnt; //cnt是时间戳，dfs数组里存的是dfs序
	for (int i = head[now]; i != 0; i = next[i])
	{
		if (edge[i] != last)Dfs(edge[i], now);
	}
	out[now] = cnt; //out数组存的是start的子树在dfs序中对应的序列的末尾的下标，以求树枝上的果数。
}
int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		Add_edge(x, y);
	}
	cnt = 0;//重置计数器
	Dfs(1, -1);
	for (int i = 1; i <= n; i++)
	{
		Modify(i, 1);
		exist[i] = 1;
	}
	char str[3];
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s%d", str, &x);
		if (str[0] == 'Q')
			printf("%d\n", Get_branch(start[x], out[x]));
		else if (exist[start[x]])
		{
			Modify(start[x], -1);
			exist[start[x]] = 0;
		}
		else
		{
			Modify(start[x], 1);
			exist[start[x]] = 1;
		}
	}
}