#include <bits/stdc++.h>

using namespace std;

typedef long unsigned int lui;
const int MAX_N = 3005;
const int MAX_C = 257;

string s;
string t;

int dp[MAX_N][MAX_N];

int filldp(int i, int j)
{

  if (dp[i][j] != -1)
    return dp[i][j];

  if (i >= (int)s.size() || j >= (int)t.size())
    return dp[i][j] = 0;

  int resp = max(filldp(i + 1, j), filldp(i, j + 1));
  if (s[i] == t[j])
    resp = max(resp, 1 + filldp(i + 1, j + 1));

  return dp[i][j] = resp;
}

string solve()
{
  string ans = "";
  int i = 0, j = 0;
  while (dp[i][j])
  {
    while (dp[i + 1][j] == dp[i][j])
      i++;
    while (dp[i][j + 1] == dp[i][j])
      j++;
    ans += s[i];
    i++;
    j++;
  }
  return ans;
}

int main(void)
{
  cin >> s >> t;

  memset(dp, -1, sizeof(dp));
  filldp(0, 0);

  cout << solve() << endl;

  return 0;
}