//POJ1990 MooFest
//2022.11.29


#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 20005
#define ll long long

ll c[2][MAXN]; //两个树状数组,c[0]存点数，c[1]存距离。
ll all_dis;
ll ans;

struct COW
{
	int v, x;//v是牛的权值，x是牛的位置
}cows[MAXN];
//树状数组，
ll lowbit(ll x);
ll get_sum(ll x, bool op);
void modify(ll x, bool op);
int comp(const COW& a, const COW& b);

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &cows[i].v, &cows[i].x);
	sort(cows + 1, cows + 1 + n, comp);
	for (int i = 1; i <= n; i++)
	{
		ll cnt = get_sum(cows[i].x, 0);
		ll now_dis = get_sum(cows[i].x, 1);
		ll left = cnt * cows[i].x - now_dis;
		ll right = all_dis -now_dis- (i - cnt - 1) * cows[i].x;
		ans += (left + right) * cows[i].v;
		all_dis += cows[i].x;
		modify(cows[i].x, 0);
		modify(cows[i].x, 1);
	}
	printf("%lld", ans);
	return 0;
}
ll lowbit(ll x)
{
	return x & (-x);
}
ll get_sum(ll x, bool op)
{
	ll sum = 0;
	for (ll i = x; i; i -= lowbit(i))
	{
		sum += c[op][i];
	}
	return sum;
}
void modify(ll x, bool op)
{
	for (ll i = x; i <= MAXN; i += lowbit(i))
	{
		if (op)
			c[op][i] += x;
		else
			c[op][i]++;
	}
}
int comp(const COW& a, const COW& b)
{
	return a.v < b.v;
}