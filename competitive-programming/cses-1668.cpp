#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 5;
const int M_MAX = 2 * 1e5 + 5;

set<int> rels[N_MAX];
int teams[N_MAX];
set<int> available;
set<int> has_team_available;

int n, m;

void solve()
{
  int next = 1;
  teams[next] = 1;
  has_team_available.insert(next);
  while (true)
  {
    // for (auto it = available.begin(); it != available.end(); it++)
    //   cout << *it << ' ';
    // cout << endl;

    int next_next = 0;

    for (auto it = rels[next].begin(); it != rels[next].end(); it++)
    {
      if (teams[next] == teams[*it])
        return;
      teams[*it] = 3 - teams[next];
      if (available.find(*it) != available.end())
      {
        has_team_available.insert(*it);
        next_next = *it;
      }
    }
    available.erase(next);
    has_team_available.erase(next);

    if (!available.size())
      break;

    next = next_next;

    if (next == 0)
    {
      if (has_team_available.size())
        next = *has_team_available.begin();
      else
      {
        next = *available.begin();
        teams[next] = 1;
        has_team_available.insert(next);
      }
    }
  }
}

int main(void)
{

  int a, b;

  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    cin >> a >> b;
    rels[a].insert(b);
    rels[b].insert(a);
  }

  for (int i = 1; i <= n; i++)
    available.insert(i);

  solve();

  if (available.size())
    cout << "IMPOSSIBLE" << endl;
  else
  {
    for (int i = 1; i < n; i++)
      cout << teams[i] << ' ';
    cout << teams[n];
  }

  return 0;
}