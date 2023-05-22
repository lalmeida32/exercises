#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1005;
const int MAX_X = 1e5 + 5;

int n, x;
int h[MAX_N];
int s[MAX_N];
int dp[MAX_X];

int main(void)
{

  cin >> n >> x;

  for (int i = 0; i < n; i++)
    cin >> h[i];

  for (int i = 0; i < n; i++)
    cin >> s[i];

  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < n; i++)
    for (int j = x; j >= h[i]; j--)
      dp[j] = max(dp[j], s[i] + dp[j - h[i]]);

  cout << dp[x];

  return 0;
}