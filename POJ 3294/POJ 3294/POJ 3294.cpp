#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define MAXN 410
#define MAXL 4010
#define MAX 400010

int c[MAX];
int n, cl;

char str[MAXL];
int p[MAX];
void init()
{
    cl = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str);
        int l = strlen(str);
        for (int j = 0; j < l; j++) c[++cl] = str[j] - 'a' + 1, p[cl] = i;
        c[++cl] = 26 + i, p[cl] = 0;
    }
}

int sa[MAX], rk[MAX], Rs[MAX], y[MAX], wr[MAX];
void get_sa(int m)
{
    memcpy(rk, c, sizeof(rk));
    for (int i = 0; i <= m; i++) Rs[i] = 0;
    for (int i = 1; i <= cl; i++) Rs[rk[i]]++;
    for (int i = 1; i <= m; i++) Rs[i] += Rs[i - 1];
    for (int i = cl; i >= 1; i--) sa[Rs[rk[i]]--] = i;

    int ln = 1, p = 0;
    while (p < cl)
    {
        int k = 0;
        for (int i = cl - ln + 1; i <= cl; i++) y[++k] = i;
        for (int i = 1; i <= cl; i++) if (sa[i] > ln) y[++k] = sa[i] - ln;
        for (int i = 1; i <= cl; i++) wr[i] = rk[y[i]];

        for (int i = 0; i <= m; i++) Rs[i] = 0;
        for (int i = 1; i <= cl; i++) Rs[wr[i]]++;
        for (int i = 1; i <= m; i++) Rs[i] += Rs[i - 1];
        for (int i = cl; i >= 1; i--) sa[Rs[wr[i]]--] = y[i];

        for (int i = 1; i <= cl; i++) wr[i] = rk[i];
        for (int i = cl + 1; i <= cl + ln; i++) wr[i] = 0;
        p = 1, rk[sa[1]] = 1;
        for (int i = 2; i <= cl; i++)
        {
            if (wr[sa[i]] != wr[sa[i - 1]] || wr[sa[i] + ln] != wr[sa[i - 1] + ln]) p++;
            rk[sa[i]] = p;
        }
        ln *= 2; m = p;
    }
    sa[0] = rk[0] = 0;
}

int height[MAX];
void get_he()
{
    int k = 0;
    for (int i = 1; i <= cl; i++) if (rk[i] != 1)
    {
        int j = sa[rk[i] - 1];
        if (k) k--;
        while (c[i + k] == c[j + k] && i + k <= cl && j + k <= cl) k++;
        height[rk[i]] = k;
    }
}

bool inq[MAXN];
queue<int > q;
int ans[2][MAX], now;
bool to_check(int x)
{
    if (x == 0) return 1;
    ans[1 - now][0] = 0;
    int cnt = 0;
    bool ok = 0;
    for (int i = 1; i <= cl - n; i++)
    {
        if (!inq[p[sa[i]]])
        {
            q.push(p[sa[i]]);
            inq[p[sa[i]]] = 1;
            cnt++;
        }
        if (height[i + 1] < x)
        {
            if (cnt > n / 2 && cnt != 1) ok = 1, ans[1 - now][++ans[1 - now][0]] = sa[i];
            cnt = 0;
            while (!q.empty()) { inq[q.front()] = 0; q.pop(); }
        }
    }
    if (ok) now = 1 - now;
    return ok;
}

void find()
{
    now = 1;
    while (!q.empty()) q.pop();
    memset(inq, 0, sizeof(inq));
    int l = 0, r = cl;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (to_check(mid)) l = mid;
        else r = mid - 1;
    }
    if (l == 0) printf("?\n");
    else
    {
        for (int i = 1; i <= ans[now][0]; i++)
        {
            for (int j = 0; j < l; j++)
                printf("%c", c[j + ans[now][i]] - 1 + 'a');
            printf("\n");
        }
    }
}

int main(void)
{
    while (1)
    {
        scanf("%d", &n);
        if (n == 0) break;
        init();
        get_sa(30 + n);
        get_he();
        find();
        printf("\n");
    }
    return 0;
}
