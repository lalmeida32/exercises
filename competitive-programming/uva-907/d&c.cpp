#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 600;
int v[N_MAX + 5];
int n, k;
int solution;

int search_answer(int l, int r)
{
  if (l > r)
    return solution;

  int m = (l + r) / 2;

  int curr = 0;
  int n_blocks = 1;
  for (int i = 0; i < n; i++)
  {
    if (curr + v[i] <= m)
      curr += v[i];
    else
    {
      n_blocks++;
      curr = v[i];
    }
  }

  if (n_blocks > k)
    return search_answer(m + 1, r);
  solution = m;
  return search_answer(l, m - 1);
}

int main(void)
{
  while (cin >> n >> k)
  {
    n++;
    k++;

    int total = 0;
    int maxv = -1;
    for (int i = 0; i < n; i++)
    {
      cin >> v[i];
      total += v[i];
      maxv = max(maxv, v[i]);
    }

    cout << search_answer(maxv, total) << endl;
  }

  return 0;
}