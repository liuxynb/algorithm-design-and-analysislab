// 2022/11/16
//并查集

/*0 同种动物，
1 捕食关系，
2被捕食关系，
*/
#include<stdio.h>
int fa[50001], rank[50001];
int to_find_fa(int x);
int main(void)
{
	int n, k;//表示有 N 个动物，K 句话。
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		rank[i] = 0;
	}
	int false_cnt = 0;//初始化。

	for (int i =1 ; i <= k; i++)
	{
		int w, x, y;
		scanf("%d%d%d", &w, &x, &y);
		if ((x > n || y > n) || (w == 2 && x == y))
		{
			false_cnt++;
			continue;
		}//处理显而易见的错误。

		int f1 = to_find_fa(x);
		int f2 = to_find_fa(y);//找出祖先

		if (w == 2)//即X吃Y
		{
			if (f1 == f2) {
				if (((rank[x] - rank[y] + 3) % 3) != 1)
				{
					false_cnt++;
					continue;
				}
			}
			else//合并。
			{
				fa[f1] = f2;
				rank[f1] = (3 - rank[x] + rank[y] + 1) % 3;
			}
				
		}
		if (w == 1) //即同类
		{
			if (f1 == f2 && rank[x] != rank[y])//判假
			{
				false_cnt++;
				continue;
			}
			else if (f1 != f2)//合并
			{
				fa[f1] = f2;
				rank[f1] = (3 - rank[x] + rank[y]) % 3;
			}
		}
	}
	printf("%d", false_cnt);
	return 0;

}

int to_find_fa(int x)//查找+路径压缩
{
	int f = fa[x];
	if (x != f)
	{
		fa[x] = to_find_fa(f);
		rank[x] = (rank[x] + rank[f]) % 3;
		return fa[x];
	}
	return x;
}
