#include <bits/stdc++.h>

using namespace std;

int main(void)
{
  vector<uint64_t> v;

  for (int n = 1; true; n++)
  {
    uint64_t num;
    cin >> num;
    if (cin.eof())
      break;
    v.push_back(num);

    for (int i = n - 1; i > 0; i--)
    {
      if (v[i] >= v[i - 1])
        break;

      uint64_t c = v[i];
      v[i] = v[i - 1];
      v[i - 1] = c;
    }

    if (n % 2 == 0)
      cout << (v[n / 2] + v[n / 2 - 1]) / 2 << endl;
    else
      cout << v[n / 2] << endl;
  }
  return 0;
}