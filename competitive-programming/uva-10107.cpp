#include <bits/stdc++.h>

using namespace std;

int main(void)
{
  vector<uint64_t> v;
  uint64_t num;

  for (int n = 1; cin >> num; n++)
  {
    auto lb_it = lower_bound(v.begin(), v.end(), num);
    v.insert(lb_it, num);

    if (n % 2 == 0)
      cout << (v[n / 2] + v[n / 2 - 1]) / 2 << endl;
    else
      cout << v[n / 2] << endl;
  }
  return 0;
}