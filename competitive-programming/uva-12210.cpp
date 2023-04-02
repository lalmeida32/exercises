#include <bits/stdc++.h>

using namespace std;

int main(void)
{
  int k = 1;

  while (true)
  {
    int b, s;
    cin >> b >> s;

    if (b == 0 && s == 0)
      break;

    int count = b - s;
    count = count < 0 ? 0 : count;
    int smallest = 70;
    int age;

    for (int i = 0; i < b; i++)
    {
      cin >> age;
      if (age < smallest)
        smallest = age;
    }

    for (int i = 0; i < s; i++)
      cin >> age;

    cout << "Case " << k << ": " << count;
    if (count > 0)
      cout << ' ' << smallest;
    cout << endl;

    k++;
  }

  return 0;
}