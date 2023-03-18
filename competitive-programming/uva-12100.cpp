#include <bits/stdc++.h>

using namespace std;

int nums[100];
int pos[10][100];
int n_pos[10];

int cyclic_get_last(int fim, int v, int n)
{
  vector<int> vec(pos[v], pos[v] + n_pos[v]);

  if (vec[0] > fim)
    return n_pos[v] - 1;

  auto lb_it = lower_bound(vec.begin(), vec.end(), fim);
  if (lb_it == vec.end() || *lb_it != fim)
    return (lb_it - 1) - vec.begin();
  return lb_it - vec.begin();
}

int get_fim(int ini, int n)
{
  return (ini - 1 + n) % n;
}

int get_new_ini(int ini, int v, int n)
{
  int fim = get_fim(ini, n);
  return (pos[v][cyclic_get_last(fim, v, n)] + 1) % n;
}

int run(int n, int m)
{
  int ini = 0;
  for (int i = 0; i < n; i++) // O(n)
  {
    cin >> nums[i];
    pos[nums[i]][n_pos[nums[i]]++] = i;
  }

  int count = 1;

  for (int v = 9; v > nums[m]; v--)
    if (n_pos[v] > 0)
    {
      ini = get_new_ini(ini, v, n); // O(log n)
      count += n_pos[v];
    }

  int last = cyclic_get_last(get_fim(ini, n), nums[m], n); // O(log n)
  int mine = cyclic_get_last(m, nums[m], n);               // O(log n)

  if (last >= mine)
    count += n_pos[nums[m]] - abs(last - mine) - 1;
  else
    count += abs(last - mine) - 1;

  return count;
}

int main(void)
{
  int t, n, m;

  cin >> t;

  for (int i = 0; i < t; i++)
  {
    cin >> n;
    cin >> m;
    memset(n_pos, 0, 10 * sizeof(int));
    cout << run(n, m) << endl;
  }

  return 0;
}