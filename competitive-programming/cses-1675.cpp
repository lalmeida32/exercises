#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

const lli MAX_N = 1e5 + 5;
const lli INF = 0x3f3f3f3f3f3f3f3fLL;

bool visited[MAX_N];
vector<pair<lli, lli>> edges[MAX_N];

lli n, m;
lli a, b, c;

void solve()
{
  priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> pq;
  lli counter = 0;
  lli weights = 0;

  pq.emplace(0, 1);

  while (pq.size())
  {
    lli w, e;
    tie(w, e) = pq.top();
    pq.pop();

    if (visited[e])
      continue;
    visited[e] = true;
    counter++;
    weights += w;

    for (auto it = edges[e].begin(); it < edges[e].end(); it++)
    {
      lli nw, ne;
      tie(nw, ne) = *it;

      if (!visited[ne])
        pq.emplace(nw, ne);
    }
  }

  if (counter == n)
  {
    cout << weights << endl;
    return;
  }
  cout << "IMPOSSIBLE" << endl;
}

int main(void)
{

  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    cin >> a >> b >> c;
    edges[a].emplace_back(c, b);
    edges[b].emplace_back(c, a);
  }

  solve();

  return 0;
}