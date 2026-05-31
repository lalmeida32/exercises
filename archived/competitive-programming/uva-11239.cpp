#include <bits/stdc++.h>

using namespace std;

struct CompareFunc
{
  bool operator()(const pair<string, int> &lhs, const pair<string, int> &rhs)
  {
    if (lhs.second < rhs.second)
      return true;
    else if (lhs.second == rhs.second && lhs.first.compare(rhs.first) > 0)
      return true;
    return false;
  }
};

int main(void)
{

  while (true)
  {
    map<string, string> rel;
    map<string, int> counter;
    set<string> removed;
    string input;
    string project;

    getline(cin, input);
    if (input == "0")
      break;

    while (input != "1")
    {
      if (input[0] >= 'A' && input[0] <= 'Z')
      {
        project = input;
        counter[project] = 0;
      }
      else if (removed.count(input) == 0)
      {
        if (rel.count(input) == 0)
        {
          rel[input] = project;
          counter[project]++;
        }
        else if (rel[input] != project)
        {
          counter[rel[input]]--;
          removed.insert(input);
        }
      }
      getline(cin, input);
    }

    priority_queue<pair<string, int>, vector<pair<string, int>>, CompareFunc> pq;

    for (auto it = counter.begin(); it != counter.end(); it++)
    {
      pq.emplace(it->first, it->second);
    }

    while (pq.size())
    {
      auto top = pq.top();
      pq.pop();
      cout << top.first << " " << top.second << endl;
    }
  }

  return 0;
}
