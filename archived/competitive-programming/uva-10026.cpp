#include <bits/stdc++.h>

using namespace std;

void solve(int n)
{
  vector<pair<long double, int>> vec;
  int Di, Ci;

  for (int i = 0; i < n; i++)
  {
    cin >> Di >> Ci;
    vec.emplace(vec.begin() + i, Di / (long double)Ci, i);
  }

  sort(vec.begin(), vec.end(), less<pair<long double, int>>());

  for (int i = 0; i < n; i++)
  {
    cout << vec[i].second + 1;
    if (i != n - 1)
      cout << ' ';
  }

  cout << endl;
}

int main(void)
{
  int t;
  cin >> t;

  for (int i = 0; i < t; i++)
  {
    int n;
    cin >> n;

    if (i != 0)
      cout << endl;

    solve(n);
  }

  return 0;
}