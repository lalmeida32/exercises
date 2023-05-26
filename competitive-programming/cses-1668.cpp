#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 5;
const int M_MAX = 2 * 1e5 + 5;

set<int> rels[N_MAX];
set<int> available;
queue<int> q;
int teams[N_MAX];
bool relaxed[N_MAX];

int n, m;

void solve()
{
  int cur = 1;

  q.push(cur);
  teams[cur] = 1;

  while (true)
  {
    cur = q.front();
    q.pop();

    for (auto it = rels[cur].begin(); it != rels[cur].end(); it++)
    {
      if (teams[cur] == teams[*it])
        return;
      if (!teams[*it])
        q.push(*it);
      teams[*it] = 3 - teams[cur];
    }

    relaxed[cur] = true;
    available.erase(cur);

    if (!available.size())
      break;

    if (!q.size())
    {
      cur = *available.begin();
      q.push(cur);
      teams[cur] = 1;
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