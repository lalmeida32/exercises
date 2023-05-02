#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000;

int l[MAX_N + 5];
int t[MAX_N + 5][18];

void fillt(int n)
{
  for (int i = 0; i < n; i++)
    t[i][0] = i;

  for (int j = 1, pot = 2; pot <= n; j++, pot = pot << 1)
    for (int i = 0, c = pot >> 1; i <= n - pot; i++, c++)
    {
      int index1 = t[i][j - 1];
      int index2 = t[c][j - 1];

      t[i][j] = l[index1] < l[index2] ? index1 : index2;
    }
}

int solve(int i, int j)
{
  int size = j - i + 1;

  int pot = size;
  int j_pot = 0;
  while (pot != 1)
  {
    pot = pot >> 1;
    j_pot++;
  }
  pot = pot << j_pot;

  return min(l[t[i][j_pot]], l[t[j - pot + 1][j_pot]]);
}

int main(void)
{
  int n, q, i, j;

  cin >> n;
  for (int k = 0; k < n; k++)
    cin >> l[k];

  fillt(n);

  cin >> q;
  for (int k = 0; k < q; k++)
  {
    cin >> i >> j;
    cout << solve(i, j) << endl;
  }

  return 0;
}