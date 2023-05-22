#include <bits/stdc++.h>

using namespace std;

typedef long long int lii;

const int MAX_N = 1005;
const lii MOD_C = 1e9 + 7;

int n;
char grid[MAX_N][MAX_N];
lii paths[MAX_N][MAX_N];

lii solve(int i, int j)
{
  if (grid[i][j] != '.')
    return 0;
  if (paths[i][j] != -1)
    return paths[i][j];

  lii res = 0;
  res += solve(i + 1, j) % MOD_C;
  res += solve(i, j + 1) % MOD_C;

  return paths[i][j] = res % MOD_C;
}

int main(void)
{
  cin >> n;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> grid[i][j];

  memset(paths, -1, sizeof(lii) * MAX_N * MAX_N);
  paths[n - 1][n - 1] = 1;

  cout << solve(0, 0);

  return 0;
}