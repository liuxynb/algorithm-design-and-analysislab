#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>

using namespace std;

#define N 40010
#define lson (p*2)
#define rson (p*2+1)


struct Node
{
    int from, to, height;
}node[N];

struct TNode
{
    int l, r;
    __int64 height;
    __int64 sum;
}tnode[N << 4];
//按高度排序
bool cmp(Node a, Node b)
{
    return a.height < b.height;
}

int temp[N << 2], index[N << 2], brush[N << 2];
//二分查找
int findPos(int a, int k)
{
    int l, r, mid = -1;
    l = 1;
    r = k;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (a < index[mid])  r = mid - 1;
        else if (a > index[mid])   l = mid + 1;
        else return mid;
    }
    return mid;
}
//建树
void initTree(int l, int r, int p)
{
    tnode[p].l = l;
    tnode[p].r = r;
    tnode[p].height = 0;
    tnode[p].sum = 0;
    if (l + 1 == r)    return;
    int mid = (l + r) >> 1;
    initTree(l, mid, lson);
    initTree(mid, r, rson);
}

void updateTree(int l, int r, int p, int h)
{
    if (tnode[p].l == l && r == tnode[p].r)
    {
        tnode[p].height = h;
        tnode[p].sum = (index[r] - index[l]) * tnode[p].height;  //这里的height是64位int，相乘得64为int
        return;
    }
    if (tnode[p].height > 0) //向下更新
    {
        tnode[lson].sum = (index[tnode[lson].r] - index[tnode[lson].l]) * tnode[p].height;
        tnode[rson].sum = (index[tnode[rson].r] - index[tnode[rson].l]) * tnode[p].height;
        tnode[lson].height = tnode[rson].height = tnode[p].height;
        tnode[p].height = 0;
    }
    int mid = (tnode[p].l + tnode[p].r) >> 1;
    if (r <= mid)  
        updateTree(l, r, lson, h);
    else if (l >= mid)  
        updateTree(l, r, rson, h);
    else
    {
        updateTree(l, mid, lson, h);
        updateTree(mid, r, rson, h);
    }
    //向上更新
    if (tnode[lson].height && tnode[rson].height && tnode[lson].height == tnode[rson].height)  //向上更新
    {
        tnode[p].height = tnode[lson].height;
    }
    tnode[p].sum = tnode[lson].sum + tnode[rson].sum;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int i, cnt = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%d%d%d", &node[i].from, &node[i].to, &node[i].height);
        temp[cnt++] = node[i].from;
        temp[cnt++] = node[i].to;
    }
    sort(temp, temp + cnt);  //排序
    int j = 1;
    index[1] = temp[0];
    for (i = 1; i < cnt; i++)  //去重
    {
        if (index[j] != temp[i])
        {
            index[++j] = temp[i];
        }
    }
    int k = j;
    initTree(1, k, 1);
    sort(node, node + n, cmp);
    for (i = 0; i < n; i++)
    {
        int from = findPos(node[i].from, k);
        int to = findPos(node[i].to, k);
        updateTree(from, to, 1, node[i].height);
    }
    printf("%I64d\n", tnode[1].sum); 
    return 0;
}