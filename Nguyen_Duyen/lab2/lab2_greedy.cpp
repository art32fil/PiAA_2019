#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Path {
public:
	char start, end;
	double weight;

	Path() {};

	Path(char s, char e, double w) :start(s), end(e), weight(w) {
		this->start = s;
		this->end = e;
		this->weight = w;
	}
};
vector<Path*> path;
vector<char> listVisit;
vector<char> res;

bool isVisit(char current) {
	for (size_t i = 0; i < listVisit.size(); i++) {
		if (listVisit[i] == current)
			return true;
	}
	return false;
}
bool greedy(char current, char end_way) {
	if (end_way == current){
		res.push_back(current);
		return true;
	}

	listVisit.push_back(current);
	for (size_t i = 0; i < path.size(); i++) {
		if (path[i]->start == current && isVisit(path[i]->end) == false) {
			res.push_back(current);
			if (greedy(path[i]->end, end_way))
				return true;
			res.pop_back();
		}
	}
	return false;
}

int main()
{
	char start_way, end_way;
	cin >> start_way >> end_way;

	while (true) {
		char s, e;
		double w;
		if ((cin >> s) && (cin >> e) && (cin >> w)) {
			Path *p = new Path(s, e, w);
			path.push_back(p);
		}
		else
			break;
	}

	greedy(start_way, end_way);
	for (int i = 0; i < res.size(); i++)
		cout << res[i];
	cout << endl;

	system("pause");
	return 0;
}
