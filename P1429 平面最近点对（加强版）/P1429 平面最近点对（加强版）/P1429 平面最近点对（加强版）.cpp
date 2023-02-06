#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 200001
#define INF (1<<31)-1
struct Node
{
	double x, y;
}node[MAXN];
int mpt[MAXN];
/*求距离*/
double dist(Node a, Node b);
/*按照x坐标排序*/
bool cmp(Node a, Node b);
/*按照y坐标排序*/
bool cmp2(int a, int b);
/*利用分治法求最近点对*/
double find(int left, int right);

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &node[i].x, &node[i].y);
	sort(node + 1, node + 1 + n, cmp);//对x坐标预排序
	printf("%.4lf", find(1, n));
	return 0;
}
/*求距离*/
double dist(Node a, Node b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
/*按照x坐标排序*/
bool cmp(Node a, Node b)
{
	if (a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}
/*按照y坐标排序*/
bool cmp2(int a, int b)
{
	return node[a].y < node[b].y;
}
/*利用分治法求最近点对*/
double find(int left, int right)
{
	int dis = INF;//自己和自己的距离设置为正无穷大
	if (left == right)return dis;
	if (left + 1 == right)return dist(node[left], node[right]); //直接求两点距离
	int mid = (left + right) / 2;
	double dis_l = find(left, mid - 1);
	double dis_r = find(mid, right);
	double minn = dis_l < dis_r ? dis_l : dis_r;
	int cnt = 0;
	for (int i = left; i <= right; i++)
	{
		if (fabs(node[mid].x - node[i].x) <= minn)  //有可能在两个平面中间还有其他的更小距离的先决条件
		{
			mpt[++cnt] = i;
		}
	}
	sort(mpt + 1, mpt + cnt + 1, cmp2);
	for (int i = 1; i <= cnt; i++)//下降算法复杂度
	{
		for (int j = i + 1; j <= cnt && (node[mpt[j]].y - node[mpt[i]].y) <= minn; j++)
		{
			double d = dist(node[mpt[i]], node[mpt[j]]);
			if (minn >= d)
			{
				minn = d;
			}
		}
	}
	return minn;
}