#include<stdio.h>
#include<string.h>
#define MAXN 601
int pre[MAXN], rank[MAXN];              //并查集
int visited[MAXN], ans[MAXN][2];        // ans[i][0]表示与根节点i同类的节点个数， ans[i][1]代表与根节点i不同类的节点个数
int d[MAXN][MAXN];  // d[i][j]前i个集合中累计人数为j时有多少种可能
int a[MAXN][2];     //记录输出值
int vis[MAXN][MAXN][2];
/*vis[i][j][]保存每一个集合选了哪一类，为最后输出用。
vis[i][j][0]表示前i个集合中累计人数为j时的最根节点，vis[i][j][1]此时与根节点的关系。
即记录答案。*/

//初始化并查集
void init_set(int n, int  p1, int p2);
//并集
void merge(int x, int y, int rel);  
//查集
int find_f(int x);          
//dp
void dp(int n, int  p1, int p2, int min);

int main(void)
{
	int n, p1, p2;
	while (scanf("%d%d%d", &n, &p1, &p2) && n + p1 + p2 != 0)
	{
		init_set(n, p1, p2);
		for (int i = 0; i < MAXN; i++)
		{
			visited[i] = 0;
		}
		for (int i = 0; i < MAXN; i++)
		{
			ans[i][0] = ans[i][1] = 0;
		}
		int min = 10e9;
		int flag = 0;//存储一共有多少个不同的最跟部的父节点
		for (int i = 1; i <= p1 + p2; i++)
		{
			int f = pre[i];
			int r = rank[i];
			if (f < min) 
			{
				min = f;
			}		
			ans[f][r]++;
			if (visited[f] == 0)//还没有访问过
			{
				visited[f] = 1; flag++;
			}
		}
		for (int i = 0; i < MAXN; i++)
			for(int j=0;j<MAXN;j++)
			{
				d[i][j] = 0;
			}
		for(int i=0;i<MAXN;i++)
			for (int j = 0; j < MAXN; j++)
			{
				vis[i][j][0] = vis[i][j][1] = 0;
			}
		d[1][ans[min][0]]++; 
		d[1][ans[min][1]]++;
		vis[1][ans[min][0]][0] = min;
		vis[1][ans[min][0]][1] = 0;
		vis[1][ans[min][1]][0] = min;
		vis[1][ans[min][1]][1] = 1;

		dp(n, p1, p2, min);

		if (d[flag][p1] == 1)//如果前flag个集合中累计人数为n1的可能为1时，有唯一解
		{
			int j = p1;
			for (int i = flag; i >= 1; i--)
			{
				a[i][0] = vis[i][j][0];
				a[i][1] = vis[i][j][1];
				j -= ans[a[i][0]][a[i][1]];
			}
			for (int i = 1; i <= p1 + p2; i++)
			{
				for (int j = 1; j <= flag; j++)
				{
					int f = pre[i];
					int sign = rank[i];
					if (f == a[j][0] && sign == a[j][1])
						printf("%d\n", i);
				}
			}
			printf("end\n");
		}
		else
		{
			printf("no\n");
		}
	}
}
void init_set(int n, int  p1, int p2)
{
	for (int i = 1; i <= p1 + p2; i++)
	{
		pre[i] = i;
		rank[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		char c[5];
		scanf("%d%d%s", &x, &y, c);
		if (c[0] == 'y')
			merge(x, y, 0);
		else
			merge(x, y, 1);
	}
	for (int i = 1; i <= p1 + p2; i++)
	{
		find_f(i);
	}                                //初始化并查集
}
void dp(int n,int  p1, int p2,int min)
{
	int k = 1;
	for (int i = min + 1; i <= p1 + p2; i++)
	{
		if (visited[i] == 1)
		{
			k++;
			int t1 = ans[i][0];
			int t2 = ans[i][1];
			int m = t1 > t2 ? t2 : t1;
			for (int j = p1; j >= m; j--)
			{
				d[k][j] = d[k - 1][j - t1] + d[k - 1][j - t2];
				if (d[k - 1][j - t1] == 1 && d[k - 1][j - t2] == 0)
				{
					vis[k][j][0] = i;
					vis[k][j][1] = 0;
				}
				else if (d[k - 1][j - t2] == 1 && d[k - 1][j - t1] == 0)
				{
					vis[k][j][0] = i;
					vis[k][j][1] = 1;
				}
			}
		}
	}
}
void merge(int x, int y, int rel)//并集
{
	int fx = find_f(x);
	int fy = find_f(y);
	if (fx != fy)
	{
		pre[fy] = fx;
		rank[fy] = (rank[x] + rank[y] + rel) % 2;
	}
}
int find_f(int x) //查找父节点并且缩短路径（查集）
{
	if (pre[x] == x)
		return x;
	int fx = pre[x];
	pre[x] = find_f(pre[x]);
	rank[x] = (rank[fx] + rank[x]) % 2;
	return pre[x];
}