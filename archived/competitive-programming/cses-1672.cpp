#include <bits/stdc++.h>

typedef long long int lli;

lli n, m, q;
lli a, b, c;

const lli MAX_N = 500 + 5;
const lli INF = 0x3f3f3f3f3f3f3f3fLL;

using namespace std;

lli dist[MAX_N][MAX_N];

int main(void)
{
  cin >> n >> m >> q;

  memset(dist, 0x3f, sizeof(dist));
  for (int i = 1; i <= n; i++)
    dist[i][i] = 0;

  for (int i = 0; i < m; i++)
  {
    cin >> a >> b >> c;
    dist[a][b] = min(dist[a][b], c);
    dist[b][a] = min(dist[b][a], c);
  }

  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  for (int i = 0; i < q; i++)
  {
    cin >> a >> b;
    cout << (dist[a][b] == INF ? -1 : dist[a][b]) << endl;
  }

  return 0;
}