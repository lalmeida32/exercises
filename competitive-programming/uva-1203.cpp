#include<bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> trio;

int main(void) {
	string command;
	priority_queue<trio, vector<trio>, greater<trio>> q;
	int Qnum, Period, Time;

	while(true) {
		cin >> command;
		if (command == "#") break;

		cin >> Qnum >> Period;

		q.emplace(Period, Qnum, Period);

	}

	int k;
	cin >> k;

	while(k-- > 0) {
		trio t = q.top();
		q.pop();

		Time = get<0>(t);
		Qnum = get<1>(t);
		Period = get<2>(t);

		cout << Qnum << endl;

		q.emplace(Time+Period, Qnum, Period);
	}

	return 0;
}
