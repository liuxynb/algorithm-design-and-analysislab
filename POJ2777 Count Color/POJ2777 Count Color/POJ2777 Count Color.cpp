/* 
2022.12.7
线段树模板
*/
#include<stdio.h>
#include<string.h>

#define MAXN 500001
bool visit[31];

struct segTree
{
	int le, ri;
	int color;
	int flag;
}tree[MAXN<<1+1];

void build_tree(int p, int le, int ri);
void Laze_spread(int p);
void modify(int p, int le, int ri, int c);
void query(int p, int le, int ri);

int main(void)
{
	int n, m, t;
	scanf("%d%d%d", &n, &t, &m);
	build_tree(1, 1, n);
	for (int i = 0; i < m; i++)
	{
		char s[5];
		int x, y;
		scanf("%s %d%d", s, &x, &y);
		if (x > y)
		{
			int swap = x;
			x = y;
			y = swap;
		}
		if (s[0] == 'P')
		{
			memset(visit, false, sizeof(visit));
			query(1, x, y);
			int ans = 0;
			for (int i = 1; i <= t; i++)
			{
				if (visit[i])
					ans++;
			}
			printf("%d\n", ans);
		}
		else
		{
			int c;
			scanf("%d", &c);
			modify(1, x, y, c);
		}
	}
	return 0;
}
void build_tree(int p, int le, int ri)
{
	tree[p].le = le;
	tree[p].ri = ri;
	tree[p].color = 1;
	tree[p].flag = 0;
	if (le == ri)
	{
		tree[p].color = 1;
		tree[p].flag = 0;
		return;
	}
	int mid = (le + ri) >> 1;
	build_tree(p * 2, le, mid);
	build_tree(p * 2 + 1, mid + 1, ri);
	tree[p].color = 1;
	tree[p].flag = 0;
}
void Laze_spread(int p)
{
	if (tree[p].flag)
	{
		tree[p * 2].color = tree[p].color;
		tree[p * 2 + 1].color = tree[p].color;
		tree[p * 2].flag = tree[p * 2 + 1].flag = 1; /*lazy标签*/
		tree[p].flag = 0;
	}
}
void modify(int p, int le, int ri, int c)
{
	if (le <= tree[p].le && ri >= tree[p].ri)
	{
		tree[p].color = c;
		tree[p].flag = 1;
		return;
	}
	Laze_spread(p);
	int mid = (tree[p].le + tree[p].ri)/2;
	if (le <= mid)
		modify(p * 2, le, ri, c);
	if (ri > mid)
		modify(p * 2 + 1, le, ri, c);
	if (tree[p * 2].color == tree[p * 2 + 1].color)
		tree[p].color = tree[p * 2].color;
	else
	{
		tree[p].color = -1;/*子区间颜色不统一*/
	}
}
void query(int p, int le, int ri)
{
	if (tree[p].le == tree[p].ri)
	{
		visit[tree[p].color] = true;
		return;
	}
	if (le <= tree[p].le && ri >= tree[p].ri)
	{
		if (tree[p].color != -1)
		{
			visit[tree[p].color] = true;
			return;
		}
	}
	Laze_spread(p);
	int mid = (tree[p].le + tree[p].ri) >> 1;
	if (le <= mid)
		query(p*2, le, ri);
	if (ri > mid)
		query(p * 2 + 1, le, ri);
	return;
}
