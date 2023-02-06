#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxn = 2e5 + 5;
char s[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], n, k;
char ans[105][1005];
void build_sa(int n, int m)
{
    int i, * x = t, * y = t2;
    for (i = 0; i < m; i++)c[i] = 0;
    for (i = 0; i < n; i++)c[x[i] = s[i]]++;
    for (i = 1; i < m; i++)c[i] += c[i - 1];
    for (i = n - 1; i >= 0; i--)sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for (i = n - k; i < n; i++)y[p++] = i;
        for (i = 0; i < n; i++)if (sa[i] >= k)y[p++] = sa[i] - k;
        for (i = 0; i < m; i++)c[i] = 0;
        for (i = 0; i < n; i++)c[x[y[i]]]++;
        for (i = 1; i < m; i++)c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--)sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1, x[sa[0]] = 0;
        for (i = 1; i < n; i++)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
        if (p >= n)break;
        m = p;
    }
}

int ht[maxn], rk[maxn];

void getHeight(int n, int m)
{
    int i, j, k = 0;
    for (i = 0; i < n; i++)rk[sa[i]] = i;
    for (i = 0; i < n - 1; i++)
    {
        if (k)k--;
        if (s[i] == '$')continue;
        int j = sa[rk[i] - 1];
        while (s[i + k] == s[j + k] && s[i + k] != '$')k++;
        ht[rk[i]] = k;
    }
}

int len[105];
int pos[maxn];
int vis[105];
int pre[maxn];
int f[maxn][20];
void st_pre(int n)
{
    for (int i = 1; i <= n; i++)f[i][0] = ht[i];
    int t = log2(n) + 1;
    for (int j = 1; j < t; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int RMQ(int i, int j)
{
    if (i > j)swap(i, j);
    i++;
    int k = pre[j - i + 1];
    return min(f[i][k], f[j - (1 << k) + 1][k]);
}

int sta[maxn];
int main(void)
{
    for (int i = 1; i < maxn; i++)pre[i] = log2(i);
    while (~scanf("%d", &k) && k)
    {
        memset(len, 0, sizeof(len));
        memset(vis, 0, sizeof(vis));
        int top = 0, ltop = 0, tot = 0;
        for (int i = 1; i <= k; i++)
        {
            scanf("%s", s + len[i - 1]);
            len[i] = strlen(s);
            s[len[i]] = '$';
            len[i]++;
        }
        if (k == 1)
        {
            for (int i = 0; i < len[1] - 1; i++)printf("%c", s[i]);
            puts("");
            continue;
        }
        build_sa(len[k], 130);
        getHeight(len[k], k);
        st_pre(len[k] - 1);
        pos[k] = upper_bound(len + 1, len + 1 + k, sa[k] + 1) - len;
        vis[pos[k]] = 1;
        int ans_num = 0;
        int cnt = 1;
        ltop = 1;
        sta[++top] = pos[k];
        int limit = ceil(k * 1.0 / 2);
        if (limit * 2 == k)limit++;
        for (int i = k + 1; i < len[k]; i++)
        {
            pos[i] = upper_bound(len + 1, len + 1 + k, sa[i] + 1) - len;
            sta[++top] = pos[i];
            if (!vis[pos[i]])
            {
                vis[pos[i]] = 1;
                cnt++;
            }
            else
            {
                vis[pos[i]]++;
                int tmp = 0;
                while (sta[top - tmp] == sta[ltop] && top - tmp > ltop)
                {
                    tmp++;
                    vis[pos[ltop + k - 1]]--;
                    ltop++;
                }
            }
            if (cnt > limit)
            {
                vis[pos[ltop + k - 1]]--;
                ltop++;
                cnt--;
                while (vis[pos[ltop + k - 1]] > 1)
                {
                    vis[pos[ltop + k - 1]]--;
                    ltop++;
                }
            }

            if (cnt == limit)
            {
                while (vis[pos[ltop + k - 1]] > 1)
                {
                    vis[pos[ltop + k - 1]]--;
                    ltop++;
                }
                int tmp = RMQ(ltop + k - 1, i);
                if (tmp > ans_num)
                {
                    ans_num = tmp;
                    tot = 0;
                    strncpy(ans[++tot], s + sa[i], ans_num);
                    ans[tot][ans_num] = '\0';
                }
                else if (tmp == ans_num && tmp)
                {
                    if (strncmp(ans[tot], s + sa[i], ans_num))strncpy(ans[++tot], s + sa[i], ans_num), ans[tot][ans_num] = '\0';
                }
            }
        }
        if (!tot)puts("?");
        else for (int i = 1; i <= tot; i++)printf("%s\n", ans[i]);
        puts("");
    }
}