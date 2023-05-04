#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 600;
const int K_MAX = 300;
const int INF = 1 << 30;
int v[N_MAX + 5];
int sum[N_MAX + 5];
int dp[N_MAX + 5][K_MAX + 5];
int n;

int rec(int begin, int kleft)
{
  if (dp[begin][kleft] >= 0)
    return dp[begin][kleft];

  if (kleft == 1)
    return dp[begin][kleft] = sum[begin];

  int ret = INF;
  int curr_dist = 0;
  for (int i = begin; i <= n - kleft; i++)
  {
    curr_dist += v[i];
    int max_dist = max(curr_dist, rec(i + 1, kleft - 1));
    ret = min(ret, max_dist);
  }

  dp[begin][kleft] = ret;
  return ret;
}

int main(void)
{
  int k;

  while (cin >> n >> k)
  {
    n++;
    k++;
    for (int i = 0; i < n; i++)
      cin >> v[i];

    memset(dp, -1, sizeof(int) * (N_MAX + 5) * (K_MAX + 5));

    if (n > 0)
      sum[n - 1] = v[n - 1];
    for (int i = n - 2; i >= 0; i--)
      sum[i] = sum[i + 1] + v[i];

    cout << rec(0, k) << endl;
  }

  return 0;
}