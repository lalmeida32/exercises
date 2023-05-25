#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5005;

string s;
string t;

int dp[MAX_N][MAX_N];

int solve(int i, int j)
{

  if (dp[i][j] != -1)
    return dp[i][j];

  if (i >= (int)s.size() || j >= (int)t.size())
  {
    int ri = (int)s.size() - i;
    int rj = (int)t.size() - j;
    return dp[i][j] = ri + rj;
  }

  int resp = 1 + solve(i + 1, j + 1);
  if (s[i] == t[j])
    resp--;
  resp = min(resp, 1 + solve(i, j + 1));
  resp = min(resp, 1 + solve(i + 1, j));

  return dp[i][j] = resp;
}

int main(void)
{
  cin >> s >> t;

  memset(dp, -1, sizeof(dp));

  cout << solve(0, 0) << endl;

  return 0;
}